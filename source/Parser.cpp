#include "Parser.h"
#include "ParkLog.h"
#include <fstream>
#include <sstream>
#include <string_view>
#include <iostream>

Parser::Parser(std::filesystem::path const & filename, ParkLog & park_log){
    std::ifstream log_file(filename);
    //
    // Assume that all log is in one line
    //
    std::getline(log_file, m_Log);
    std::string::size_type log_sep_begin = 0, log_sep_end = 0;
    bool loop = true;
    do{
        //
        // The last car log is not ended by ';' separator.
        //
        if((log_sep_end = m_Log.find(static_cast<char>(Separators::LOG), log_sep_begin)) == std::string::npos){
            loop = false;
            log_sep_end = m_Log.size() - 1;
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
        // Parse positions
        //

        park_log.m_CarLogs.emplace_back(std::move(car_log));
        log_sep_begin = log_sep_end + 1;
    }while(loop);


}