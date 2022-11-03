#include "../include/button.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL_image.h>
using namespace view;

Button::Button()
{
    overflow = false;
}
Button::Button(const Button& other) : Text(other), Clickable(other)
{
    overflow = false;
}

BaseElement* Button::clone(const std::string& id) const
{
    Button* cl = new Button(*this);
    cl->name = id;
    return cl;
}
