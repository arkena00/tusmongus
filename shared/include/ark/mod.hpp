#ifndef INCLUDE_ARKMOD_MOD_HPP_ARKENA_MOD
#define INCLUDE_ARKMOD_MOD_HPP_ARKENA_MOD

#include <ark/module.hpp>
#include <ark/setting.hpp>
#include <ark/version.hpp>

#include <vector>
#include <format>

namespace ark
{
    namespace ui { class core; }
    class core;

    struct mod_info
    {
        std::string name;
        ark::version version;
        std::string description;
    };

    class ARK_SHARED mod
    {
    public:
        using settings_type = std::vector<ark::setting>;

    public:
        explicit mod(ark::core& core, std::string name, ark::version = {0, 0, 1}, bool synchronized = true);

        mod(const mod&) = delete;
        mod& operator=(const mod&) = delete;

        void log(const std::string& data);

        template<class... Ts>
        void log(const std::string& message, Ts&&... ts)
        {
            log(std::vformat(message, std::make_format_args(ts...)));
        }

        virtual void on_enable() {}
        virtual void on_disable() {}
        virtual void on_settings_update() {}

        void enable();
        void disable();

        void set_info(ark::mod_info info);

        ark::core& core();
        const std::string& name() const;
        const std::string& fullname() const;
        ark::version version() const;
        const std::string& description() const;
        bool synchronized() const;
        bool enabled() const;

        // settings
        //void add_setting(ark::setting);
        template<class... Ts>
        void add_setting(Ts&&... ts);
        settings_type& settings();
        void save_settings();
        template<class T>
        T setting(const std::string& name) const;
    };
}// ark

namespace ark
{
    template<class... Ts>
    void mod::add_setting(Ts&&... ts)
    {
        settings().emplace_back(std::move(ts)...);
    }

} // ark

#endif// INCLUDE_ARKMOD_MOD_HPP_ARKENA_MOD