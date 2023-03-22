// global header
#include <cstdint>
#include <cs/string.hpp>
#include <cs/array.hpp>
//#include <cs/list.hpp>

#include <il2cpp/api.hpp>

#define ark_meta(NS, Name, Type) \
static inline auto internal_ns = NS; \
static inline auto internal_name = Name; \
static inline auto internal_type = Type; \
static inline auto internal_fullname = []{ return ((NS) == nullptr) ? (Name) : NS "." Name; }()

#define method_call(Klass, ReturnType, ArgTypes, Args) il2cpp::call<ReturnType(*)ArgTypes>Args
#define static_method_call(Klass, ReturnType, ArgTypes, Args) il2cpp::call<ReturnType(*)ArgTypes>Args
#define method_rva(RVA, Klass, ReturnType, FunctionName, ...) \
template<> inline uintptr_t rva<static_cast<ReturnType(Klass::*)(__VA_ARGS__)>( &Klass::FunctionName)>() { return RVA; }
#define method_static_rva(RVA, Klass, ReturnType, FunctionName, ...) \
template<> inline uintptr_t rva<static_cast<ReturnType(*)(__VA_ARGS__)>( &Klass::FunctionName)>() { return RVA; }

#define field_static(Klass, Type, Field) static Type Field();
#define field_static_impl(Klass, Type, Field) Type Klass::Field() { return reinterpret_cast<internal_statics*>(il2cpp::api::template get_class<Klass>()->static_fields)->Field; }

// windows macro, generated files use this identifier
#undef DECIMAL_NEG