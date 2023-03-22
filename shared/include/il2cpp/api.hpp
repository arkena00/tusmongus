#pragma once

#include <ark/module.hpp>
#include <il2cpp/core.hpp>
#include <il2cpp/type.hpp>

namespace il2cpp
{
    class api;

    template<class T>
    auto build()
    {
        return il2cpp::api::template object_new<T>(api::template get_class<T>());
    }

    template<class T, class... Ts>
    T* make(Ts&&... ts)
    {
        auto obj = static_cast<T*>(il2cpp::api::object_new(api::template get_class<T>()));
        obj->ctor(std::forward<Ts>(ts)...);
        return obj;
    }

    template<class T, class... Ts>
    T* new_object(Ts&&... ts)
    {
        return static_cast<T*>(il2cpp::api::object_new(api::template get_class<T>()));
    }


    /*
    template<class T, class Fn, class... Ts>
    T* make_ctor(Fn fn, Ts&&... ts)
    {
        auto obj = static_cast<T*>(il2cpp::api::object_new(api::template get_class<T>()));
        std::invoke(fn, obj, std::forward<Ts>(ts)...);
        return obj;
    }*/

    template<class T>
    auto make_array(int size) { return reinterpret_cast<il2cpp::array<T>*>(il2cpp::api::array_new(api::template get_class<T>(), size)); }

    class api
    {
    public:
        #define ARK_MAKE_MEMBER
        #include <il2cpp/make_api.hpp>
        #undef ARK_MAKE_MEMBER

        template<class T>
        static inline il2cpp::Il2CppClass* get_class()
        {
            auto namespace_ = T::internal_ns;
            auto class_ = T::internal_name;

            auto dom = domain_get();

            std::size_t assembly_count = 0;
            const auto assemblies = domain_get_assemblies(dom, &assembly_count);

            Il2CppClass* cls = nullptr;

            for (auto it = assemblies; it != assemblies + assembly_count; ++it) {
                auto img = assembly_get_image(*it);
                if (!img)
                {
                    //spdlog::error("null assembly..");
                    continue;
                }

/*
                auto c = api::image_get_class_count(img);
                for (int i = 0; i < c; ++i)
                {
                    if(api::image_get_class(img, i)->_1.namespaze == std::string(""))
                    {
                        //ark_trace(": {} {}", api::image_get_class(img, i)->_1.name, api::image_get_class(img, i)->_1.namespaze);
                        auto v = il2cpp::api::type_get_assembly_qualified_name(il2cpp::api::class_get_type(api::image_get_class(img, i)));
                        std::cout << "\n__" << v;
                    }
                }*/

                cls = class_from_name(img, namespace_, class_);
                if (cls) break;
            }

            //if (cls == nullptr) spdlog::error("class not found {} in {}", class_, namespace_[0] ? namespace_ : "(none)");

            static auto klass = cls;
            return klass;
        }

        static auto test()
        {

            /*
            auto address = ark::base_address() + 0x1c52160;

            auto k = reinterpret_cast<il2cpp::Il2CppClass**>(address);
            ark_trace("k {}", (uintptr_t)k);
            ark_trace("k {}", (*k)->_1.name);*/

        }

        static void initialize()
        {
            #define ARK_MAKE_STATIC_INIT
            #include <il2cpp/make_api.hpp>
            #undef ARK_MAKE_STATIC_INIT
        }

    public:
        template<class T, class... Args>
        static decltype(auto) process(FARPROC function_address, Args&&... args)
        {
            return reinterpret_cast<T>(function_address)(std::forward<Args>(args)...);
        }

        #define ARK_MAKE_STATIC
        #include <il2cpp/make_api.hpp>
        #undef ARK_MAKE_STATIC
    };
} // il2cpp