#ifndef LV_WINDOW_H_
#define LV_WINDOW_H_

#include <map>
#include "canvas.h"
#include <SDL2/SDL_timer.h>

struct SDL_MouseButtonEvent;
struct SDL_KeyboardEvent;

namespace view
{
    enum WindowState
    {
        Open,
        Closed
    };

    struct WindowPosition
    {
        SDL_Rect rect;
        bool absolute;
    };

    class Window
    {
        public:
            Window(std::string title = "window", int w = 800, int h = 600, SDL_Surface* icon = nullptr);
            ~Window();

            SDL_Color bg_color = {0, 0, 0, 0xff};

            WindowState get_status() const;
            SDL_Rect get_dimensions() const;
            std::string get_title() const;
            uint16_t get_fps_limit() const;

            void set_icon(SDL_Surface* icon);
            void set_dimensions(int w, int h);
            void set_title(const std::string& title);
            void set_fps_limit(uint16_t limit);

            void update();

            Canvas& canvas();

            events::event<uint32_t, uint32_t>& on_window_resize();
            events::event<>& on_window_open();
            events::event<>& on_window_close();
            events::event<SDL_KeyboardEvent>& on_button();
            events::event<SDL_MouseButtonEvent>& on_click();
        private:
            uint32_t window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
            WindowState status = WindowState::Open;
            SDL_Window *window;

            Canvas* face;

            uint16_t fps_limit = 0;
            SDL_TimerID draw_coroutine_id = 0;

            events::invokable<uint32_t, uint32_t> on_window_resize_event;
            events::invokable<> on_window_open_event;
            events::invokable<> on_window_close_event;
            events::invokable<SDL_KeyboardEvent> on_button_event;
            events::invokable<SDL_MouseButtonEvent> on_click_event;

            void draw();
            static uint32_t draw_callback(uint32_t interval, void* params);

            void close_window();
    };
}
#endif
