#pragma once

#include <ark/module.hpp>

namespace ark
{
    ARK_SHARED uintptr_t base_address();

    namespace method_info
    {
        template<auto Method>
        inline const char* name();

        template<auto Method>
        uintptr_t rva();
    } // method_info
} // ark