#pragma once

#include <string>

class Space2dPosition{
public:
    Space2dPosition(int const & abscissa, int const & ordinate);
    double getSpaceDistance(Space2dPosition const & reference_pos) const ;
protected:
    int m_Abscissa;
    int m_Ordinate;
};

class TimePosition{
public:
    TimePosition(int const & time);
    int getTimeDistance(TimePosition const & reference_pos) const ;
protected:
    int m_Time;
};

class TimeSpacePosition : public TimePosition, public Space2dPosition{
public:
    TimeSpacePosition(int const & abscissa, int const & ordinate, int const & time);
    TimeSpacePosition(TimeSpacePosition const &) = delete;
    TimeSpacePosition& operator=(TimeSpacePosition const &) = delete;
    TimeSpacePosition(TimeSpacePosition&&) = default;
    TimeSpacePosition& operator=(TimeSpacePosition&&) = default;
    virtual ~TimeSpacePosition() = default;

    bool operator<(TimeSpacePosition const & rhs) const ;
    std::string const serialize() const;
};
