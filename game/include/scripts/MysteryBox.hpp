#ifndef MYSTERYBOX_HPP_
#define MYSTERYBOX_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

enum class MysteryBoxType {
    SPEED_UP,
    REVERSE_CONTROLLE,
    REVERSE_CAM,
    RANGE_BOMB,
    ACTION_SPEED,
};

class MysteryBox : public CppBehaviour {
public:
    MysteryBox(MysteryBoxType type);
    ~MysteryBox();

    void on_start() override;
    void update() override;

protected:
private:
    void ApplyEffect(ige::plugin::script::Scripts& playerController);
    void PlayAudio(int idSound);

    std::optional<ige::ecs::EntityId> audioSource;
    ige::plugin::audio::AudioSource* m_audioSource;
    MysteryBoxType m_type;
};

#endif /* !MYSTERYBOX_HPP_ */
