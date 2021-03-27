cmake_minimum_required(VERSION 3.16)

project(CppPlayGround CXX)
include(Cmake/StandardProjectSettings.cmake)
include(Cmake/PreventInSourceBuilds.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()



#find_package(Catch2 REQUIRED)
add_subdirectory(src)
#target_link_libraries(test PRIVATE Catch2::Catch2)