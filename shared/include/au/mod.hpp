#pragma once

#include <ark/mod.hpp>
#include <ark/hook.hpp>

#include <memory>
#include <functional>

namespace au
{
    class core;
    class gamestate;
    class player;

    class ARK_SHARED mod : public ark::mod
    {
    public:
        void register_gamestate(std::function<std::unique_ptr<au::gamestate>()> make_gamestate);
        void register_player(std::function<std::unique_ptr<au::player>()> make_player);

        template<class T>
        void register_class()
        {
            if constexpr (std::is_base_of_v<au::gamestate, T>) register_gamestate([]{ return std::make_unique<T>(); });
            else if constexpr (std::is_base_of_v<au::player, T>) register_player([]{ return std::make_unique<T>(); });
        }

        au::core& core();
    };
} // au

extern "C" ARK_EXPORT int mod_load(au::mod& mod);