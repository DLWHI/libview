#ifndef LV_CLICKABLE_H_
#define LV_CLICKABLE_H_

#include "invokable.h"

struct SDL_MouseButtonEvent;

namespace view
{
    class Clickable
    {
        public:
            Clickable() = default;
            Clickable(const Clickable& other);
            virtual ~Clickable() = default;

            events::event<Clickable&, SDL_MouseButtonEvent>& on_mouse_button_down();
            events::event<Clickable&, SDL_MouseButtonEvent>& on_mouse_button_up();
        protected:
            friend class Canvas; // maybe not so good solution to invoke clicks

            events::invokable<Clickable&, SDL_MouseButtonEvent> on_mb_down;
            events::invokable<Clickable&, SDL_MouseButtonEvent> on_mb_up;

            void click(const SDL_MouseButtonEvent& data);
    };
}
#endif
