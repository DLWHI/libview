#ifndef LV_ELEMENT_H_
#define LV_ELEMENT_H_

#include <string>
#include <SDL2/SDL_rect.h>
#include "invokable.h"

struct SDL_Renderer;

namespace view
{
    class BaseElement
    {
        public:
            BaseElement() = default;
            BaseElement(const BaseElement& other);
            virtual ~BaseElement() = default;

            bool displayed = true; // should element be rendered

            std::string get_name() const;
            SDL_Rect get_dim() const;

            void set_name(const std::string& new_name);
            void set_dim(const SDL_Rect& new_dim);

            events::event<BaseElement&>& on_view_change(); // f(sender)
            events::event<BaseElement&, SDL_Rect>& on_resize(); // f(sender, new_size)
            events::event<BaseElement&, std::string>& on_property_changed(); // f(sender, property_name)

            virtual void build_texture_cache(SDL_Renderer* ren); // if element caches textures this must set element to be ready for draw
            virtual void draw(SDL_Renderer* ren) = 0; // if pos_absolute = true then size = dim, otherwise user must specify drawing rect
            virtual BaseElement* clone(const std::string& id) const = 0; // clones element and sets specific id to clone
            // does not check for id equality hence it is not protected from collisions
        protected:
            friend class Canvas;
            uint16_t id; // used in view::Window

            SDL_Rect dim = {0, 0, 0, 0};
            std::string name; // name of the element, can be used to distinguish elements

            events::invokable<BaseElement&> on_view_change_event; // fires when there is need to rebuild texture cache
            events::invokable<BaseElement&, SDL_Rect> on_resize_event; // fires when set_dim() was called, before applying changes
            events::invokable<BaseElement&, std::string> on_property_changed_event; // fires when when changing any property, except resizing and texture changes
    };
}
#endif
