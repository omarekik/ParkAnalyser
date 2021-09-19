#include <gtest/gtest.h>
#include "Parser.h"
#include "ParkLog.h"
#include <iostream>

TEST(ParserTest, canInstanciateParser){
    ParkLog park_log;
    Parser parser("D:\\formations\\diegeizParkAnalyzer\\ParkAnalyzer\\testes\\car_data.txt",park_log);
    EXPECT_STREQ("111", park_log.m_CarLogs[0].m_CarId.c_str());
    EXPECT_STREQ("333", park_log.m_CarLogs[2].m_CarId.c_str());
    EXPECT_STREQ("55", park_log.m_CarLogs[4].m_CarId.c_str());
}