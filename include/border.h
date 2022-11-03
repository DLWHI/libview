#ifndef LV_BORDER_H_
#define LV_BORDER_H_
#include "base_element.h"

namespace view
{
    class Border: public BaseElement
    {
        public:
            Border() = default;
            Border(const Border& other);
            SDL_Color get_color() const;
            uint32_t get_width() const;

            void set_color(const SDL_Color& color);
            void set_width(uint32_t w);

            void draw(SDL_Renderer* ren);
            BaseElement* clone(const std::string& id) const;
        private:
            SDL_Color color = {0, 0, 0, 255};
            uint32_t width = 1;
    };
}
#endif
