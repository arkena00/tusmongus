#include <au/mod.hpp>

#include <tmg/mod.hpp>

int mod_load(ark::mod_api& api)
{
    api.register_class<tmg::mod>();

    return 0;
}