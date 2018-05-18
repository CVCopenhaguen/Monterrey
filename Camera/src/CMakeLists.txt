cmake_minimum_required(VERSION 2.8.11)

project(camera)

find_package(OpenCV 3 REQUIRED)

add_executable(camera camera.cpp)

target_link_libraries(camera ${OpenCV_LIBS})
