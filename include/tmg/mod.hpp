#pragma once

#include <au/mod.hpp>
#include <tmg/tusmo.hpp>

namespace tmg
{
    class mod : public au::mod
    {
    public:
        mod(ark::mod_api&);

        void on_enable() override;
        void on_draw() override;
        void on_settings_update() override;

        void hook();

    private:
        tmg::tusmo tusmo_;

        float killtimer_reduction_multiplier_ = 1.f;
    };
} // tmg