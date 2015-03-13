cmake_minimum_required(VERSION 3.1.1 FATAL_ERROR)
project(ICS161GameEngine)

set(OTHER_LIBRARIES CACHE STRING "")
set(OTHER_INCLUDE_DIRS CACHE STRING "")

set(LIBRARY_NAME ${PROJECT_NAME})

# libraries found through pkg-config
include(FindPkgConfig)
foreach(pkg
    sdl2
    SDL2_image
)
    pkg_search_module(${pkg} REQUIRED ${pkg})
endforeach()

include_directories(${sdl2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})

add_library(${LIBRARY_NAME}
    Map.cpp
)
find_package(Boost COMPONENTS filesystem system)

target_link_libraries(${LIBRARY_NAME}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${sdl2_LIBRARIES}
    ${SDL2_image_LIBRARIES}
    ${OTHER_LIBRARIES}
)

if(NOT OTHER_INCLUDE_DIRS STREQUAL "")
    include_directories(${OTHER_INCLUDE_DIRS})
endif()

set(DEMO_NAME ${PROJECT_NAME}_demo)

add_executable(${DEMO_NAME}
    MapDemo.cpp
)

target_link_libraries(${DEMO_NAME}
    ${LIBRARY_NAME}
)



