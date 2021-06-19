#ifndef BOMBERMAN_MAPGENERATOR_HPP
#define BOMBERMAN_MAPGENERATOR_HPP

#include "ige.hpp"

#include "glm/vec2.hpp"

#include <string>
#include <vector>

using ige::core::App;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class MapGenerator : public CppBehaviour {
public:
    MapGenerator(App&, std::optional<ige::ecs::EntityId> audioSource);

    void on_start() override;
    void update() override;
    void tick() override;

    int numberPlayer = 4;

protected:
private:
    std::vector<std::vector<std::string>> splitCsv(std::istream&);
    void SpawnPlayer(
        std::vector<std::vector<int>>, std::vector<std::vector<int>>);
    std::string GenerateCsv(std::string, bool);
    void EndGame();
    void SetUi();

    ige::core::App& m_app;
    std::vector<ige::ecs::EntityId> textNbrPlayer;
    std::optional<ige::ecs::EntityId> m_audioSource;
};

#endif // BOMBERMAN_MAPGENERATOR_HPP
