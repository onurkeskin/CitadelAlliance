cmake_minimum_required(VERSION 3.9)
project (DetourTileCache)

add_library(DetourTileCache SHARED 
    Source/DetourTileCache.cpp
    Source/DetourTileCacheBuilder.cpp
)


target_include_directories(DetourTileCache PUBLIC ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(${PROJECT_NAME}
    Detour
)