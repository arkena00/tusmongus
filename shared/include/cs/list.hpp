#pragma once

#include <au/System/Collections/Generic/List.hpp>

namespace cs
{
    template<class T>
    struct list : System::Collections::Generic::List<T>
    {
        using base = cs::list<T>;
        using value_type = T*;

        value_type* begin() {
            return &base::_items->m_Items;
        }

        value_type* end() {
            return &base::_items->m_Items + size();
        }

        std::size_t size() const {
            return static_cast<std::size_t>(base::_size);
        }

        value_type& operator[](std::size_t index) {
            assert(index <= size());
            return begin()[index];
        }
    };

    template<class T>
    cs::list<T>& as_list(System::Collections::Generic::List<T>* list)
    {
        return *static_cast<cs::list<T>*>(list);
    }
} // cs