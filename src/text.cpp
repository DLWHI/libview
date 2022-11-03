#include "../include/text.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL_image.h>

using namespace view;

//----------constructors----------
Text::Text(const std::string& text, const std::string& font_file, uint32_t size) : TextRenderer(font_file, size)
{
    this->text = text;
    on_resize_event += std::bind(resize_carriage, this, std::placeholders::_1, std::placeholders::_2);
}
Text::Text(const Text& other) : TextRenderer(other), border(other.border), bg(other.bg)
{
    text = other.text;
    display_type = other.display_type;
    on_resize_event += std::bind(resize_carriage, this, std::placeholders::_1, std::placeholders::_2);
}

BaseElement* Text::clone(const std::string& id) const
{
    Text* cl = new Text(*this);
    cl->name = id;
    return cl;
}
//----------getters----------
std::string Text::get_text() const
{
    return text;
}
TextDisplay Text::get_display_type() const
{
    return display_type;
}
uint32_t Text::get_border_width() const
{
    return border.get_width();
}
SDL_Color Text::get_border_color() const
{
    return border.get_color();
}
std::string Text::get_background_image() const
{
    return bg.get_image_file();
}
SDL_Color Text::get_background_color() const
{
    return bg.get_filler_color();
}
//----------setters----------
void Text::set_text(const std::string& txt)
{
    text = txt;
    resize_carriage(*this, dim);
    on_property_changed_event(*this, "text");
}
void Text::set_display_type(TextDisplay type)
{
    display_type = type;
    resize_carriage(*this, dim);
    on_property_changed_event(*this, "display");
}
void Text::set_border_width(uint32_t w)
{
    border.set_width(w);
    on_property_changed_event(*this, "border_width");
}
void Text::set_border_color(const SDL_Color& color)
{
    border.set_color(color);
    on_property_changed_event(*this, "border_color");
}
void Text::set_background_image(const std::string& file)
{
    bg.set_image(file);
    on_view_change_event(*this);
}
void Text::set_background_color(const SDL_Color& color)
{
    bg.set_filler_color(color);
    on_property_changed_event(*this, "bg_color");
}
//----------rendering----------
void Text::draw(SDL_Renderer* ren)
{
    bg.draw(ren);
    border.draw(ren);
    carriage.x = dim.x;
    carriage.y = dim.y;
    for (auto i = text.begin(); *i; i++)
    {
        if (carriage.x + carriage.w > dim.x + dim.w && *i != '\n')
        {
            if (display_type == TextDisplay::NonOverflow)
                continue;
            else if (display_type == TextDisplay::Wrapped)
                draw_glyph('\n', ren, dim);
        }
        draw_glyph(*i, ren, dim);
    }
}

void Text::build_texture_cache(SDL_Renderer* ren)
{
    TextRenderer::build_texture_cache(ren);
    bg.build_texture_cache(ren);
    maximal_carriage = carriage;
    resize_carriage(*this, dim);
}

void Text::resize_carriage(BaseElement& sender, SDL_Rect size)
{
    border.set_dim(dim);
    if (display_type == TextDisplay::Shrinked)
    {
        int32_t text_w = 0, text_h = 1;
        int32_t char_c = 0;
        for (auto i = text.begin(); *i; i++)
        {
            if (*i == '\n' && *i == '\0')
            {
                if (text_w < char_c)
                    text_w = char_c;
                char_c = 0;
                text_h++;
            } else
                char_c++;
        }
        if (text_w < char_c)
            text_w = char_c;

        carriage.h = std::min(size.h/text_h, maximal_carriage.h);
        if (text_w)
            carriage.w = std::min(size.w/text_w, maximal_carriage.w);
        else
            carriage.w = maximal_carriage.w;
    }
    else
        carriage = maximal_carriage;
}
