#ifndef MYSTERYBOX_HPP_
#define MYSTERYBOX_HPP_

#include "ige.hpp"

#include <glm/vec3.hpp>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class MysteryBox : public CppBehaviour {
public:
    MysteryBox();
    ~MysteryBox();

    void on_start() override;
    void update() override;

protected:
private:
    void ApplyEffect(ige::plugin::script::Scripts& playerController);
    void PlayAudio(int idSound);

    std::optional<ige::ecs::EntityId> audioSource;
    ige::plugin::audio::AudioSource* m_audioSource;
};

#endif /* !MYSTERYBOX_HPP_ */
