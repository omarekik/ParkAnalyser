#include <gtest/gtest.h>
#include "Parser.h"
#include "ParkLog.h"
#include <iostream>

TEST(ParserTest, canParseCleanData){
    ParkLog park_log;
    Parser parser("D:\\formations\\diegeizParkAnalyzer\\ParkAnalyzer\\testes\\config\\car_data.txt", park_log);
    EXPECT_STREQ("111", park_log.m_CarLogs[0].m_CarId.c_str());
    EXPECT_STREQ("333", park_log.m_CarLogs[2].m_CarId.c_str());
    EXPECT_STREQ("55", park_log.m_CarLogs[4].m_CarId.c_str());
    //
    // Test parsing the position 12*19*5 of car id 333
    //
    EXPECT_EQ(12, park_log.m_CarLogs[2].m_Positions[3].m_Abscissa);
    EXPECT_EQ(19, park_log.m_CarLogs[2].m_Positions[3].m_Ordinanate);
    EXPECT_EQ(5, park_log.m_CarLogs[2].m_Positions[3].m_Time);
    //
    // Exhaustive test
    //
    EXPECT_STREQ(parser.serializePark(park_log).c_str(), "111|0*0*0/5*1*1/10*1*3/8*0*4/26*20*5/5*-3*6/9*-7*8/9*-5*10/"
    "11*-1*12/13*-4*13/15*-8*15/35*12*16/12*-4*18/14*-8*20/10*-9*21/5*-6*220;222|0*0*0/1*5*2/-3*10*4/-1*12*5/-1*11*7/"
    "2*6*9/-1*1*10/2*-1*11/1*-6*12/-2*-2*13/3*-7*15/4*-8*16/-1*-5*18;333|0*0*0/-3*-3*1/1*1*3/12*19*5/6*-1*6/3*-2*8/"
    "4*-7*9/1*-12*11/15*8*12/5*-8*13/17*12*15/5*-6*16/2*-2*18/5*0*20/8*2*21/6*4*22/7*2*23/9*0*24/12*3*25/32*21*26/"
    "10*2*27/12*7*29;444|0*0*0/-5*5*2/-1*2*4/2*7*5/3*12*6/0*8*7/-5*4*8/-4*9*10/13*26*11/-8*4*13/12*18*15/-8*0*16/"
    "-8*2*18/-12*7*20/-12*11*21/-10*12*22/-11*8*24/-9*10*26/-13*6*28/1*25*29/-18*1*31/-17*5*33;55|0*0*0/-5*-1*1/"
    "-2*-4*3/-7*-5*5/5*14*6/-5*-7*8/-10*-10*10/-14*-13*12/-15*-10*14/-17*-12*16/-18*-10*17/-4*2*18/-19*-11*20/"
    "-22*-10*22/-17*-10*24/-19*-11*26;");
}

TEST(ParserTest, canParseGrossData){
    ParkLog park_log;
    Parser parser("D:\\formations\\diegeizParkAnalyzer\\ParkAnalyzer\\testes\\config\\car_data (with error).txt", park_log);
    ASSERT_STREQ("222", park_log.m_CarLogs[0].m_CarId.c_str());
    ASSERT_STREQ("444", park_log.m_CarLogs[2].m_CarId.c_str());
    ASSERT_STREQ("55", park_log.m_CarLogs[3].m_CarId.c_str());
    //
    // Test parsing the position 12*19*5 of car id 333
    //
    ASSERT_EQ(12, park_log.m_CarLogs[1].m_Positions[3].m_Abscissa);
    ASSERT_EQ(19, park_log.m_CarLogs[1].m_Positions[3].m_Ordinanate);
    ASSERT_EQ(5, park_log.m_CarLogs[1].m_Positions[3].m_Time);
    //
    // Exhaustive test
    //
    EXPECT_STREQ(parser.serializePark(park_log).c_str(), "222|0*0*0/1*5*2/-3*10*4/-1*12*5/-1*11*7/2*6*9/-1*1*10/"
    "2*-1*11/1*-6*12/-2*-2*13/3*-7*15/4*-8*16/-1*-5*18;333|0*0*0/-3*-3*1/1*1*3/12*19*5/6*-1*6/3*-2*8/4*-7*9/1*-12*11/"
    "15*8*12/5*-8*13/17*12*15/5*-6*16/2*-2*18/5*0*20/8*2*21/6*4*22/7*2*23/9*0*24/12*3*25/32*21*26/10*2*27/12*7*29;"
    "444|0*0*0/-5*5*2/-1*2*4/2*7*5/3*12*6/0*8*7/-5*4*8/-4*9*10/13*26*11/-8*4*13/12*18*15/-8*0*16/-8*2*18/-12*7*20/"
    "-12*11*21/-10*12*22/-11*8*24/-9*10*26/-13*6*28/1*25*29/-18*1*31/-17*5*33;55|0*0*0/-5*-1*1/-2*-4*3/-7*-5*5/5*14*6/"
    "-5*-7*8/-10*-10*10/-14*-13*12/-15*-10*14/-17*-12*16/-18*-10*17/-4*2*18/-19*-11*20/-22*-10*22/-17*-10*24/"
    "-19*-11*26;");
    
}