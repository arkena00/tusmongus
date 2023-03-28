#pragma once

#include <au/core.hpp>
#include <au/player.hpp>

#include <gen/au/PlayerControl.hpp>

namespace amodus
{
    class player : public au::player
    {
    public:
        player(au::mod& mod, au::PlayerControl* au_player) : au::player(mod, au_player) {}

        void on_begin_play()
        {
        }

        /* void on_initialize(au::role role, params)
        {
            amodule::role::make(role_id, params);
            if (role_id == jester) return jester::make(params);
        } */

        void on_die(au::DeathReason reason, bool assignGhostRole) override
        {
            mod().log("on die {} {}", (int)reason, assignGhostRole);
            //role_->die();
        }

    private:
        //amodus::role role_;
    };
}