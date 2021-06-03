//
// Created by mathias on 6/2/21.
//

#ifndef BOMBERMAN_MAPGENERATOR_HPP
#define BOMBERMAN_MAPGENERATOR_HPP

#include "ige.hpp"

#include "glm/vec2.hpp"

#include <vector>
#include <string>

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
    void SpawnPlayer();

    std::vector<glm::ivec2> m_spawnPoints;
    float sizeMap = 0;
    float x = -1.0f;
    float y = -1.0f;
};

#endif // BOMBERMAN_MAPGENERATOR_HPP
