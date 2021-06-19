#ifndef A861DF6F_757D_4CD0_9176_1564DE8FAFF3
#define A861DF6F_757D_4CD0_9176_1564DE8FAFF3

#include "ige.hpp"

class PreSoloGameState : public ige::core::State {
private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;

public:
    void on_start(ige::core::App&) override;
};

#endif /* A861DF6F_757D_4CD0_9176_1564DE8FAFF3 */
