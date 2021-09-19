#include <gtest/gtest.h>
#include "Parser.h"

TEST(SeparatorTest, canGetSeparators){
    EXPECT_STREQ(";|*/", getSeparators().c_str());  
}

TEST(ParserTest, canInstanciateParser){
    ParkLog park_log;
    Parser parser("car_data.txt",park_log);
}