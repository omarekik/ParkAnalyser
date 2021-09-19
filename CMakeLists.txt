include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/8aa657ee397a3273f9d2bb14a10b39fd1d556a77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

cmake_minimum_required(VERSION 3.12) # version can be different
project(ParkAnalyzer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(mytest testes/main.cpp 
                      testes/test.cpp
                      source/Parser.cpp
                      source/ParkLog.cpp)

target_link_libraries(mytest gtest_main)

add_custom_command(TARGET mytest
                   POST_BUILD
                   COMMAND mytest.exe --output-on-failure)