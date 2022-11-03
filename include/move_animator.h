#ifndef LV_MOVE_ANIMATOR_H_
#define LV_MOVE_ANIMATOR_H_

#include <string>
#include "animator.h"

namespace view
{
    class BaseElement;

    class MoveAnimator : public Animator
    {
        public:
            MoveAnimator(BaseElement& target, uint32_t v0[2] = nullptr, uint32_t a0[2] = nullptr) : bound_element(target) { };
            MoveAnimator(const MoveAnimator& other);
            ~MoveAnimator() = default;
        private:
            BaseElement& bound_element;

            uint32_t t = 0; // lifetime
            uint32_t v[2] = {0, 0}; // velocity
            uint32_t a[2] = {0, 0}; // acceleration

            void timed();
    };
}
#endif
