cmake_minimum_required(VERSION 3.11)
project(graphy VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)

find_package(UnitTest++ REQUIRED)

add_executable( ${PROJECT_NAME}
                main.cpp
                tests.cpp

                src/graphy.cpp
                src/database.cpp

                src/commands/get.cpp
                src/commands/set.cpp)
target_link_libraries(${PROJECT_NAME} UnitTest++)