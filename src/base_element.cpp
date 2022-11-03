#include "../include/base_element.h"

using namespace view;

BaseElement::BaseElement(const BaseElement& other)
{
    dim = other.dim;
    name = other.name;
}

std::string BaseElement::get_name() const
{
    return name;
}
SDL_Rect BaseElement::get_dim() const
{
    return dim;
}

void BaseElement::set_dim(const SDL_Rect& new_dim)
{
    on_resize_event(*this, new_dim);
    dim = new_dim;
}
void BaseElement::set_name(const std::string& new_name)
{
    name = new_name;
    on_property_changed_event(*this, "name");
}

void BaseElement::build_texture_cache(SDL_Renderer* ren)
{

}

events::event<BaseElement&>& BaseElement::on_view_change()
{
    return on_view_change_event;
}
events::event<BaseElement&, SDL_Rect>& BaseElement::on_resize()
{
    return on_resize_event;
}
events::event<BaseElement&, std::string>& BaseElement::on_property_changed()
{
    return on_property_changed_event;
}
