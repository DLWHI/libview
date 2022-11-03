#ifndef LV_CANVAS_H_
#define LV_CANVAS_H_

#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL_render.h>
#include "invokable.h"

struct SDL_MouseButtonEvent;
struct SDL_KeyboardEvent;

namespace view
{
    class BaseElement;
    class Clickable;
    class Controllable;

    class Canvas
    {
        public:
            Canvas(SDL_Window* window);
            Canvas(const Canvas& other);
            ~Canvas();
            
            BaseElement& get_element(const std::string& name);
            Clickable& get_clickable(const std::string& name);
            Controllable& get_controllable(const std::string& name);

            BaseElement& get_element(uint16_t id);
            Clickable& get_clickable(uint16_t id);
            Controllable& get_controllable(uint16_t id);

            BaseElement& push_element(const BaseElement& el, const std::string& id);
            void remove_element(uint16_t id);
        private:
            friend class Window;

            uint32_t render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
            SDL_Renderer *renderer;

            int32_t w;
            int32_t h;

            std::vector<BaseElement*> elements;
            std::vector<Controllable*> controllables;
            uint16_t** index_buffer; // holds only clickables

            void draw(const SDL_Color& bg_color);

            void refresh_index_buffer(uint32_t nw, uint32_t nh);
            void refresh_index_buffer(BaseElement& element, SDL_Rect size);
            void refresh_element(BaseElement& sender);

            void invoke_click(SDL_MouseButtonEvent data);
            void invoke_keypress(SDL_KeyboardEvent data);
    };
}
#endif
