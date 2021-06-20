#include "menu/LayoutSubControls.hpp"

using ige::core::EventChannel;
using ige::ecs::World;
using ige::plugin::input::Bindings;
using ige::plugin::input::InputEvent;
using ige::plugin::input::InputEventType;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;
using ige::plugin::render::ImageRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;

static const std::string ActionsTab[4]
    = { "action", "action_j2", "action_j3", "action_j4" };

LayoutSubControls::LayoutSubControls(std::optional<ige::ecs::EntityId> lm)
{
    layoutManager = lm;
}

LayoutSubControls::~LayoutSubControls()
{
}

ige::ecs::EntityId LayoutSubControls::createSprite(
    glm::vec2 anchorMin, glm::vec2 anchorMax, Texture::Handle tex)
{
    return world().create_entity(
        Parent { this->entity() },
        RectTransform {}
            .set_anchors(anchorMin, anchorMax)
            .set_bounds({ 0.0f, 0.0f }, { 0.0f, 0.0f }),
        ImageRenderer { tex, ImageRenderer::Mode::STRETCHED });
}

void LayoutSubControls::on_start()
{
    auto input_channel = world().get<EventChannel<InputEvent>>();

    if (input_channel) {
        m_input_events = input_channel->subscribe();
    }

    auto tex_players = { Texture::make_new("assets/Text/J1.png"),
                         Texture::make_new("assets/Text/J2.png"),
                         Texture::make_new("assets/Text/J3.png"),
                         Texture::make_new("assets/Text/J4.png") };
    auto tex_controls = {
        Texture::make_new("assets/Text/Action.png"),
        Texture::make_new("assets/Text/characters/_arrow_right.png"),
        Texture::make_new("assets/Text/characters/_arrow_left.png"),
        Texture::make_new("assets/Text/characters/_arrow_down.png"),
        Texture::make_new("assets/Text/characters/_arrow_up.png"),
    };

    tex_cases = Texture::make_new("assets/Menu/Bomb/Menus/Settings/controls/"
                                  "Menu_settings_layout_case.png");
    tex_select = Texture::make_new("assets/Menu/Bomb/Menus/Settings/controls/"
                                   "Menu_settings_layout_select.png");
    tex_valid = Texture::make_new("assets/Menu/Bomb/Menus/Settings/controls/"
                                  "Menu_settings_layout_valid.png");

    for (std::size_t i = 0; i < 5; i++) {
        float maxWidth = (i == 0) ? 0.515f : 0.495f;
        float minHeight = (i == 0) ? 0.28f : 0.26f;
        float maxHeight = (i == 0) ? 0.3f : 0.32f;
        createSprite(
            { 0.445f, minHeight + 0.09f * i },
            { maxWidth, maxHeight + 0.09f * i }, *(tex_controls.begin() + i));
    }

    for (std::size_t i = 0; i < 4; i++) {
        createSprite(
            { 0.53f + i * 0.09f, 0.7f }, { 0.58f + i * 0.09f, 0.75f },
            *(tex_players.begin() + i));
    }

    for (std::size_t player = 0; player < 4; player++) {
        for (std::size_t i = 0; i < 5; i++) {
            ent_cases[player][i] = createSprite(
                { 0.51f + player * 0.09f, 0.24f + 0.09f * i },
                { 0.60f + player * 0.09f, 0.34f + 0.09f * i }, tex_cases);
        }
    }
}

void LayoutSubControls::update()
{
    auto scripts = world().get_component<Scripts>(layoutManager.value());
    auto lm = scripts->get<MenuLayoutManager>();

    updateCases(lm);
}

void LayoutSubControls::unlock(MenuLayoutManager* lm)
{
    if (auto input = world().get<InputManager<>>()) {
        if (!input->bindings.has_value()) {
            lm->lockMove = false;
            return;
        }

        if (m_input_events) {
            while (auto event = m_input_events->next_event()) {
                if (event->type == InputEventType::KEYBOARD) {
                    if (event->keyboard.state == InputRegistryState::PRESSED) {
                        input->bindings->insert_action(
                            "action", event->keyboard.key);
                        lm->lockMove = false;
                    }
                }
            }
        }
    }
    lm->lockMove = false;
}

void LayoutSubControls::updateActions(MenuLayoutManager* lm)
{
    if (!lm->lockMove)
        return;

    std::size_t player = lm->selectionID / 10;
    std::size_t action = lm->selectionID % 5;

    if (player < 1 || player > 4)
        return;

    for (std::size_t p = 0; p < 4; p++) {
        for (std::size_t i = 0; i < 5; i++) {
            if (player == p + 1 && action == 4 - i) { }
        }
    }
}

void LayoutSubControls::updateCases(MenuLayoutManager* lm)
{
    std::size_t player = lm->selectionID / 10;
    std::size_t action = lm->selectionID % 5;

    if (player < 1 || player > 4)
        return;

    for (std::size_t p = 0; p < 4; p++) {
        for (std::size_t i = 0; i < 5; i++) {
            auto ir
                = world().get_component<ImageRenderer>(ent_cases[p][i].value());

            if (player == p + 1 && action == 4 - i) {
                if (lm->lockMove) {
                    ir->texture = tex_valid;
                } else {
                    ir->texture = tex_select;
                }
            } else {
                ir->texture = tex_cases;
            }
        }
    }
}
