#include "../include/controllable.h"
#include <SDL2/SDL_events.h>

using namespace view;

Controllable::Controllable(const Controllable& other) : on_down(other.on_down), on_up(other.on_up)
{

}

events::event<Controllable&, SDL_KeyboardEvent>& Controllable::on_keyboard_down()
{
    return on_down;
}
events::event<Controllable&, SDL_KeyboardEvent>& Controllable::on_keyboard_up()
{
    return on_up;
}

void Controllable::press(const SDL_KeyboardEvent& data)
{
    if (data.type == SDL_KEYDOWN)
        on_down(*this, data);
    else if (data.type == SDL_KEYUP)
        on_up(*this, data);
}
