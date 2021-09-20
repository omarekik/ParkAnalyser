#include "Position.h"
#include "Parser.h"
#include <math.h>

Space2dPosition::Space2dPosition(int const & abscissa, int const & ordinate) : m_Abscissa(abscissa)
                                                                             , m_Ordinate(ordinate) {
}

double Space2dPosition::getSpaceDistance(Space2dPosition const & reference_pos) const {
    return std::sqrt(std::pow(this->m_Abscissa - reference_pos.m_Abscissa, 2) +
                     std::pow(this->m_Ordinate - reference_pos.m_Ordinate, 2));
}

TimePosition::TimePosition(int const & time) : m_Time(time) {
}

int TimePosition::getTimeDistance(TimePosition const & reference_pos) const {
    return std::abs(this->m_Time - reference_pos.m_Time);
}


TimeSpacePosition::TimeSpacePosition(int const & abscissa, 
                                     int const & ordinate, 
                                     int const & time) : Space2dPosition(abscissa, ordinate)
                                                       , TimePosition(time){
}

bool TimeSpacePosition::operator<(TimeSpacePosition const & rhs) const {
    return this->m_Time < rhs.m_Time;
}

std::string const TimeSpacePosition::serialize() const {
    std::string res = "";
    res += std::to_string(m_Abscissa);
    res += static_cast<char>(Separators::SPACE_TIME);
    res += std::to_string(m_Ordinate);
    res += static_cast<char>(Separators::SPACE_TIME);
    res += std::to_string(m_Time);
    res += static_cast<char>(Separators::POSITION);
    return res;
}