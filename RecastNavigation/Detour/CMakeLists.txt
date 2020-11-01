cmake_minimum_required(VERSION 3.9)
project (Detour)

add_library(Detour SHARED 
    Source/DetourAlloc.cpp
    Source/DetourAssert.cpp
    Source/DetourCommon.cpp
    Source/DetourNavMesh.cpp
    Source/DetourNavMeshBuilder.cpp
    Source/DetourNavMeshQuery.cpp
    Source/DetourNode.cpp
)


target_include_directories(Detour PUBLIC ${PROJECT_SOURCE_DIR}/Include)