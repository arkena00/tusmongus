#pragma once

#include <string>

namespace au
{
    enum class DeathReason : int32_t
    {
        Exile
        , Kill
        , Disconnect
    };
} // au

#pragma once



namespace au
{
    class PlayerControl;
    class mod;
    class gamestate;

    struct ARK_SHARED player
    {
        virtual void on_die(au::DeathReason reason, bool assignGhostRole) {}

        au::mod& mod();
        au::gamestate& gamestate();

        std::string name() const;

    };
} // au