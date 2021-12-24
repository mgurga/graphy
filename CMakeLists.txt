cmake_minimum_required(VERSION 3.11)
project(graphy VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)

find_package(UnitTest++ REQUIRED)

add_executable( ${PROJECT_NAME}
                src/graphy.cpp
                src/main.cpp
                src/tests.cpp
                src/database.cpp

                src/commands/get.cpp
                src/commands/set.cpp)
target_link_libraries(${PROJECT_NAME} UnitTest++)