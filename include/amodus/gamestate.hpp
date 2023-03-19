#pragma once

#include <au/gamestate.hpp>

namespace amodus
{
    class gamestate : public au::gamestate
    {
    public:
        void on_start_meeting(au::player& reporter) override
        {
            mod().log("amodus start meeting");
        }

        void on_begin_play()
        {
            //au::remote_call(&player::custom_kill, 0, 1);
        }

    private:
        //amodus::core& core_;
    };
} // auv