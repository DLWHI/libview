#ifndef LV_TEXT_H_
#define LV_TEXT_H_
#include "border.h"
#include "image.h"
#include "text_renderer.h"
#include <string>

namespace view
{
    enum TextDisplay
    {
        NonOverflow,
        Overflow,
        Shrinked,
        Scrolled,
        Wrapped
    };

    class Text: public TextRenderer
    {
        public:
            Text() = default;
            Text(const std::string& text, const std::string& font_file, uint32_t size = 8);
            Text(const Text& other);
            ~Text() = default;

            void set_text(const std::string& txt);
            void set_display_type(TextDisplay type);
            void set_border_width(uint32_t w);
            void set_border_color(const SDL_Color& color);
            void set_background_image(const std::string& file);
            void set_background_color(const SDL_Color& color);

            std::string get_text() const;
            TextDisplay get_display_type() const;
            uint32_t get_border_width() const;
            SDL_Color get_border_color() const;
            std::string get_background_image() const;
            SDL_Color get_background_color() const;

            void draw(SDL_Renderer* ren);
            void build_texture_cache(SDL_Renderer* ren);
            BaseElement* clone(const std::string& id) const;
        protected:
            std::string text;
            bool overflow = true;
            TextDisplay display_type = TextDisplay::NonOverflow;
            SDL_Rect maximal_carriage = {0, 0, 0, 0};

            Image bg;
            Border border;

            void resize_carriage(BaseElement& sender, SDL_Rect size);
    };
}
#endif
