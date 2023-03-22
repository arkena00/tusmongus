#pragma once

#include <il2cpp/api.hpp>
#include <il2cpp/type.hpp>

namespace cs
{
    template<class T>
    struct array : il2cpp::array<T>
    {

    };

    template<class T>
    cs::array<T>* make_array(int size) { return static_cast<cs::array<T>*>(il2cpp::make_array<T>(size)); }

} // namespace cs