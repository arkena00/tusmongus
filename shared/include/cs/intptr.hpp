#pragma once

#include <ark/class.hpp>
#include <il2cpp/type.hpp>

namespace cs
{
    struct IntPtr : ark::meta<IntPtr>
    {
        ark_meta("System", "IntPtr", "");

        void* value; // 0x0
    };
}

namespace ark::method_info
{

}