cmake_minimum_required(VERSION 3.9)
project (DebugUtils)

add_library(${PROJECT_NAME} SHARED 
    Source/DebugDraw.cpp
    Source/DetourDebugDraw.cpp
    Source/RecastDebugDraw.cpp
    Source/RecastDump.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries( ${PROJECT_NAME}
    Recast
    Detour
    DetourTileCache
)