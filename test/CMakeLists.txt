set(TEST_PROJECT_NAME test_${PROJECT_NAME})

message("started fetching googletest...")
include(FetchContent)
FetchContent_Declare(
    googletest
    # v 1.11.0
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
message("finished fetching googletest")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
file(GLOB_RECURSE TESTFILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable( ${TEST_PROJECT_NAME}
                ${TESTFILES})
target_link_libraries(${TEST_PROJECT_NAME}
                      gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME})
