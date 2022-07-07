#./CMakeLists.txt
#
#

cmake_minimum_required(VERSION 3.22.1)

project(memoizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

option(BUILD_EXAMPLES "build" ON)



if(BUILD_EXAMPLES)

    file (GLOB EXAMPLES "examples/*.cpp" )

    foreach(EACH IN LISTS EXAMPLES)
        get_filename_component(TARGET ${EACH} NAME_WE  )
        add_executable(${TARGET} ${EACH})
        target_include_directories(${TARGET}  PUBLIC source/)
        message(STATUS "X=${TARGET}")
    endforeach()
 
endif(BUILD_EXAMPLES)
