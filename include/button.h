#ifndef LV_BUTTON_H_
#define LV_BUTTON_H_

#include "border.h"
#include "text.h"
#include "clickable.h"

struct SDL_Texture;

namespace view
{
    class Button: public Text, public Clickable
    {
        public:
            Button();
            Button(const Button& other);

            BaseElement* clone(const std::string& id) const;
    };
}
#endif
