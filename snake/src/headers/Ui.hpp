#pragma once

#include "structs.hpp"
#include <functional>
class Game;

class Ui
{
public:
    using event_fn = std::function<void(int)>; // key client (subscribe on key)
    using timer_fn = std::function<void(void)>; // timer client (subscribe on timer)

    enum
    {
        KEY_UP = 1000,
        KEY_DOWN,
        KEY_RIGHT,
        KEY_LEFT,
    };

    static Ui* get(const char* ui_type = nullptr);

    virtual int get_width()  const = 0;
    virtual int get_height() const = 0;

    virtual void run(Game&) = 0;
    
    virtual void draw() = 0;
    virtual void quit() = 0;

    virtual void on_key(event_fn fn) = 0;
    virtual void on_timer(int, timer_fn fn) = 0;

    virtual void painter(const BodyPart&) = 0;
    virtual void painter(const Rabbit&) = 0;
    virtual void painter(int id, int score) = 0;

    virtual ~Ui() = 0;
protected:
    Ui() = default;
private:
    static Ui* instance;
};
