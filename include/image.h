#ifndef LV_IMAGE_H_
#define LV_IMAGE_H_
#include "base_element.h"

struct SDL_Texture;

namespace view
{
    class Image: public BaseElement
    {
        public:
            Image() = default;
            Image(const std::string& file);
            Image(const Image& other);
            ~Image();

            void set_image(const std::string& file);
            void set_filler_color(const SDL_Color& color);

            std::string get_image_file() const;
            SDL_Color get_filler_color() const;

            void draw(SDL_Renderer* ren);
            void build_texture_cache(SDL_Renderer* ren);
            BaseElement* clone(const std::string& id) const;
        private:
            std::string img_file;
            SDL_Texture* texture = nullptr;
            SDL_Color filler = {255, 0, 0, 255};
    };
}
#endif
