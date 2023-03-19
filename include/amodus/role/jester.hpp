#pragma once

namespace amodus
{
    class jester : au::player
    {
    public:
        jester(amodus::core& core) : core_{ core } {}

    private:
        amodus::core core_;
    };
} // auv