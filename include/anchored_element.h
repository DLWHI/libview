#ifndef LV_ANCHORED_H_
#define LV_ANCHORED_H_

#include <SDL2/SDL_rect.h>
#include "base_element.h"

namespace view
{
    class AnchoredElement: public BaseElement
    {
        public:
            AnchoredElement() = default;
            AnchoredElement(const AnchoredElement& other);
            virtual ~AnchoredElement() = default;

            void set_anchors(const SDL_Rect& new_anchors);

            SDL_Rect get_anchors() const;

        protected:
            friend class Canvas;

            SDL_Rect anchors;

            void resize(uint32_t screen_w, uint32_t screen_h);
    };
}
#endif
