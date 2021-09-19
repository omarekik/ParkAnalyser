#include <gtest/gtest.h>
#include "Parser.h"

TEST(SeparatorTest, canGetSeparators){
    EXPECT_STREQ(";|*/", getSeparators().c_str());  
}