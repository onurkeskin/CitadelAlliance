cmake_minimum_required(VERSION 3.9)
project (Recast)

add_library(${PROJECT_NAME} SHARED 
    Source/Recast.cpp
    Source/RecastAlloc.cpp
    Source/RecastArea.cpp
    Source/RecastAssert.cpp
    Source/RecastContour.cpp
    Source/RecastFilter.cpp
    Source/RecastLayers.cpp
    Source/RecastMesh.cpp
    Source/RecastMeshDetail.cpp
    Source/RecastRasterization.cpp
    Source/RecastRegion.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(${PROJECT_NAME}
    Detour
)