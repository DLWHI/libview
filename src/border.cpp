#include "../include/border.h"
#include <SDL2/SDL_render.h>
using namespace view;

Border::Border(const Border& other) : BaseElement(other)
{
    width = other.width;
    color = other.color;
}

SDL_Color Border::get_color() const
{
    return color;
}
uint32_t Border::get_width() const
{
    return width;
}

void Border::set_color(const SDL_Color& color)
{
    this->color = color;
    on_property_changed_event(*this, "color");
}
void Border::set_width(uint32_t w)
{
    width = w;
    on_property_changed_event(*this, "width");
}

void Border::draw(SDL_Renderer* ren)
{
    SDL_Rect rect = dim;
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    for (int i = 0; i < width; i++)
    {
        SDL_RenderDrawRect(ren, &rect);
        rect.x -= 1;
        rect.y -= 1;
        rect.w += 2;
        rect.h += 2;
    }
}
BaseElement* Border::clone(const std::string& id) const
{
    Border* cl = new Border(*this);
    cl->name = id;
    return cl;
}
