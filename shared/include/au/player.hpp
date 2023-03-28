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

namespace au
{
    struct PlayerControl;
    class mod;
    class gamestate;

    class ARK_SHARED player
    {
    public:
        player(au::mod&, au::PlayerControl*);

        virtual void on_die(au::DeathReason reason, bool assignGhostRole) {}

        au::mod& mod();
        au::gamestate& gamestate();

        std::string name() const;
        au::PlayerControl* au_player() const;
        /*
        // rpc_server(set_color)
        void server_set_color(uint32_t hex_value)
        {
            // net_servercall(player, set_color)
            // netsend(server_set_color, hex_value);
            // network.send();
            // send(player.id, 99, rpc_id<&server_set_color>)
            //StartRpcImmediately(uint32_t targetNetId, uint8_t callId, Hazel::SendOption option, int32_t targetClientId)
        }
        void server_set_color_impl()
        {
            //au_player_->SetColor()
        }
        void set_color(uint32_t hex_value);*/

        static au::player& local();

    private:
        static std::unique_ptr<au::player> local_player;

        au::mod& mod_;
        au::PlayerControl* au_player_ = nullptr;

        friend class core;
    };
} // au