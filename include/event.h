#ifndef EVENT_H_
#define EVENT_H_
#include <functional>
#include <list>

namespace events
{
    template <typename... Args>
    class event
    {
        public:
            void add(std::function<void(Args...)> func)
            {
                invoke_list.push_back(func);
            }
            void remove(std::function<void(Args...)> func)
            {
                for (auto i = invoke_list.rbegin(); i != invoke_list.rend(); i++)
                    if (get_address(func) == get_address(*i))
                    {
                        invoke_list.erase(--i.base());
                        return;
                    }
            }

            void operator+=(std::function<void(Args...)> func)
            {
                add(func);
            }
            void operator-=(std::function<void(Args...)> func)
            {
                remove(func);
            }
        protected:
            virtual ~event() = default;

            std::list<std::function<void(Args...)>> invoke_list;

            template <typename T, typename... U> // not my shit needs examination
            size_t get_address(std::function<T(U...)> f)
            {
                typedef T(fnType)(U...);
                fnType **fnPointer = f.template target<fnType *>();
                return (size_t)*fnPointer;
            }
    };
}
#endif
