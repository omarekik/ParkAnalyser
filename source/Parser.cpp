#include "Parser.h"
#include <fstream>
#include <sstream>

std::string const getSeparators() {
    std::string res = "";
    res += static_cast<char>(Separators::LOG);
    res += static_cast<char>(Separators::ID);
    res += static_cast<char>(Separators::SPACE_TIME);
    res += static_cast<char>(Separators::POSITION);
    return res;
}

Parser::Parser(std::filesystem::path const & filename, ParkLog & park_log){
    std::ifstream log_file(filename);
    //
    // Assume that all log is in one line
    //
    std::getline(log_file, m_Log);

}