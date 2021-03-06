cmake_minimum_required(VERSION 3.6)
project(glutProject)
## use the open source file dialog "native file dialog"
add_subdirectory(nfd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/setup/SimpleObjLoader.cpp src/setup/SimpleObjLoader.h src/matrix/RotationHelper.cpp
        src/matrix/RotationHelper.h src/ui/UserInputManager.cpp src/ui/UserInputManager.h
        src/ui/StringUtils.cpp src/ui/StringUtils.h src/setup/Preferences.cpp src/setup/Preferences.h src/setup/SetupFileLoader.cpp src/setup/SetupFileLoader.h src/matrix/InterpolationHelper.cpp src/matrix/InterpolationHelper.h src/matrix/QuaternionConverter.cpp src/matrix/QuaternionConverter.h)

#########################################################
# Include Files
#########################################################
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        src/ui
        src/setup
        src/matrix
        ${CMAKE_SOURCE_DIR}/nfd
)


add_executable (glutProject
        src/main.cpp
        ${SOURCE_FILES})

IF (APPLE)
    include_directories (/System/Library/Frameworks)
    find_library (GLUT_LIBRARY GLUT)
    find_library (OpenGL_LIBRARY OpenGL)
    find_library (APPKIT_LIBRARY APPKIT)
    mark_as_advanced (GLUT_LIBRARY OpenGL_LIBRARY APPKIT_LIBRARY)
    set (EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY} ${APPKIT_LIBRARY})
ENDIF (APPLE)

target_link_libraries(glutProject ${EXTRA_LIBS} nativefiledialog)

##################
# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # list of files for which we add a copy rule
    set(object_files teddy.obj)

    foreach(item IN LISTS object_files)
        message(STATUS ${item})
        add_custom_command(
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
                COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/data/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/data/${item}"
        )
    endforeach()
endif()

# files are only copied if a target depends on them
add_custom_target(teddy ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/teddy.obj")
# add the dependency project to the project target
ADD_DEPENDENCIES(glutProject teddy)