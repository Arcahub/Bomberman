//
// Created by mathias on 6/2/21.
//

#ifndef BOMBERMAN_MAPGENERATOR_HPP
#define BOMBERMAN_MAPGENERATOR_HPP

#include "ige.hpp"

using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;

class MapGenerator : public CppBehaviour {
public:
    MapGenerator();
    ~MapGenerator();

    void on_start() override;
    void tick() override;
protected:
private:
    std::vector<std::vector<std::string>> splitCsv(std::istream&);
};

#endif // BOMBERMAN_MAPGENERATOR_HPP
