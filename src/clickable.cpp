#include "../include/clickable.h"
#include <SDL2/SDL_events.h>

using namespace view;

Clickable::Clickable(const Clickable& other) : on_mb_down(other.on_mb_down), on_mb_up(other.on_mb_up)
{

}

events::event<Clickable&, SDL_MouseButtonEvent>& Clickable::on_mouse_button_down()
{
    return on_mb_down;
}
events::event<Clickable&, SDL_MouseButtonEvent>& Clickable::on_mouse_button_up()
{
    return on_mb_up;
}

void Clickable::click(const SDL_MouseButtonEvent& data)
{
    if (data.type == SDL_MOUSEBUTTONDOWN)
        on_mb_down(*this, data);
    else if (data.type == SDL_MOUSEBUTTONUP)
        on_mb_up(*this, data);
}
