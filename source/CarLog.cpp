#include "CarLog.h"
#include "Parser.h"
#include <iostream>


void MobileLog::insert(TimeSpacePosition time_space_position){
    //
    // It is presumed that values of time_space_position are already sorted, so hint reduce insert to O(1). 
    //
    m_PosLog_hint = m_PosLog.insert(m_PosLog_hint, std::move(time_space_position));
}

void MobileLog::updateAvgSpeed(){
    if(m_PosLog.size() >= 2){
        auto last_element_it = m_PosLog.end();
        last_element_it--;
        int const duration = m_PosLog.begin()->getTimeDistance(*last_element_it);
        double distance = 0;
        auto it = m_PosLog.begin();
        auto it_previous = it++;
        for(; it != m_PosLog.end(); ++it){
            distance += it->getSpaceDistance(*it_previous);
            it_previous = it;
        }
        m_AvgSpeed = distance / duration;
    }
    else{
        std::cout<<"Minimum number of positions to calculate Avg speed is 2.";
        m_AvgSpeed = 0;
    }
}

MobileLog::MobileLog() : m_AvgSpeed(0)
                       , m_PosLog_hint(m_PosLog.end()) {
}

bool MobileLog::operator<(MobileLog const & rhs) const {
    return this->m_AvgSpeed < rhs.m_AvgSpeed;
}

bool MobileLog::operator<(int const & rhs) const {
    return this->m_AvgSpeed < rhs;
}

CarLog::CarLog(std::string car_id) : m_CarId(std::move(car_id)){
}

std::string const & CarLog::getCarId() const{
    return m_CarId;
}

std::string const CarLog::serialize() const {
    std::string res = "";
    res += m_CarId;
    res += static_cast<char>(Separators::ID);
    for(auto & position : m_PosLog){
        res += position.serialize();
    }
    //
    // In serialization, last position is not ended by Separators::POSITION
    //
    res.pop_back();
    res += static_cast<char>(Separators::LOG);
    return res;
}