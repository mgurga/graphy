cmake_minimum_required(VERSION 3.11)
project(graphy VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Graphy executable
file(GLOB_RECURSE SRCFILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable( ${PROJECT_NAME}
                ${SRCFILES})
target_link_libraries(${PROJECT_NAME})

# Testing executable
IF (BUILD_TESTING)
    add_subdirectory(test)
ENDIF(BUILD_TESTING)
