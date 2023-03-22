#pragma once

#include <il2cpp/core.hpp>

#include <cstddef>
#include <cstdint>
#include <type_traits>

using Il2CppChar = uint16_t;

namespace il2cpp
{
    template <class T>
    struct array {
        il2cpp::Il2CppObject obj;
        il2cpp::Il2CppArrayBounds* bounds;
        il2cpp::il2cpp_array_size_t max_length;
        T* m_Items;

        using value_type = T*;

        value_type* begin() { return &m_Items; }

        value_type* end() { return &m_Items + size(); }

        std::size_t size() const { return static_cast<std::size_t>(max_length); }

        value_type& get(std::size_t index) {
            assert(index <= size());
            return begin()[index];
        }

        value_type& operator[](std::size_t index) { return get(index); }
    };

    struct string {
        il2cpp::Il2CppObject obj;
        int32_t length;
        uint16_t* chars;
    };
}