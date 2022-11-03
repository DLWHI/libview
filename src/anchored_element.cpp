#include "../include/anchored_element.h"

using namespace view;

AnchoredElement::AnchoredElement(const AnchoredElement& other) : BaseElement(other)
{
    anchors = other.anchors;
}

void AnchoredElement::set_anchors(const SDL_Rect& new_anchors)
{
    dim.x = new_anchors.x*dim.x/anchors.x;
    dim.y = new_anchors.y*dim.y/anchors.y;
    dim.w = new_anchors.w*dim.w/anchors.w;
    dim.h = new_anchors.h*dim.x/anchors.h;
    anchors = new_anchors;
    on_resize_event(*this, dim);
}

SDL_Rect AnchoredElement::get_anchors() const
{
    return anchors;
}

void AnchoredElement::resize(uint32_t screen_w, uint32_t screen_h)
{
    dim.x = screen_w*anchors.x/100;
    dim.y = screen_h*anchors.y/100;
    dim.w = screen_w*anchors.w/100;
    dim.h = screen_h*anchors.h/100;
}
