#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "utils/CsvUtils.hpp"

std::vector<std::vector<std::string>> CsvUtils::SplitCsv(const std::string& map)
{
    std::vector<std::vector<std::string>> result;
    std::stringstream str(map);
    std::string line;

    while (std::getline(str, line)) {
        std::vector<std::string> resultLine;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            resultLine.push_back(cell);
        }
        if (!lineStream && cell.empty())
            resultLine.push_back("");
        result.push_back(resultLine);
    }
    return result;
}
