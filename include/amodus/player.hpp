#pragma once

#include <au/core.hpp>
#include <au/player.hpp>

namespace amodus
{
    class player : public au::player
    {
    public:
        void on_die(au::DeathReason reason, bool assignGhostRole) override
        {
            //mod().core().gamestate().endgame();
            mod().log("on die {} {}", (int)reason, assignGhostRole);
        }

    private:
        //amodus::role role_;
    };
}