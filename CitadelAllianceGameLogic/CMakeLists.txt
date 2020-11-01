cmake_minimum_required(VERSION 3.9)
project (GameLogic VERSION 1.0 DESCRIPTION "description")

include(GNUInstallDirs)
# Version number
set (GameLogic_VERSION_MAJOR 1)
set (GameLogic_VERSION_MINOR 0)

add_library(GameLogic SHARED 
    src/CJsonSerializer.cpp
    src/GameLogic.cpp
    src/GameUnit.cpp
    src/MoveableGameUnit.cpp
    src/MoveableUnitBehaviourAI.cpp
    src/SpawnPoint.cpp
    src/UnitMoveObjective.cpp
    src/UnitState.cpp
)

# set_target_properties(GameLogic PROPERTIES VERSION ${PROJECT_VERSION})
# set_target_properties(GameLogic PROPERTIES SOVERSION 1)

# set_target_properties(GameLogic PROPERTIES PUBLIC_HEADER include/GameLogic.h)

# configure_file(GameLogic.pc.in GameLogic.pc @ONLY)

# target_include_directories(GameLogic PRIVATE include)

# install(TARGETS GameLogic
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# install(FILES ${CMAKE_BINARY_DIR}/GameLogic.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
target_include_directories(GameLogic PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    UtilLibrary
    GameMapBind
    jsoncpp_lib_static
)