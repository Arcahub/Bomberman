#ifndef FF03DA6A_5D6C_454E_B9AF_DF309C9E6E62
#define FF03DA6A_5D6C_454E_B9AF_DF309C9E6E62

#include "ige/core/App.hpp"
#include "ige/core/State.hpp"
#include "ige/core/Task.hpp"
#include <functional>
#include <iostream>
#include <tuple>

template <typename NextState, typename... Ts>
class LoadingState : public ige::core::State {
    using Tasks = std::tuple<ige::core::Task<Ts>...>;

public:
    LoadingState(ige::core::Task<Ts>&&... tasks)
        : m_tasks(std::make_tuple<ige::core::Task<Ts>...>(
            std::forward<ige::core::Task<Ts>>(tasks)...))
    {
    }

    void on_start(ige::core::App&) override
    {
        std::cout << "Loading started..." << std::endl;
    }

    void on_update(ige::core::App& app) override
    {
        bool all_ready = check_all_ready();

        if (all_ready) {
            std::apply(
                [&](auto... tasks) {
                    app.state_machine().switch_to<NextState>(
                        std::move(tasks.value())...);
                },
                m_tasks);
        }
    }

    void on_stop(ige::core::App&) override
    {
        std::cout << "Loading finished!" << std::endl;
    }

private:
    template <std::size_t I = 0>
    bool check_all_ready() const noexcept
    {
        if constexpr (I < std::tuple_size_v<Tasks>) {
            return std::get<I>(m_tasks).has_value() && check_all_ready<I + 1>();
        } else {
            return true;
        }
    }

    Tasks m_tasks;
};

#endif /* FF03DA6A_5D6C_454E_B9AF_DF309C9E6E62 */
