#ifndef LV_TEXT_RENDER_H_
#define LV_TEXT_RENDER_H_
#define SDL_MAIN_HANDLED
#include <string>
#include <SDL2/SDL_ttf.h>
#include "base_element.h"

namespace view
{
    // base class for all elements that draw text one way or the other
    class TextRenderer: public BaseElement
    {
        public:
            TextRenderer() = default;
            TextRenderer(const std::string& font_file, uint32_t size);
            TextRenderer(const TextRenderer& other);
            virtual ~TextRenderer();

            void open_font(const std::string& font_file, uint32_t size);

            void set_font(const std::string& file);
            void set_font_size(uint32_t size);
            void set_font_color(const SDL_Color& color);

            std::string get_font() const;
            uint32_t get_font_size() const;
            SDL_Color get_font_color() const;

            virtual void build_texture_cache(SDL_Renderer* ren);
        protected:
            SDL_Rect carriage = {0, 0, 0, 0};
            SDL_Color color = {0, 0, 0, 255};

            const SDL_Rect& get_stencil() const;

            void draw_glyph(char c, SDL_Renderer* ren, SDL_Rect size);
        private:
            TTF_Font* font = nullptr;
            std::string font_name;
            uint32_t font_size = 0;
            SDL_Texture* atlas_lower = nullptr;
            SDL_Texture* atlas_upper = nullptr;
            SDL_Texture* atlas_numbers = nullptr;
            SDL_Texture* atlas_punc = nullptr;
            SDL_Rect stencil = {0, 0, 0, 0};

            void build_atlas(SDL_Renderer* ren, SDL_Texture*& atlas, const char* chars);
    };
}
#endif
