cmake_minimum_required(VERSION 3.6)
project(glutProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/simpleObjLoader.cpp src/SimpleObjHeader.h)
## add_executable(glutProject ${SOURCE_FILES} src/Cool.cpp src/Cool.h src/Shy.cpp src/Shy.h src/Guy.h)

#########################################################
# Include Files
#########################################################
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(src/CMakeLists.txt)
add_executable (glutProject
        main.cpp
        ${SOURCE_FILES})

IF (APPLE)
    include_directories (/System/Library/Frameworks)
    find_library (GLUT_LIBRARY GLUT)
    find_library (OpenGL_LIBRARY OpenGL)
    mark_as_advanced (GLUT_LIBRARY
            OpenGL_LIBRARY)
    set (EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
ENDIF (APPLE)

target_link_libraries(glutProject ${EXTRA_LIBS})

##################
# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # list of files for which we add a copy rule
    set(data_SHADOW elepham.obj)

    foreach(item IN LISTS data_SHADOW)
        message(STATUS ${item})
        add_custom_command(
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
                COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/data/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/data/${item}"
        )
    endforeach()
endif()

# files are only copied if a target depends on them
add_custom_target(data-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/elepham.obj")