cmake_minimum_required(VERSION 3.0.0)
project(sdlgame)

add_executable(sdlgame
    src/main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(sdlgame
    PRIVATE
    "${SDL2_INCLUDE_DIRS}"
    "${SDL2_IMAGE_INCLUDE_DIRS}"
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(sdlgame
    PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

target_compile_features(sdlgame
    PRIVATE
    cxx_std_17
)