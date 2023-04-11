#pragma once

#include <au/mod.hpp>
#include <tmg/tusmo.hpp>

namespace tmg
{
    class mod : public au::mod
    {
    public:
        mod(ark::mod_api&);

        //void on_ui_initialize() override;
        void on_enable() override;
        void on_draw() override;

        void hook();

    private:
        tmg::tusmo tusmo_;

    };
} // tmg