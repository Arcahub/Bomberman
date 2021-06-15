#ifndef BOMBERMAN_MAPGENERATOR_HPP
#define BOMBERMAN_MAPGENERATOR_HPP

#include "ige.hpp"

#include "glm/vec2.hpp"

#include <string>
#include <vector>

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class MapGenerator : public CppBehaviour {
public:
    void on_start() override;
    void tick() override;

protected:
private:
    std::vector<std::vector<std::string>> splitCsv(std::istream&);
    void SpawnPlayer(
        std::vector<std::vector<int>>, std::vector<std::vector<int>>);
    std::string GenerateCsv(std::string, bool);
    void SetUi();

    std::vector<glm::ivec2> m_spawnPoints;
    std::vector<ige::ecs::EntityId> blockMuds;
    std::vector<glm::vec2> posBlockMuds;
    float sizeMap = 0;
    float x = -1.0f;
    float y = -1.0f;

    int nbrlife = 3;
    int startNumberPlayer = 3;
    int numberPlayer = 3;
    int nbrStair = 2;
    float bockMudPercent = 70;
    float bockStonePercent = 15;
    float bonusBlock = 5;

    std::vector<ige::ecs::EntityId> textNbrPlayer;
};

#endif // BOMBERMAN_MAPGENERATOR_HPP
