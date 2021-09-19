#pragma once
#include <string>

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

std::string const getSeparators();



