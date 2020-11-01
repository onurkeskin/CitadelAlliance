cmake_minimum_required(VERSION 2.6)
project (CitadelAlliance)

add_subdirectory(boost-cmake)
add_subdirectory(jsoncpp)
add_subdirectory(RecastNavigation)
add_subdirectory(CitadelAllianceGameLogic)
add_subdirectory(CitadelAllianceGameServer)
add_subdirectory(CitadelAllianceRecastDetourControl)
add_subdirectory(CitadelAllianceGameMapBind)
add_subdirectory(CitadelAllianceUtilLibrary)

# target_link_libraries(lib_using_header_only PUBLIC Boost::boost)