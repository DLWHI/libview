#include "window.h"
#include "elements.h"
#include "base_elements.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

#ifndef IMG_TYPES
#define IMG_TYPES IMG_INIT_PNG
#endif

namespace
{
    class Initializer
    {
        public:
            Initializer()
            {
                if (SDL_Init(SDL_INIT_EVERYTHING))
                    throw std::runtime_error(SDL_GetError());
                if ((IMG_Init(IMG_TYPES) & IMG_TYPES) != IMG_TYPES)
                    throw std::runtime_error(IMG_GetError());
                if (TTF_Init())
                    throw std::runtime_error(TTF_GetError());
            };
            ~Initializer()
            {
                TTF_Quit();
                IMG_Quit();
                SDL_Quit();
            };
    };
    
    Initializer i;
}
