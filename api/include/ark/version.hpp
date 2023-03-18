#pragma once

#include <string>

namespace ark
{
    struct version
    {
        std::uint32_t major = 0;
        std::uint32_t minor = 0;
        std::uint32_t fix = 0;

        std::string str() const { return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(fix); }

        bool compatible_with(ark::version rhs) const
        {
            return major == rhs.major && minor == rhs.minor;
        }
    };
} // ark