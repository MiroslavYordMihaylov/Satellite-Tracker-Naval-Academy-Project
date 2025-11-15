cmake_minimum_required(VERSION 3.20)
project(SatelliteTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PREDICT REQUIRED predict)

add_executable(SatelliteTracker
        src/main.cpp
        src/main.cpp
        src/main.h
        main.c
)

target_include_directories(SatelliteTracker PRIVATE ${PREDICT_INCLUDE_DIRS})
target_link_libraries(SatelliteTracker PRIVATE ${PREDICT_LIBRARIES})

