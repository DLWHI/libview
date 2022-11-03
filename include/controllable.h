#ifndef LV_CONTROLLABLE_H_
#define LV_CONTROLLABLE_H_

#include "invokable.h"

struct SDL_KeyboardEvent;

namespace view
{    
    class Controllable
    {
        public:
            Controllable() = default;
            Controllable(const Controllable& other);
            virtual ~Controllable() = default;

            events::event<Controllable&, SDL_KeyboardEvent>& on_keyboard_down();
            events::event<Controllable&, SDL_KeyboardEvent>& on_keyboard_up();
        protected:
            friend class Canvas; // maybe not so good solution to invoke key presses

            events::invokable<Controllable&, SDL_KeyboardEvent> on_down;
            events::invokable<Controllable&, SDL_KeyboardEvent> on_up;

            void press(const SDL_KeyboardEvent& data);
    };
}
#endif
