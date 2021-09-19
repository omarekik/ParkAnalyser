#include "Parser.h"

std::string const getSeparators() {
    std::string res = "";
    res += static_cast<char>(Separators::LOG);
    res += static_cast<char>(Separators::ID);
    res += static_cast<char>(Separators::SPACE_TIME);
    res += static_cast<char>(Separators::POSITION);
    return res;
}