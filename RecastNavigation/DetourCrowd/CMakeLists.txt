cmake_minimum_required(VERSION 3.9)
project (DetourCrowd)

add_library(${PROJECT_NAME} SHARED 
    Source/DetourCrowd.cpp
    Source/DetourLocalBoundary.cpp
    Source/DetourObstacleAvoidance.cpp
    Source/DetourPathCorridor.cpp
    Source/DetourPathQueue.cpp
    Source/DetourProximityGrid.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Include)

target_link_libraries(${PROJECT_NAME}
    Detour
)