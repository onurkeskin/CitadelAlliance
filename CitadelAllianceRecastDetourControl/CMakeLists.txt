cmake_minimum_required(VERSION 3.9)
project (RecastDetourControl VERSION 1.0 DESCRIPTION "description")

# include(GNUInstallDirs)
# Version number
set (RecastDetourControl_VERSION_MAJOR 1)
set (RecastDetourControl_VERSION_MINOR 0)

add_library(RecastDetourControl SHARED 
    src/NavMapController.cpp
)

set_target_properties(RecastDetourControl PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(RecastDetourControl PROPERTIES SOVERSION 1)

# set_target_properties(RecastDetourControl PROPERTIES PUBLIC_HEADER include/RecastDetourControl.h)

# configure_file(RecastDetourControl.pc.in RecastDetourControl.pc @ONLY)

target_include_directories(RecastDetourControl PUBLIC ${PROJECT_SOURCE_DIR}/include)

# install(TARGETS RecastDetourControl
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# install(FILES ${CMAKE_BINARY_DIR}/RecastDetourControl.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

target_link_libraries(${PROJECT_NAME}
    Recast
    Detour
    DetourCrowd
    DebugUtils
    UtilLibrary
    GameMapBind
)