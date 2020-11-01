cmake_minimum_required(VERSION 3.9)
project(GameServer VERSION 1.0 DESCRIPTION "description")

# include(GNUInstallDirs)
# Version number
set (GameServer_VERSION_MAJOR 1)
set (GameServer_VERSION_MINOR 0)


add_executable(GameServer src/main.cpp)

# set_target_properties(GameServer PROPERTIES VERSION ${PROJECT_VERSION})
# set_target_properties(GameServer PROPERTIES SOVERSION 1)

# set_target_properties(GameServer PROPERTIES PUBLIC_HEADER include/GameServer.h)

# configure_file(GameServer.pc.in GameServer.pc @ONLY)

# install(TARGETS GameServer
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# install(FILES ${CMAKE_BINARY_DIR}/GameServer.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

target_link_libraries(${PROJECT_NAME} Boost::boost)
target_link_libraries(${PROJECT_NAME}
    UtilLibrary
)