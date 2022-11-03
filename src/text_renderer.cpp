#include "../include/text_renderer.h"
#include <stdexcept>

using namespace view;


const std::string letters = "abcdefghijklmnopqrstuvwxyz";
const std::string letters_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string numbers = "0123456789#";
const std::string punctuation = ".:,;\'\"(!?)+-*/^<>~`\\=@";
//----------constructors----------
TextRenderer::TextRenderer(const std::string& font_file, uint32_t size)
{
    open_font(font_file, size);
}
TextRenderer::TextRenderer(const TextRenderer& other) : BaseElement(other)
{
    color = other.color;
    stencil = other.stencil;
    carriage = other.carriage;
    open_font(other.font_name, other.font_size);
}
TextRenderer::~TextRenderer()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(atlas_lower);
    SDL_DestroyTexture(atlas_upper);
    SDL_DestroyTexture(atlas_numbers);
    SDL_DestroyTexture(atlas_punc);
}

void TextRenderer::open_font(const std::string& font_file, uint32_t size)
{
    if (font)
        TTF_CloseFont(font);
    font_name = font_file;
    font_size = size;
    font = TTF_OpenFont(font_file.c_str(), size);
}
//----------getters----------
std::string TextRenderer::get_font() const
{
    return font_name;
}
uint32_t TextRenderer::get_font_size() const
{
    return font_size;
}
SDL_Color TextRenderer::get_font_color() const
{
    return color;
}

const SDL_Rect& TextRenderer::get_stencil() const
{
    return stencil;
}
//----------setters----------
void TextRenderer::set_font(const std::string& file)
{
    font_name = file;
    on_view_change_event(*this);
}
void TextRenderer::set_font_size(uint32_t size)
{
    font_size = size;
    on_view_change_event(*this);
}
void TextRenderer::set_font_color(const SDL_Color& color)
{
    this->color = color;
    on_view_change_event(*this);
}
//----------rendering----------
void TextRenderer::draw_glyph(char c, SDL_Renderer* ren, SDL_Rect size)
{
    if (!font)
        throw std::runtime_error("Using non initialized text renderer");
    SDL_Texture* atlas;
    size_t pos = 0;
    if ((pos = letters.find(c)) + 1)
        atlas = atlas_lower;
    else if ((pos = letters_upper.find(c)) + 1)
        atlas = atlas_upper;
    else if ((pos = numbers.find(c)) + 1)
        atlas = atlas_numbers;
    else if ((pos = punctuation.find(c)) + 1)
        atlas = atlas_punc;
    else
    {
        if (c == ' ')
            carriage.x += carriage.w;
        else if (c == '\n')
        {
            carriage.y += carriage.h;
            carriage.x = size.x;
        }
        return;
    }
    stencil.x = pos * stencil.w;
    SDL_RenderCopy(ren, atlas, &stencil, &carriage);
    carriage.x += carriage.w;
}

void TextRenderer::build_texture_cache(SDL_Renderer* ren)
{
    SDL_DestroyTexture(atlas_lower);
    SDL_DestroyTexture(atlas_upper);
    SDL_DestroyTexture(atlas_numbers);
    SDL_DestroyTexture(atlas_punc);

    build_atlas(ren, atlas_lower, letters.c_str());
    build_atlas(ren, atlas_upper, letters_upper.c_str());
    build_atlas(ren, atlas_numbers, numbers.c_str());
    build_atlas(ren, atlas_punc, punctuation.c_str());

    SDL_Surface* stencil_surface = TTF_RenderGlyph32_Blended(font, ',', color);
    SDL_Texture* stencil_texture = SDL_CreateTextureFromSurface(ren, stencil_surface);
    SDL_FreeSurface(stencil_surface);
    SDL_QueryTexture(stencil_texture, nullptr, nullptr, &stencil.w, &stencil.h);
    SDL_DestroyTexture(stencil_texture);
    carriage = stencil;
}
void TextRenderer::build_atlas(SDL_Renderer* ren, SDL_Texture*& atlas, const char* chars)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, chars, color);
    atlas = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
}
