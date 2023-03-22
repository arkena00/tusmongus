#pragma once

#include <ark/meta.hpp>

#include <Windows.h>
#include <bit>
#include <cstddef>
#include <cstdint>

namespace il2cpp
{
    using Il2CppMethodPointer = void(*)();

    template <class Signature, class... Args>
    inline auto call(uintptr_t rva, Args&&... args)
    {
        auto address = ark::base_address() + rva;
        auto function = std::bit_cast<Signature>(reinterpret_cast<il2cpp::Il2CppMethodPointer>(address));
        return function(args...);
    }

    struct Il2CppImage;
    struct Il2CppThread;
    struct Il2CppAssembly;
    struct Il2CppClass;
    struct Il2CppArray;
    struct MethodInfo;
    struct ParameterInfo;
    struct Il2CppTypeDefinition;
    struct Il2CppMethodDefinition;

    struct Il2CppDomain
    {
        struct Il2CppAppDomain* domain;
        struct Il2CppAppDomainSetup* setup;
        struct Il2CppAppContext* default_context;
        const char* friendly_name;
        uint32_t domain_id;
        volatile int threadpool_jobs;
        void* agent_info;
    };

    struct VirtualInvokeData
    {
        Il2CppMethodPointer methodPtr;
        const MethodInfo* method;
    };

    struct Il2CppType
    {
        void* data;
        unsigned int bits;
    };

    struct Il2CppObject
    {
        Il2CppClass *klass;
        void *monitor;
    };

    union Il2CppRGCTXData
    {
        void* rgctxDataDummy;
        const MethodInfo* method;
        const Il2CppType* type;
        Il2CppClass* klass;
    };

    struct Il2CppClass_1
    {
        void* image;
        void* gc_desc;
        const char* name;
        const char* namespaze;
        Il2CppType byval_arg;
        Il2CppType this_arg;
        Il2CppClass* element_class;
        Il2CppClass* castClass;
        Il2CppClass* declaringType;
        Il2CppClass* parent;
        void* generic_class;
        const Il2CppTypeDefinition* typeDefinition;
        void* interopData;
        Il2CppClass* klass;
        void* fields;
        void* events;
        void* properties;
        void* methods;
        Il2CppClass** nestedTypes;
        Il2CppClass** implementedInterfaces;
        void* interfaceOffsets;
    };

    struct Il2CppClass_2
    {
        Il2CppClass** typeHierarchy;
        void *unity_user_data;
        uint32_t initializationExceptionGCHandle;
        uint32_t cctor_started;
        uint32_t cctor_finished;
        size_t cctor_thread;
        int32_t genericContainerIndex;
        uint32_t instance_size;
        uint32_t actualSize;
        uint32_t element_size;
        int32_t native_size;
        uint32_t static_fields_size;
        uint32_t thread_static_fields_size;
        int32_t thread_static_fields_offset;
        uint32_t flags;
        uint32_t token;
        uint16_t method_count;
        uint16_t property_count;
        uint16_t field_count;
        uint16_t event_count;
        uint16_t nested_type_count;
        uint16_t vtable_count;
        uint16_t interfaces_count;
        uint16_t interface_offsets_count;
        uint8_t typeHierarchyDepth;
        uint8_t genericRecursionDepth;
        uint8_t rank;
        uint8_t minimumAlignment;
        uint8_t naturalAligment;
        uint8_t packingSize;
        uint8_t bitflags1;
        uint8_t bitflags2;
    };

    struct Il2CppClass
    {
        Il2CppClass_1 _1;
        void* static_fields;
        Il2CppRGCTXData* rgctx_data;
        Il2CppClass_2 _2;
        VirtualInvokeData vtable[255];
    };

    struct Il2CppGenericInst
    {
        uint32_t type_argc;
        const Il2CppType** type_argv;
    };
    struct Il2CppGenericContext
    {
        const Il2CppGenericInst* class_inst;
        const Il2CppGenericInst* method_inst;
    };

    struct Il2CppGenericClass
    {
        /*TypeDefinitionIndex*/ int32_t typeDefinitionIndex;
        Il2CppGenericContext context;
        Il2CppClass* cached_class;
    };

    typedef uintptr_t il2cpp_array_size_t;
    typedef int32_t il2cpp_array_lower_bound_t;
    struct Il2CppArrayBounds
    {
        il2cpp_array_size_t length;
        il2cpp_array_lower_bound_t lower_bound;
    };

    struct FieldInfo
    {
        const char* name;
        const Il2CppType* type;
        Il2CppClass* parent;
        int32_t offset;
        uint32_t token;
    };

    struct MethodInfo
    {
        Il2CppMethodPointer methodPointer;
        void* invoker_method;
        const char* name;
        Il2CppClass *klass;
        const Il2CppType *return_type;
        const ParameterInfo* parameters;
        union
        {
            const Il2CppRGCTXData* rgctx_data;
            const Il2CppMethodDefinition* methodDefinition;
        };
        union
        {
            const void* genericMethod;
            const void* genericContainer;
        };
        uint32_t token;
        uint16_t flags;
        uint16_t iflags;
        uint16_t slot;
        uint8_t parameters_count;
        uint8_t bitflags;
    };

    struct ParameterInfo
    {
        const char* name;
        int32_t position;
        uint32_t token;
        const Il2CppType* parameter_type;
    };

    struct Il2CppTypeDefinition
    {
        int32_t  nameIndex;
        int32_t  namespaceIndex;
        int32_t  byvalTypeIndex ;
        int32_t  declaringTypeIndex;
        int32_t  parentIndex;
        int32_t  elementTypeIndex;
        int32_t  genericContainerIndex;
        uint32_t flags;
        int32_t  fieldStart;
        int32_t  methodStart;
        int32_t  eventStart;
        int32_t  propertyStart;
        int32_t  nestedTypesStart;
        int32_t  interfacesStart;
        int32_t  vtableStart;
        int32_t  interfaceOffsetsStart;
        uint16_t method_count;
        uint16_t property_count;
        uint16_t field_count;
        uint16_t event_count;
        uint16_t nested_type_count;
        uint16_t vtable_count;
        uint16_t interfaces_count;
        uint16_t interface_offsets_count;
        uint32_t bitfield;
        uint32_t token;
    };

    struct Il2CppMethodDefinition
    {
        uint32_t nameIndex;
        uint32_t declaringType;
        uint32_t returnType;
        uint32_t parameterStart;
        uint32_t genericContainerIndex;
        uint32_t token;
        uint16_t flags;
        uint16_t iflags;
        uint16_t slot;
        uint16_t parameterCount;
    };

    static constexpr auto TYPE_END = 0x00;       /* End of List */
    static constexpr auto TYPE_VOID = 0x01;
    static constexpr auto TYPE_BOOLEAN = 0x02;
    static constexpr auto TYPE_CHAR = 0x03;
    static constexpr auto TYPE_I1 = 0x04;
    static constexpr auto TYPE_U1 = 0x05;
    static constexpr auto TYPE_I2 = 0x06;
    static constexpr auto TYPE_U2 = 0x07;
    static constexpr auto TYPE_I4 = 0x08;
    static constexpr auto TYPE_U4 = 0x09;
    static constexpr auto TYPE_I8 = 0x0a;
    static constexpr auto TYPE_U8 = 0x0b;
    static constexpr auto TYPE_R4 = 0x0c;
    static constexpr auto TYPE_R8 = 0x0d;
    static constexpr auto TYPE_STRING = 0x0e;
    static constexpr auto TYPE_PTR = 0x0f;       /* arg: <type> token */
    static constexpr auto TYPE_BYREF = 0x10;       /* arg: <type> token */
    static constexpr auto TYPE_VALUETYPE = 0x11;       /* arg: <type> token */
    static constexpr auto TYPE_CLASS = 0x12;       /* arg: <type> token */
    static constexpr auto TYPE_VAR = 0x13;       /* Generic parameter in a generic type definition, represented as number (compressed unsigned integer) number */
    static constexpr auto TYPE_ARRAY = 0x14;       /* type, rank, boundsCount, bound1, loCount, lo1 */
    static constexpr auto TYPE_GENERICINST = 0x15;     /* <type> <type-arg-count> <type-1> \x{2026} <type-n> */
    static constexpr auto TYPE_TYPEDBYREF = 0x16;
    static constexpr auto TYPE_I = 0x18;
    static constexpr auto TYPE_U = 0x19;
    static constexpr auto TYPE_FNPTR = 0x1b;        /* arg: full method signature */
    static constexpr auto TYPE_OBJECT = 0x1c;
    static constexpr auto TYPE_SZARRAY = 0x1d;       /* 0-based one-dim-array */
    static constexpr auto TYPE_MVAR = 0x1e;       /* Generic parameter in a generic method definition; represented as number (compressed unsigned integer)  */
    static constexpr auto TYPE_CMOD_REQD = 0x1f;       /* arg: typedef or typeref token */
    static constexpr auto TYPE_CMOD_OPT = 0x20;       /* optional arg: typedef or typref token */
    static constexpr auto TYPE_INTERNAL = 0x21;       /* CLR internal type */

    static constexpr auto TYPE_MODIFIER = 0x40;       /* Or with the following types */
    static constexpr auto TYPE_SENTINEL = 0x41;       /* Sentinel for varargs method signature */
    static constexpr auto TYPE_PINNED = 0x45;       /* Local var that points to pinned object */

    static constexpr auto TYPE_ENUM = 0x55;        /* an enumeration */

    //

    static constexpr int FIELD_ATTRIBUTE_FIELD_ACCESS_MASK = 0x0007;
    static constexpr int FIELD_ATTRIBUTE_COMPILER_CONTROLLED = 0x0000;
    static constexpr int FIELD_ATTRIBUTE_PRIVATE = 0x0001;
    static constexpr int FIELD_ATTRIBUTE_FAM_AND_ASSEM = 0x0002;
    static constexpr int FIELD_ATTRIBUTE_ASSEMBLY = 0x0003;
    static constexpr int FIELD_ATTRIBUTE_FAMILY = 0x0004;
    static constexpr int FIELD_ATTRIBUTE_FAM_OR_ASSEM = 0x0005;
    static constexpr int FIELD_ATTRIBUTE_PUBLIC = 0x0006;

    static constexpr int FIELD_ATTRIBUTE_STATIC = 0x0010;
    static constexpr int FIELD_ATTRIBUTE_INIT_ONLY = 0x0020;
    static constexpr int FIELD_ATTRIBUTE_LITERAL = 0x0040;

    /*
     * Method Attributes (22.1.9)
     */
    static constexpr int METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK = 0x0007;
    static constexpr int METHOD_ATTRIBUTE_COMPILER_CONTROLLED = 0x0000;
    static constexpr int METHOD_ATTRIBUTE_PRIVATE = 0x0001;
    static constexpr int METHOD_ATTRIBUTE_FAM_AND_ASSEM = 0x0002;
    static constexpr int METHOD_ATTRIBUTE_ASSEM = 0x0003;
    static constexpr int METHOD_ATTRIBUTE_FAMILY = 0x0004;
    static constexpr int METHOD_ATTRIBUTE_FAM_OR_ASSEM = 0x0005;
    static constexpr int METHOD_ATTRIBUTE_PUBLIC = 0x0006;

    static constexpr int METHOD_ATTRIBUTE_STATIC = 0x0010;
    static constexpr int METHOD_ATTRIBUTE_FINAL = 0x0020;
    static constexpr int METHOD_ATTRIBUTE_VIRTUAL = 0x0040;

    static constexpr int METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK = 0x0100;
    static constexpr int METHOD_ATTRIBUTE_REUSE_SLOT = 0x0000;
    static constexpr int METHOD_ATTRIBUTE_NEW_SLOT = 0x0100;

    static constexpr int METHOD_ATTRIBUTE_ABSTRACT = 0x0400;

    static constexpr int METHOD_ATTRIBUTE_PINVOKE_IMPL = 0x2000;

    /*
    * Type Attributes (21.1.13).
    */
    static constexpr int TYPE_ATTRIBUTE_VISIBILITY_MASK = 0x00000007;
    static constexpr int TYPE_ATTRIBUTE_NOT_PUBLIC = 0x00000000;
    static constexpr int TYPE_ATTRIBUTE_PUBLIC = 0x00000001;
    static constexpr int TYPE_ATTRIBUTE_NESTED_PUBLIC = 0x00000002;
    static constexpr int TYPE_ATTRIBUTE_NESTED_PRIVATE = 0x00000003;
    static constexpr int TYPE_ATTRIBUTE_NESTED_FAMILY = 0x00000004;
    static constexpr int TYPE_ATTRIBUTE_NESTED_ASSEMBLY = 0x00000005;
    static constexpr int TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM = 0x00000006;
    static constexpr int TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM = 0x00000007;


    static constexpr int TYPE_ATTRIBUTE_INTERFACE = 0x00000020;

    static constexpr int TYPE_ATTRIBUTE_ABSTRACT = 0x00000080;
    static constexpr int TYPE_ATTRIBUTE_SEALED = 0x00000100;

    static constexpr int TYPE_ATTRIBUTE_SERIALIZABLE = 0x00002000;

    /*
    * Flags for Params (22.1.12)
    */
    static constexpr int PARAM_ATTRIBUTE_IN = 0x0001;
    static constexpr int PARAM_ATTRIBUTE_OUT = 0x0002;
    static constexpr int PARAM_ATTRIBUTE_OPTIONAL = 0x0010;
} // il2cpp