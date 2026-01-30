cmake_minimum_required(VERSION 3.5)
project(SatelliteTracker)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option 1: First try to find system libpredict
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(PC_PREDICT QUIET predict)
endif()

if(PC_PREDICT_FOUND)
    # Use system library
    set(PREDICT_INCLUDE_DIRS ${PC_PREDICT_INCLUDE_DIRS})
    set(PREDICT_LIBRARIES ${PC_PREDICT_LIBRARIES})
    message(STATUS "Using system libpredict")
else()
    # Use local libpredict as subdirectory
    message(STATUS "Using local libpredict subdirectory")

    # Check if libpredict directory exists
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libpredict/CMakeLists.txt")
        add_subdirectory(libpredict)
        # libpredict creates a target called 'predict'
        set(PREDICT_LIBRARIES predict)
        set(PREDICT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/libpredict/src")
    else()
        message(FATAL_ERROR "libpredict not found. Please clone it to ${CMAKE_CURRENT_SOURCE_DIR}/libpredict")
    endif()
endif()

add_executable(SatelliteTracker
        main.c
        ascii.c
        ascii.h
        directory_options.c
        directory_options.h
        main.h
)

target_include_directories(SatelliteTracker PRIVATE ${PREDICT_INCLUDE_DIRS})
target_link_libraries(SatelliteTracker PRIVATE ${PREDICT_LIBRARIES})