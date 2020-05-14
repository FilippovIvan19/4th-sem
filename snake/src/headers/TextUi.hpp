#pragma once

#include <termios.h>
#include <sys/ioctl.h>
#include <vector>
#include <signal.h>
#include <unistd.h>
#include "Ui.hpp"

class TextUi : public Ui
{
public:
    TextUi();
   ~TextUi();

    int get_width()  const { return window_info.ws_col; }
    int get_height() const { return window_info.ws_row; }

    void run(Game&) override;
    void quit() override;

    void on_key(event_fn fn) override;
    void on_timer(int t, timer_fn fn) override;

    void painter(const BodyPart&) override;
    void painter(const Rabbit&) override;
    void painter(int id, int score) override;
    void draw() override;
private:
    void clear();
    void putc(int x, int y, char c);
    void setcolor(int color);
    void gotoxy(int x, int y);
    bool read_event();
    void fini_tty();
    void winch();

    struct winsize window_info; // window info
    struct termios ttys; // terminal info
    bool running;

    std::vector<event_fn> events;
    std::vector<std::pair<int, timer_fn>> timers;
};
