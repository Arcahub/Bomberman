#ifndef FF03DA6A_5D6C_454E_B9AF_DF309C9E6E62
#define FF03DA6A_5D6C_454E_B9AF_DF309C9E6E62

#include "ige/asset/Texture.hpp"
#include "ige/core/App.hpp"
#include "ige/core/State.hpp"
#include "ige/core/Task.hpp"
#include "ige/ecs/Entity.hpp"
#include "ige/plugin/RenderPlugin.hpp"
#include "ige/plugin/TransformPlugin.hpp"
#include <functional>
#include <iostream>
#include <optional>
#include <tuple>

template <typename NextState, typename... Ts>
class LoadingState : public ige::core::State {
private:
    using Tasks = std::tuple<ige::core::Task<Ts>...>;

    template <std::size_t I = 0>
    bool check_tasks_ready() const noexcept
    {
        if constexpr (I < std::tuple_size_v<Tasks>) {
            return std::get<I>(m_tasks).has_value()
                && check_tasks_ready<I + 1>();
        } else {
            return true;
        }
    }

    Tasks m_tasks;
    std::optional<ige::ecs::EntityId> m_loading_screen;

public:
    LoadingState(ige::core::Task<Ts>&&... tasks)
        : m_tasks(std::make_tuple<ige::core::Task<Ts>...>(
            std::forward<ige::core::Task<Ts>>(tasks)...))
    {
    }

    void on_start(ige::core::App& app) override
    {
        using ige::asset::Texture;
        using ige::plugin::render::ImageRenderer;
        using ige::plugin::transform::RectTransform;

        std::cout << "Loading started..." << std::endl;

        {
            m_loading_screen = app.world().create_entity(
                RectTransform {},
                ImageRenderer {
                    Texture::make_new("./assets/loading.png"),
                    ImageRenderer::Mode::STRETCHED,
                });
        }
    }

    void on_update(ige::core::App& app) override
    {
        if (check_tasks_ready()) {
            std::apply(
                [&](auto... tasks) {
                    app.state_machine().switch_to<NextState>(
                        std::move(tasks.value())...);
                },
                m_tasks);
        }
    }

    void on_stop(ige::core::App& app) override
    {
        app.world().remove_entity(*m_loading_screen);

        std::cout << "Loading finished!" << std::endl;
    }
};

#endif /* FF03DA6A_5D6C_454E_B9AF_DF309C9E6E62 */
