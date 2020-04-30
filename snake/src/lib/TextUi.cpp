#include "../headers/TextUi.hpp"

#include "../headers/Game.hpp"
#include <cstdio>
#include <sys/poll.h>


static void on_winch(int signo)
{
    Ui::get()->draw();
}

static void on_term(int signo)
{
    Ui::get()->quit();
}

TextUi::TextUi()
{
    struct termios tty;

    tcgetattr(0, &tty);
    ttys = tty;
    
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    signal(SIGINT,   on_term);
    signal(SIGTERM,  on_term);
    signal(SIGWINCH, on_winch);
    winch();
    setvbuf(stdout, NULL, _IONBF, 0);
}

TextUi::~TextUi()
{
    clear();
    fini_tty();
    setvbuf(stdout, NULL, _IOLBF, 0);
    printf("bye!\n");
}

void TextUi::clear()
{
    printf("\e[H\e[J\e[m");
}

void TextUi::gotoxy(int x, int y)
{
    printf("\e[%d;%dH", get_height() - y, x + 1);
}

void TextUi::setcolor(int color)
{
    printf("\e[%dm", color ? color + 30 : 0);
}

void TextUi::putc(int x, int y, char c)
{
    printf("\e[%d;%dH%c", y, x, c);
}

void TextUi::painter(int id, int score)
{
    gotoxy(10 * id, 0);
    setcolor(id);
    printf(" %d ", score);
    setcolor(0);
    gotoxy(0, 0);
}

void TextUi::painter(const BodyPart& elem)
{
    setcolor(elem.id);
    putc(elem.first, elem.second, "^v><# "[elem.dir]);
    setcolor(0);
    gotoxy(0, 0);
}

void TextUi::painter(const Rabbit& rab)
{
    putc(rab.first, rab.second, '@');
    gotoxy(0, 0);
}

void TextUi::fini_tty(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &ttys);
    signal(SIGINT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
    signal(SIGWINCH, SIG_DFL);
}

void TextUi::winch()
{
    ioctl(STDIN_FILENO, TIOCGWINSZ, &window_info);
}

void TextUi::quit()
{
    running = false;
}

void TextUi::on_key(event_fn fn)
{
    events.push_back(fn);
}

void TextUi::on_timer(int t, timer_fn fn)
{
    timers.emplace_back(std::max(0,t), fn);
    std::sort(timers.begin(), timers.end(),
            [] (const auto& a, const auto& b) { return a.first < b.first; } );
}

void TextUi::draw()
{
    winch();
    clear();

    for (int i = 1; i <= get_width(); i++)
    {
        putc(i, 1, '*');
        putc(i, get_height(), '*');
    }
    for (int i = 1; i <= get_height(); i++)
    {
        putc(1, i, '*');
        putc(get_width(), i, '*');
    }

    gotoxy(3,0);
    printf(" Score: ");

    gotoxy(0,0);
}

void TextUi::run(Game& game)
{
    game.draw();

    running = true;
    while (running)
    {
        struct pollfd pfd[1] = {{ .fd = STDIN_FILENO, .events = POLLIN}};
        int msecs = -1;

        if (!timers.empty())
            msecs = timers.front().first;

        struct timespec ta, tb;
        clock_gettime(CLOCK_MONOTONIC, &ta);
        int n = poll(pfd, 1, msecs);
        clock_gettime(CLOCK_MONOTONIC, &tb);
        int elapsed = ( (tb.tv_sec - ta.tv_sec) * 1000 + (tb.tv_nsec - ta.tv_nsec) / 1000000 );

        if (msecs != -1)
        {
            auto i = timers.begin();
            auto f = i->second;

            for (auto& t : timers)
                t.first = std::max(0, t.first - elapsed);

            if (msecs <= elapsed)
            {
                timers.erase(i);
                f();
            }
        }

        if (n == 1)
            if (read_event())
                break;
    }
}

bool TextUi::read_event()
{
    char ch[100];
    int n = read(STDIN_FILENO, ch, sizeof(ch));

    if (n <= 0)
        return true;

    if (n == 1 && ch[0] == '\e')
        return true;

    for (int i = 0; i < n; i++)
    {
        int key = ch[i];

        if (ch[i] == '\e' && i + 2 < n && ch[i+1] == '[')
        {
            i += 2;
            switch (ch[i])
            {
                case 'A': key = KEY_UP; break;
                case 'B': key = KEY_DOWN; break;
                case 'C': key = KEY_RIGHT; break;
                case 'D': key = KEY_LEFT; break;
            }
        }

        for (auto& f : events)
            f(key);
    }

    return false;
}
