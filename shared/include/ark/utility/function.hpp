#pragma once

#include <functional>

namespace ark
{
    template<class T>
    struct function_trait : public function_trait<decltype(&std::decay_t<T>::operator())> {};

    template<class Class, class Return, class... Args>
    struct function_trait<Return(Class::*)(Args...) const> : function_trait<Return(Class::*)(Args...)>{};

    template<class Class, class Return, class... Args>
    struct function_trait<Return(Class::*)(Args...)> {
        using class_type = Class;
        using return_type = Return;
        using method_type = std::function<Return(Class*, Args...)>;
        using flat_method_type = Return(*)(Class*, Args...);
        using functional_type = Return(Args...);
        using overwrite_method_type = std::function<Return(flat_method_type, Class*, Args...)>;
    };
} // ark