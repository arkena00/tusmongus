#pragma once

#include <au/player.hpp>

namespace amodus
{
    class player : public au::player
    {
    public:
        void on_set_name(const std::string& name)
        {
            //if (name == "Arkena") set_color(0xFF0000);
        }

        void on_begin_play()
        {

        }

    private:
        //amodus::role role_;
    };
}