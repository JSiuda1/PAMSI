cmake_minimum_required(VERSION 3.0)

project(projekt_1)

include_directories(inc)
file(GLOB SOURCE "src/*.cpp" "inc/*.hh")

add_executable(${PROJECT_NAME} ${SOURCE} "src/protocolReceiver.cpp" "src/protocolTransmiter.cpp")