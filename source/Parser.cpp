#include "Parser.h"
#include "ParkLog.h"
#include <fstream>
#include <sstream>
#include <string_view>
#include <iostream>
#include <charconv>

Parser::Parser(std::filesystem::path const & filename, ParkLog & park_log){
    std::ifstream log_file(filename);
    //
    // Assume that all log is in one line and that the file contains at least one car log.
    //
    std::getline(log_file, m_Log);
    std::string::size_type log_sep_begin = 0, log_sep_end = 0;
    for(bool log_loop = true; log_loop;){
        //
        // The last car log is not ended by ';' separator.
        //
        if((log_sep_end = m_Log.find(static_cast<char>(Separators::LOG), log_sep_begin)) == std::string::npos){
            log_loop = false;
            log_sep_end = m_Log.size();
        }
        CarLog car_log;
        std::string_view car_log_sv(&m_Log[log_sep_begin], log_sep_end - log_sep_begin);
        //
        // Parse car id
        //
        std::string::size_type id_sep_end = 0;
        id_sep_end = car_log_sv.find(static_cast<char>(Separators::ID));
        std::string_view car_id(&m_Log[log_sep_begin], id_sep_end);
        car_log.m_CarId = std::move(std::string(car_id));
        //
        // Parse the list of car positions
        //
        std::string::size_type position_sep_begin = id_sep_end + 1, position_sep_end = id_sep_end;
        for(bool position_loop = true; position_loop;){
            //
            // The case that the list of positions ended by a position (Separators::LOG) and not Separators::POSITION
            //
            if((position_sep_end = car_log_sv.find(static_cast<char>(Separators::POSITION), position_sep_begin)) == std::string_view::npos){
                position_loop = false;
                position_sep_end = car_log_sv.size() ;
            }
            //
            // The case that the list of positions ended by Separators::POSITION
            //
            if(position_sep_end > car_log_sv.size() - 2) position_loop = false;
            Position position;
            std::string_view position_sv(&car_log_sv[position_sep_begin], position_sep_end - position_sep_begin);
            //
            // Parse abscissa
            //    
            std::string::size_type abscissa_sep_end = 0;
            abscissa_sep_end = position_sv.find(static_cast<char>(Separators::SPACE_TIME));
            int abscissa = 0;
            std::string_view abscissa_sv(&position_sv[0], abscissa_sep_end);
            auto result = std::from_chars(abscissa_sv.data(), abscissa_sv.data() + abscissa_sv.size(), abscissa);
            if (result.ec == std::errc::invalid_argument) {
                std::cout << "Could not convert abscissa:" << std::string(abscissa_sv) << "\n";
            }
            position.m_Abscissa = std::move(abscissa);
            //
            // Parse ordinate of position.
            //    
            std::string::size_type ordinate_sep_begin = abscissa_sep_end + 1, ordinate_sep_end = abscissa_sep_end + 1;
            ordinate_sep_end = position_sv.find(static_cast<char>(Separators::SPACE_TIME), ordinate_sep_begin);
            int ordinate = 0;
            std::string_view ordinate_sv(&position_sv[ordinate_sep_begin], ordinate_sep_end - ordinate_sep_begin);
            result = std::from_chars(ordinate_sv.data(), ordinate_sv.data() + ordinate_sv.size(), ordinate);
            if (result.ec == std::errc::invalid_argument) {
                std::cout << "Could not convert ordinate:" << std::string(ordinate_sv) << "\n";
            }
            position.m_Ordinanate = std::move(ordinate);
            //
            // Parse time of position.
            //    
            int time = 0;
            std::string_view time_sv(&position_sv[ordinate_sep_end + 1], position_sv.size() - (ordinate_sep_end + 1));
            result = std::from_chars(time_sv.data(), time_sv.data() + time_sv.size(), time);
            if (result.ec == std::errc::invalid_argument) {
                std::cout << "Could not convert time:" << std::string(time_sv) << "\n";
            }
            position.m_Time = std::move(time);
            //
            // move position to list of positions of car
            //
            car_log.m_Positions.emplace_back(std::move(position));
            position_sep_begin = position_sep_end + 1;
        }
        //
        // move car log to park log
        //
        park_log.m_CarLogs.emplace_back(std::move(car_log));
        log_sep_begin = log_sep_end + 1;
    }
}

std::string Parser::serializePark(ParkLog & park_log){
    std::string res = "";
    for(auto & car_log : park_log.m_CarLogs){
        res += car_log.m_CarId;
        res += static_cast<char>(Separators::ID);
        for(auto & position : car_log.m_Positions){
            res += std::to_string(position.m_Abscissa);
            res += static_cast<char>(Separators::SPACE_TIME);
            res += std::to_string(position.m_Ordinanate);
            res += static_cast<char>(Separators::SPACE_TIME);
            res += std::to_string(position.m_Time);
            res += static_cast<char>(Separators::POSITION);
        }
        //
        // In serialization, last position is not ended by Separators::POSITION
        //
        res.pop_back();
        res += static_cast<char>(Separators::LOG);
    }
    return res;
}