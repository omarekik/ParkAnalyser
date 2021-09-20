#pragma once

#include <string>
#include <filesystem>
#include "ParkLog.h"

enum class Separators : char {
    //
    // Separate between the log of two cars
    //
     LOG = ';',
    //
    // Separate between id and first space time position
    //
     ID = '|',
    //
    // Separate between abscissa, ordonate and time
    //
     SPACE_TIME = '*',
    //
    // Separate between two space time positions
    //
     POSITION = '/'
};

class Parser
{
public:
    Parser(std::filesystem::path const & filename, ParkLog & park_log);
    //
    // Used only for test
    //
    std::string serializePark(ParkLog & park_log);
private:
    std::string m_Log;
};
