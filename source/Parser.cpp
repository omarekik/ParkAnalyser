#include "Parser.h"
#include "ParkLog.h"
#include "Position.h"
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
        std::string_view car_log_sv(&m_Log[log_sep_begin], log_sep_end - log_sep_begin);
        //std::cout<<"car log: " << car_log_sv << "\n";

        //
        // Parse car id
        //
        std::string::size_type id_sep_end = 0;
        id_sep_end = car_log_sv.find(static_cast<char>(Separators::ID));
        if(id_sep_end != std::string_view::npos){
            std::string_view car_id(&m_Log[log_sep_begin], id_sep_end);
            CarLog car_log(std::move(std::string(car_id)));
            //std::cout<<"car id: " << car_id << "\n";

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
                std::string_view position_sv(&car_log_sv[position_sep_begin], position_sep_end - position_sep_begin);
                //
                // Parse abscissa
                //    
                std::string::size_type abscissa_sep_end = 0;
                abscissa_sep_end = position_sv.find(static_cast<char>(Separators::SPACE_TIME));
                if(abscissa_sep_end != std::string_view::npos){
                    int abscissa = 0;
                    std::string_view abscissa_sv(&position_sv[0], abscissa_sep_end);
                    auto result = std::from_chars(abscissa_sv.data(), abscissa_sv.data() + abscissa_sv.size(), abscissa);
                    bool parsed_position = true;
                    if (result.ec == std::errc::invalid_argument) {
                        std::cout << "Could not convert abscissa:" << std::string(abscissa_sv) << "\n";
                        parsed_position = false;
                    }
                    //
                    // Parse ordinate of position.
                    //    
                    std::string::size_type ordinate_sep_begin = abscissa_sep_end + 1, ordinate_sep_end = abscissa_sep_end + 1;
                    ordinate_sep_end = position_sv.find(static_cast<char>(Separators::SPACE_TIME), ordinate_sep_begin);
                    if(ordinate_sep_end != std::string_view::npos){
                        int ordinate = 0;
                        std::string_view ordinate_sv(&position_sv[ordinate_sep_begin], ordinate_sep_end - ordinate_sep_begin);
                        result = std::from_chars(ordinate_sv.data(), ordinate_sv.data() + ordinate_sv.size(), ordinate);
                        if (result.ec == std::errc::invalid_argument) {
                            std::cout << "Could not convert ordinate:" << std::string(ordinate_sv) << "\n";
                            parsed_position = false;
                        }
                        //
                        // Parse time of position.
                        //    
                        int time = 0;
                        std::string_view time_sv(&position_sv[ordinate_sep_end + 1], position_sv.size() - (ordinate_sep_end + 1));
                        result = std::from_chars(time_sv.data(), time_sv.data() + time_sv.size(), time);
                        if (result.ec == std::errc::invalid_argument) {
                            std::cout << "Could not convert time:" << std::string(time_sv) << "\n";
                            parsed_position = false;
                        }
                        //
                        // move position to list of positions of car
                        //
                        if(parsed_position){
                            car_log.insert(TimeSpacePosition(abscissa, ordinate, time));
                            //std::cout<<"Parsed position   abscissa: "<< abscissa << ", ordinate: "<< ordinate << ", time: " << time;
                        }
                        else{
                            std::cout<<"Position is rejected because one of its elements can not be converted to integer: " << position_sv << "\n";
                        }
                    }
                    else {
                        std::cout<<"Position is rejected because no space time separator between ordinate and time: "
                                << position_sv << "\n";
                    }
                }
                else {
                    std::cout<<"Position is rejected because no space time separator between abscissa and ordinate: "
                             << position_sv << "\n";
                }
                position_sep_begin = position_sep_end + 1;
            }
            //
            // move car log to park log
            //
            car_log.updateAvgSpeed();
            park_log.emplace(std::move(car_log));
        }
        else{
            //
            // Reject car log with no ID separator.
            //
            std::cout << "Car log contains no ID separator: " << car_log_sv << "\n";
        }
        log_sep_begin = log_sep_end + 1;
    }
}
