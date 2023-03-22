#pragma once

#include <ark/class.hpp>
#include <cs/intptr.hpp>
#include <cs/string.hpp>

namespace cs
{
    struct string;

    struct type : ark::meta<type>
    {
        ark_meta("System", "Type", "");

        // RVA: 0x143DEE0 Offset: 0x143C6E0 VA: 0x1143DEE0 Slot: 3
        cs::string* ToString() { return method_call(ToString); }

	// RVA: 0x143CD50 Offset: 0x143B550 VA: 0x1143CD50
	static cs::type* GetType(cs::string* typeName, bool throwOnError = false, bool ignoreCase = true) { return static_method_call(type, GetType, typeName, throwOnError, ignoreCase); }

        // RVA: 0x143EB70 Offset: 0x143D370 VA: 0x1143EB70
	static cs::type* internal_from_handle(cs::IntPtr* handle) { return static_method_call(type, internal_from_handle, handle); }
    };

    template<class T>
    cs::type* get_type()
    {
        auto t = cs::type::GetType(cs::make_string(T::internal_type));
        if (!t) ark_trace("type not found: {}", T::internal_type);
        return t;
    }
}

namespace ark::method_info
{
    method_rva(cs::type::ToString, 0x143DEE0)
    method_rva(cs::type::GetType, 0x143CD50)
    method_rva(cs::type::internal_from_handle, 0x143EB70)
}