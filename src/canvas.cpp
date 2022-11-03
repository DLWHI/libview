#include "../include/canvas.h"
#include <stdexcept>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "../include/anchored_element.h"
#include "../include/clickable.h"
#include "../include/controllable.h"

using namespace view;

//----------constructors----------
Canvas::Canvas(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (!renderer)
        return;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_GetWindowSize(window, &w, &h);

    index_buffer = new uint16_t*[w];
    index_buffer[0] = new uint16_t[w*h];
    for (int i = 1; i < w; i++)
        index_buffer[i] = index_buffer[i - 1] + h;
    for (uint32_t i = 0; i < h; i++)
        for (uint32_t j = 0; j < w; j++)
            index_buffer[j][i] = 0;
}
Canvas::Canvas(const Canvas& other)
{

}
Canvas::~Canvas()
{
    delete[] index_buffer[0];
    delete[] index_buffer;
    for (auto i = elements.begin(); i != elements.end(); i++)
        delete *i;
    SDL_DestroyRenderer(renderer);
}

//----------interface----------
BaseElement& Canvas::get_element(const std::string& name)
{
    for (auto i = elements.begin(); i != elements.end(); i++)
        if ((*i)->get_name() == name)
            return **i;
    throw std::runtime_error("No element with such name, abort");
}
Clickable& Canvas::get_clickable(const std::string& name)
{
    for (auto i = elements.begin(); i != elements.end(); i++)
        if ((*i)->get_name() == name)
            return *dynamic_cast<Clickable*>(*i);
    throw std::runtime_error("No clickable element with such name, abort");
}
Controllable& Canvas::get_controllable(const std::string& name)
{
    for (auto i = elements.begin(); i != elements.end(); i++)
        if ((*i)->get_name() == name)
            return *dynamic_cast<Controllable*>(*i);
    throw std::runtime_error("No controllable element with such name, abort");
}

BaseElement& Canvas::get_element(uint16_t id)
{
    return *elements[id];
}
Clickable& Canvas::get_clickable(uint16_t id)
{
    return *dynamic_cast<Clickable*>(elements[id]);
}
Controllable& Canvas::get_controllable(uint16_t id)
{
    return *dynamic_cast<Controllable*>(elements[id]);
}

BaseElement& Canvas::push_element(const BaseElement& el, const std::string& id)
{
    elements.push_back(el.clone(id));
    elements.back()->id = elements.size();
    elements.back()->build_texture_cache(renderer);
    elements.back()->on_view_change() += std::bind(refresh_element, this, std::placeholders::_1);

    if (dynamic_cast<Clickable*>(elements.back()))
    {
        elements.back()->on_resize() += std::bind(static_cast<void(Canvas::*)(BaseElement&, SDL_Rect)>(refresh_index_buffer), this, 
                                                  std::placeholders::_1, std::placeholders::_2);
        SDL_Rect pos = elements.back()->get_dim();
        for (uint32_t i = pos.y; i < pos.y + pos.h && 0 <= i && i < h; i++)
            for (uint32_t j = pos.x; j < pos.x + pos.w && 0 <= j && j < w; j++)
                index_buffer[j][i] = elements.back()->id;
    }

    if (dynamic_cast<Controllable*>(elements.back()))
        controllables.push_back(dynamic_cast<Controllable*>(elements.back()));
    return *elements.back();
}
void Canvas::remove_element(uint16_t id)
{
    delete elements[id];
    elements.erase(elements.begin() + id);
}
//----------canvas-state----------
void Canvas::refresh_index_buffer(uint32_t nw, uint32_t nh)
{
    delete[] index_buffer[0];
    delete[] index_buffer;

    w = nw;
    h = nh;

    index_buffer = new uint16_t*[w];
    index_buffer[0] = new uint16_t[w*h];
    for (int i = 1; i < w; i++)
        index_buffer[i] = index_buffer[i - 1] + h;

    for (uint32_t i = 0; i < h; i++)
        for (uint32_t j = 0; j < w; j++)
            index_buffer[j][i] = 0;
    for (uint16_t it = 0; it != elements.size(); it++)
    {
        SDL_Rect pos = elements[it]->get_dim();
        for (uint32_t i = pos.y; i < pos.y + pos.h && 0 <= i && i < h; i++)
            for (uint32_t j = pos.x; j < pos.x + pos.w && 0 <= j && j < w; j++)
                index_buffer[j][i] = it + 1;
    }
}
void Canvas::refresh_index_buffer(BaseElement& element, SDL_Rect size)
{
    SDL_Rect pos = element.get_dim();
    for (uint32_t i = pos.y; i < pos.y + pos.h && 0 <= i && i < h; i++)
        for (uint32_t j = pos.x; j < pos.x + pos.w && 0 <= j && j < w; j++)
            index_buffer[j][i] = 0;
    for (uint32_t i = size.y; i < size.y + size.h && 0 <= i && i < h; i++)
        for (uint32_t j = size.x; j < size.x + size.w && 0 <= j && j < w; j++)
            index_buffer[j][i] = element.id;
}

void Canvas::refresh_element(BaseElement& sender)
{
    sender.build_texture_cache(renderer);
}
//----------event-firing----------
void Canvas::invoke_click(SDL_MouseButtonEvent data)
{
    if (0 <= data.x && data.x < w && 0 <= data.y && data.y < h && index_buffer[data.x][data.y])
        dynamic_cast<Clickable*>(elements[index_buffer[data.x][data.y] - 1])->click(data);
}
void Canvas::invoke_keypress(SDL_KeyboardEvent data)
{
    for (auto i = controllables.begin(); i != controllables.end(); i++)
        (*i)->press(data);
}
//----------render----------
void Canvas::draw(const SDL_Color& bg_color)
{
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);
    for (uint16_t i = 0; i < elements.size(); i++)
        elements[i]->draw(renderer);
    SDL_RenderPresent(renderer);
}
