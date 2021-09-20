#pragma once

#include "CarLog.h"
#include <set>
#include <string>
#include <filesystem>

class ParkLog{
public:
    void emplace(CarLog car_log);
    std::string getSpeedy(int const & minSpeed)const;
    std::string getSpeedy(int const & minSpeed, int const & maxSpeed)const;
    std::string const serialize() const;
private:    
    std::multiset<CarLog> m_CarLogs;
};
