cmake_minimum_required(VERSION 3.21)

# webasm
if (EMSCRIPTEN)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
  set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so taht you can directly open it.
endif ()


# Config
project(GameJam VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
# Source
set(SOURCES 
src/main.cpp
src/game.cpp
src/plant.cpp
src/player.cpp
)

set(HEADERS 
inc/game.hpp
inc/plant.hpp
inc/player.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)


# Libraries
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # make sure it will print the download progress

## Raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples 
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied example games 

FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

execute_process(COMMAND sed -i "s/\\/\\/#define SUPPORT_FILEFORMAT_JPG/#define SUPPORT_FILEFORMAT_JPG/" config.h
                  WORKING_DIRECTORY ${raylib_SOURCE_DIR}/src) # Enables JPG


target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src/extras)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if ("${PLATFORM}" STREQUAL "Web")
    target_compile_options(${PROJECT_NAME} PRIVATE -DPLATFORM=Web)
    file(COPY configure/GameJam.html DESTINATION .)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE --static)
    # To fix strange seg fault bug
endif()


# Options
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-DDEBUG>)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)