#ifndef ROOMSTATE_HPP_
#define ROOMSTATE_HPP_

#include "ige.hpp"

#include <optional>
#include <string>

struct IsServerMarker {
};

class RoomState : public ige::core::State {
public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
    void on_stop(ige::core::App&) override;

private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;
    bool m_as_client;
    std::string m_mm_id;
};

#endif /* !ROOMSTATE_HPP_ */
