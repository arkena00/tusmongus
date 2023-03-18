#pragma once

#include <array>
#include <string>
#include <variant>

namespace ark
{
    struct setting
    {
        using value_type = std::variant<std::string, bool, int, float>;

        setting(std::string name, const char* value, std::string description = "") : setting(std::move(name), std::string(value), std::move(description)) {}

        template<class T>
        setting(std::string name, T value, std::string description = "")
            : name_{ std::move(name) }
            , value_{ std::move(value) }
            , description_{ std::move(description) }
        {
            std::visit([this](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::string>)
                {
                    std::get<std::string>(value_).reserve(64);
                }

            }, value_);
        }

        const std::string& name() const { return name_; }
        setting::value_type& value() { return value_; }
        const setting::value_type& value() const { return value_; }
        const std::string& description() const { return description_; }

        template<class T>
        T get() const { return std::get<T>(value_); }

        template<class T>
        void set(T value)
        {
            if constexpr (std::is_same_v<T, std::string>)
            {
                std::get<T>(value_).reserve(64);
            }
            std::get<T>(value_) = value;
        }

    private:
        std::string name_;
        setting::value_type value_;
        std::string description_;
    };
} // ark