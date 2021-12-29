cmake_minimum_required(VERSION 3.11)
project(graphy VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)

find_package(UnitTest++ REQUIRED)

file(GLOB_RECURSE SRCFILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB MAINFILES ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable( ${PROJECT_NAME}
                ${MAINFILES}
                ${SRCFILES})
target_link_libraries(${PROJECT_NAME} UnitTest++)