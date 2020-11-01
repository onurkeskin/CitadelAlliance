cmake_minimum_required(VERSION 2.6)
project (GameMapBind)

# Version number
set (GameMapBind_VERSION_MAJOR 1)
set (GameMapBind_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
# configure_file (
#   "${PROJECT_SOURCE_DIR}/UtilConfig.h.in"
#   "${PROJECT_BINARY_DIR}/UtilConfig.h"
#   )

add_library(GameMapBind SHARED 
    src/GameMapBind.cpp
)

target_include_directories(GameMapBind PUBLIC ${PROJECT_SOURCE_DIR}/include)