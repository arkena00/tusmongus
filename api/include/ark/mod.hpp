#pragma once


/*
template<class... Ts>
void init(Ts&&... ts)
{
    if constexpr (std::is_base_of_v<Ts, au::player>)
    {
        mod.init_player(std::make_unique<Ts>());
    }
}*/



#include <ark/setting.hpp>
#include <ark/version.hpp>
#include <string>
#include <vector>

namespace ark
{
    struct mod_info
    {
        std::string name;
        ark::version version;
        std::string description;
    };

    class __declspec(dllimport) mod
    {
    public:

        using settings_type = std::vector<ark::setting>;

        void set_info(ark::mod_info info);
        void log(const std::string& data);
        const std::string& name() const;

        settings_type& settings();

        template<class... Ts>
        void add_setting(Ts&&... ts)
        {
            settings().emplace_back(std::move(ts)...);
        }
    };
} // ark


extern "C"
{
    __declspec(dllexport) int mod_load(ark::mod& mod);
}