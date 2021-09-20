#include "ParkLog.h"

void ParkLog::emplace(CarLog car_log){
    m_CarLogs.emplace(std::move(car_log));
}

std::string ParkLog::getSpeedy(int const & minSpeed) const {
    std::string res = "";
    auto it = std::lower_bound(m_CarLogs.begin(), m_CarLogs.end(), minSpeed);
    for(; it != m_CarLogs.end(); ++it){
        res += it->getCarId() + '|';
    }
    return res;
}

std::string ParkLog::getSpeedy(int const & minSpeed, int const & maxSpeed) const {
    std::string res = "";
    auto it = std::lower_bound(m_CarLogs.begin(), m_CarLogs.end(), minSpeed);
    auto it_end = std::lower_bound(m_CarLogs.begin(), m_CarLogs.end(), maxSpeed);
    for(; it != it_end; ++it){
        res += it->getCarId() + '|';
    }
    return res;
}

std::string const ParkLog::serialize() const {
    std::string res = "";
    for(auto const & car_log : m_CarLogs){
        res += car_log.serialize();
    }
    return res;
}