cmake_minimum_required(VERSION 3.20)
project(untitled1)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(FETCHCONTENT_QUIET OFF CACHE INTERNAL "Override verbose output" FORCE)
set(SFML_WARNINGS_AS_ERRORS OFF CACHE INTERNAL "Dezactiveaza erorile stricte" FORCE)
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.0.0
        GIT_SHALLOW    1
        GIT_PROGRESS   ON)
FetchContent_MakeAvailable(SFML)
#set(SFML_DIR "C:/Users/andre/CLionProjects/untitled1/cmake-build-debug/CMakeFiles/SFML-3.1.0")
include_directories(include)
add_executable(${PROJECT_NAME} main.cpp
        include/arma.cpp
        include/arma.h
        include/armura.cpp
        include/armura.h
        include/harta_map.h
        include/arena.cpp
        include/arena.h
        include/personajesicaractere.cpp
        include/personajesicaractere.h
        include/meniu.cpp
        include/meniu.h
        include/exceptii.cpp
        include/exceptii.h
        include/ceva_abstractidk.cpp
        include/ceva_abstractidk.h
        include/inventar_template.cpp
        include/inventar_template.h
        include/iobject.cpp
        include/iobject.h
        include/logger.cpp
        include/logger.h)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)
#if(POLICY CMP0135)
#    cmake_policy(SET CMP0135 NEW)
#endif()
#include(FetchContent)
#FetchContent_Declare(
#        raylib
#        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz)
#FetchContent_MakeAvailable(raylib)
#add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
