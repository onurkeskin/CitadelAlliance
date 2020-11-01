cmake_minimum_required(VERSION 3.9)
project (UtilLibrary VERSION 1.0 DESCRIPTION "description")

# Create a library called "UtilLibrary" which includes the source file "camathfuncs.h".
# The extension is already found. Any number of sources could be listed here.
add_library (UtilLibrary SHARED 
    src/camathfuncs.cpp
)

# set_target_properties(UtilLibrary PROPERTIES VERSION ${PROJECT_VERSION})
# set_target_properties(UtilLibrary PROPERTIES SOVERSION 1)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories ( ${PROJECT_NAME} 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)