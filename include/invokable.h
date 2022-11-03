#ifndef INVOKABLE_H_
#define INVOKABLE_H_
#include "event.h"

namespace events
{
    template <typename... Args>
    class invokable : public event<Args...>
    {
        public:
            void invoke(Args... params) const
            {
                for (auto i = this->invoke_list.begin(); i != this->invoke_list.end(); i++)
                    (*i)(params...);
            }

            void operator()(Args... params)
            {
                invoke(params...);
            }
    };
}
#endif
