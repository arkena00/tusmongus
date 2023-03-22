#pragma once

#include <ark/utility/encoding.hpp>
#include <il2cpp/api.hpp>
#include <il2cpp/core.hpp>

namespace cs
{
    struct string : il2cpp::Il2CppObject
    {
        std::int32_t m_stringLength;
        char16_t m_firstChar;


        std::u16string_view to_view() const { return { &m_firstChar, static_cast<std::size_t>(m_stringLength) }; }

        std::string str() const { return ::to_utf8(to_view()); }

        static cs::string* make(const std::string& data)
        {
            return reinterpret_cast<string*>(il2cpp::api::string_new_len(data.data(), data.size()));
        }
    };

    inline auto make_string(const std::string& data)
    {
        return reinterpret_cast<string*>(il2cpp::api::string_new_len(data.data(), data.size()));
    }
} // namespace cs