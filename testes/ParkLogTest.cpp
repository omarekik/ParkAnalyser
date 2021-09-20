#include <gtest/gtest.h>
#include "Position.h"
#include "CarLog.h"
#include "ParkLog.h"
#include <math.h>


TEST(PositionTest, canGetTimeDistance){
    TimePosition time_position_1(1), time_position_2(2);      
    EXPECT_EQ(1, time_position_1.getTimeDistance(time_position_2));                    
}

TEST(PositionTest, canGetSpaceDistance){
    Space2dPosition space_2d_position_1(0, 0), space_2d_position_2(3, 4);      
    EXPECT_EQ(5, space_2d_position_1.getSpaceDistance(space_2d_position_2));                    
}

TEST(PositionTest, canCompare){
    TimeSpacePosition time_space_position_1(0, 0, 1), time_space_position_2(3, 4, 2);      
    EXPECT_TRUE(time_space_position_1 < time_space_position_2);  
    EXPECT_FALSE(time_space_position_1 < time_space_position_1);   
    EXPECT_FALSE(time_space_position_2 < time_space_position_1);                     
}

TEST(CarLogTest, canGetCarId){
    CarLog  car_log("000");  
    EXPECT_STREQ("000", car_log.getCarId().c_str());
}

TEST(CarLogTest, canCompare){
    CarLog  car_log_1("000");   
    car_log_1.insert(TimeSpacePosition(0, 0, 1));                        
    car_log_1.insert(TimeSpacePosition(3, 4, 2));      
    car_log_1.updateAvgSpeed();//AvgSpeed = 5
    EXPECT_FALSE(car_log_1 < 4);
    EXPECT_FALSE(car_log_1 < 5);
    EXPECT_TRUE(car_log_1 < 6);

    CarLog  car_log_2("001");   
    car_log_2.insert(TimeSpacePosition(3, 4, 2)); 
    car_log_2.insert(TimeSpacePosition(5, 6, 4));     
    car_log_2.updateAvgSpeed();//AvgSpeed = sqrt(2)  
    EXPECT_FALSE(car_log_1 < car_log_2);  
    EXPECT_TRUE(car_log_2 < car_log_1);         
}


TEST(ParkLogTest, canGetSpeedy){
    ParkLog  park_log;
    CarLog  car_log_1("000");   
    car_log_1.insert(TimeSpacePosition(0, 0, 1));                        
    car_log_1.insert(TimeSpacePosition(4, 4, 2));     
    car_log_1.updateAvgSpeed();//AvgSpeed = sqrt(32) > 5
    park_log.emplace(std::move(car_log_1));
    CarLog  car_log_2("001");   
    car_log_2.insert(TimeSpacePosition(0, 0, 1));                        
    car_log_2.insert(TimeSpacePosition(4, 4, 2));     
    car_log_2.updateAvgSpeed();//AvgSpeed = sqrt(32) > 5 same as car_log_1 to check m_CarLogs contains both cars
    park_log.emplace(std::move(car_log_2));
    
    CarLog  car_log_3("002");                    
    car_log_3.insert(TimeSpacePosition(3, 4, 2)); 
    car_log_3.insert(TimeSpacePosition(5, 6, 4));      
    car_log_3.updateAvgSpeed();//AvgSpeed = sqrt(2) < 5 
    park_log.emplace(std::move(car_log_3));  

    CarLog  car_log_4("003");                    
    car_log_4.insert(TimeSpacePosition(2, 2, 2)); 
    car_log_4.insert(TimeSpacePosition(10, 10, 3));      
    car_log_4.updateAvgSpeed();//AvgSpeed = sqrt(128) > 10 
    park_log.emplace(std::move(car_log_4));   

    EXPECT_STREQ(park_log.getSpeedy(5).c_str(), "000|001|003|");
    EXPECT_STREQ(park_log.getSpeedy(5, 10).c_str(), "000|001|");
}
