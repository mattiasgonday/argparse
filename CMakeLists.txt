cmake_minimum_required(VERSION 3.20)
project(argparse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable clang-tidy if available
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()

add_library(argparse_lib INTERFACE)
target_include_directories(argparse_lib
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_options(argparse_lib INTERFACE -Wall)

# Install headers
include(GNUInstallDirs)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS argparse_lib EXPORT argparseTargets)

install(EXPORT argparseTargets
  FILE argparseTargets.cmake
  NAMESPACE argparse::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/argparse
)

# Package config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/argparseConfigVersion.cmake"
  VERSION 1.0.0
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/argparseConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/argparseConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/argparse
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/argparseConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/argparseConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/argparse
)

option(BUILD_ARGPARSE_CLI "Build local playground CLI app" OFF)

if(BUILD_ARGPARSE_CLI)
  add_executable(argparse main.cpp)
  target_link_libraries(argparse PRIVATE argparse_lib)
endif()

option(ENABLE_TESTING "Enable tests" OFF)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
