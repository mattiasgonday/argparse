# 1. Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(argparse_tests ${TEST_SOURCES})
target_link_libraries(argparse_tests PRIVATE argparse_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(argparse_tests)
