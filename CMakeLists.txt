cmake_minimum_required(VERSION 2.8)

project(idconverter)

add_executable(idconverter main.cpp idconverter.cpp)

add_executable(idtest test.cpp idconverter.cpp)
target_link_libraries(idtest cpptest)

install(TARGETS idconverter DESTINATION bin)
