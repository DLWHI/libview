#ifndef LV_ANIMATOR_H_
#define LV_ANIMATOR_H_

namespace view
{
    class BaseElement;

    class Animator
    {
        public:
            Animator() = default;
            Animator(const Animator& other) = default;
            ~Animator() = default;
        private:
            virtual void mouse_down() { };
            virtual void on_click() { };
            virtual void key_down() { };
            virtual void key_up() { };
            virtual void on_hover() { };
            virtual void timed() { };
    };
}
#endif
