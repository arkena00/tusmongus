#pragma once

#include <ark/mod.hpp>
#include <ark/hook.hpp>

#include <memory>
#include <functional>

namespace au
{
    struct PlayerControl;
    class core;
    class gamestate;
    class player;

    class ARK_SHARED mod : public ark::mod
    {
    public:
        void register_gamestate(std::function<std::unique_ptr<au::gamestate>()> make_gamestate);
        void register_player(std::function<std::unique_ptr<au::player>(au::PlayerControl*)> make_player);

        template<class T>
        void register_class()
        {
            if constexpr (std::is_base_of_v<au::gamestate, T>) register_gamestate([this]{ return std::make_unique<T>(*this); });
            else if constexpr (std::is_base_of_v<au::player, T>) register_player([this](au::PlayerControl* au_player){ return std::make_unique<T>(*this, au_player); });
        }

        au::core& core();
    };
} // au

extern "C" ARK_EXPORT int mod_load(au::mod& mod);