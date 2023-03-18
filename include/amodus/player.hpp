#pragma once

#include <au/api/player.hpp>

struct mod
{
    mod(){}

    void set_player(au::player& player)
    {
        player_ = player;
        player_.init();
    }

    au::player player_;
};

namespace au
{
    struct player
    {
        au::PlayerControl* au_player_

        const std::string& name() const
        {
            return au_player()._cached.PlayerName;
        }

        void init()
        {
            au_player_ = au::PlayerControl;

            ark::hook<&au::PlayerControl::SetName>::before([this](auto&&, auto name){
                on_set_name(cs_tostd(name));
            });
            ark::hook<&au::PlayerControl::SetName>::after([this](auto&&, auto name){
                on_set_name(cs_tostd(name));
            });
        }

        void set_color(int v)
        {
            au_player_->SetColor(); // gen
        }

        virtual void on_set_name(const std::string& name) {}
    };
}

namespace amodus
{
    class player : au::player
    {
    public:
        void on_set_name(const std::string& name)
        {
            if (name == "Arkena") set_color(0xFF0000);
        }

        void on_begin_play()
        {

        }

    private:
        amodus::role role_;
    };
}