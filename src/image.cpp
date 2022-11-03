#include "../include/image.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL_image.h>
using namespace view;

Image::Image(const Image& other) : BaseElement(other)
{
    img_file = other.img_file;
    filler = other.filler;
}
Image::Image(const std::string& file)
{
    img_file = file;
}
Image::~Image()
{
    SDL_DestroyTexture(texture);
}

void Image::set_image(const std::string& file)
{
    img_file = file;
    on_view_change_event(*this);
}
void Image::set_filler_color(const SDL_Color& color)
{
    filler = color;
    on_property_changed_event(*this, "filler_color");
}

std::string Image::get_image_file() const
{
    return img_file;
}
SDL_Color Image::get_filler_color() const
{
    return filler;
}

void Image::draw(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, filler.r, filler.g, filler.b, filler.a);
    if (texture)
        SDL_RenderCopy(ren, texture, nullptr, &dim);
    else
        SDL_RenderFillRect(ren, &dim);
}
void Image::build_texture_cache(SDL_Renderer* ren)
{
    SDL_DestroyTexture(texture);
    SDL_Surface* surf = IMG_Load(img_file.c_str());
    if (surf)
    {
        texture = SDL_CreateTextureFromSurface(ren, surf);
        SDL_FreeSurface(surf);
    }
}
BaseElement* Image::clone(const std::string& id) const
{
    Image* cl = new Image(*this);
    cl->name = id;
    return cl;
}
