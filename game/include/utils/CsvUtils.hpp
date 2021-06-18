#ifndef CSVUTILS_HPP_
#define CSVUTILS_HPP_

#include <string>
#include <vector>

class CsvUtils {
public:
    static std::vector<std::vector<std::string>>
    SplitCsv(const std::string& str);
};

#endif /* !CSVUTILS_HPP_ */
