#pragma once

#include <ark/mod.hpp>

#include <memory>

namespace au
{
    class core;
    class gamestate;
    class player;

    class ARK_SHARED mod : public ark::mod
    {
    public:
        void register_player(std::unique_ptr<au::player> player);
        void register_gamestate(std::unique_ptr<au::gamestate> gamestate);

        template<class T>
        void register_class()
        {
            if constexpr (std::is_base_of_v<au::gamestate, T>) register_gamestate(std::make_unique<T>());
            else if constexpr (std::is_base_of_v<au::player, T>) register_player(std::make_unique<T>());
        }

        au::core& core();
    };
} // au

extern "C" ARK_EXPORT int mod_load(au::mod& mod);