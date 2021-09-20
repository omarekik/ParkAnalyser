#pragma once

#include "Position.h"
#include <set>
#include <string>
#include <filesystem>

class MobileLog{
public:
    MobileLog();
    bool operator<(MobileLog const & rhs) const ;
    bool operator<(int const & rhs) const ;
    void insert(TimeSpacePosition time_space_position);
    void updateAvgSpeed();
public:
    double m_AvgSpeed;
protected:
    //
    // set will sort TimeSpacePosition by Time
    // to overcome error of unordered timestamps
    //
    std::set<TimeSpacePosition> m_PosLog;
private:
    std::set<TimeSpacePosition>::iterator m_PosLog_hint;
};

class CarLog : public MobileLog{
public:
    CarLog(std::string car_id);
    CarLog(CarLog const &) = delete;
    CarLog& operator=(CarLog const &) = delete;
    CarLog(CarLog&&) = default;
    CarLog& operator=(CarLog&&) = default;
    virtual ~CarLog() = default;

    std::string const & getCarId() const;
    std::string const serialize() const;
private:
    std::string m_CarId;
};
