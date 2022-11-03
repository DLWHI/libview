#include "../include/window.h"
#include <stdexcept>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
using namespace view;

//----------constructors----------
Window::Window(std::string title, int w, int h , SDL_Surface* icon)
{
    window = SDL_CreateWindow(title.c_str(), 100, 100, w, h, window_flags);
    if (!window)
        return;
    SDL_SetWindowMinimumSize(window, 800, 600);
    if (icon)
        SDL_SetWindowIcon(window, icon);

    face = new Canvas(window);
    on_window_resize_event += std::bind(static_cast<void(Canvas::*)(uint32_t, uint32_t)>(Canvas::refresh_index_buffer), face, std::placeholders::_1, std::placeholders::_2);
}
Window::~Window()
{
    close_window();
}

//----------getters----------
WindowState Window::get_status() const
{
    return status;
}
SDL_Rect Window::get_dimensions() const
{
    SDL_Rect dim = {0, 0, 0, 0};
    SDL_GetWindowSize(window, &dim.w, &dim.h);
    return dim;
}
std::string Window::get_title() const
{
    return std::string(SDL_GetWindowTitle(window));
}
uint16_t Window::get_fps_limit() const
{
    return fps_limit;
}
//----------setters----------
void Window::set_icon(SDL_Surface* icon)
{
    SDL_SetWindowIcon(window, icon);
}
void Window::set_dimensions(int w, int h)
{
    SDL_SetWindowSize(window, w, h);
}
void Window::set_title(const std::string& title)
{
    SDL_SetWindowTitle(window, title.c_str());
}
void Window::set_fps_limit(uint16_t limit)
{
    fps_limit = limit;
}
//----------events----------
events::event<uint32_t, uint32_t>& Window::on_window_resize()
{
    return on_window_resize_event;
}
events::event<>& Window::on_window_close()
{
    return on_window_close_event;
}
events::event<>& Window::on_window_open()
{
    return on_window_open_event;
}
events::event<SDL_KeyboardEvent>& Window::on_button()
{
    return on_button_event;
}
//----------element-interface----------
Canvas& Window::canvas()
{
    if (status == WindowState::Closed)
        throw std::runtime_error("Accessing closed canvas on window");
    return *face;
}

//----------functionality----------
void Window::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            close_window();
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                on_window_resize_event(get_dimensions().w, get_dimensions().h);
            else if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                close_window();
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
            on_click_event(event.button);
            face->invoke_click(event.button);
        }
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            on_button_event(event.key);
            face->invoke_keypress(event.key);
        }
    }
    draw();
}

void Window::close_window()
{
    if (status == WindowState::Closed)
        return;
    on_window_close_event();
    SDL_DestroyWindow(window);
    delete face;
    status = WindowState::Closed;
}
//----------drawing----------
void Window::draw()
{
    if (status == WindowState::Closed)
        return;
    face->draw(bg_color);
}

uint32_t Window::draw_callback(uint32_t interval, void* params)
{
    ((Window*)params)->draw();
    return interval;
}
