cmake_minimum_required(VERSION 3.16)
project(tdsreader LANGUAGES "CXX")

find_package(Eigen3 QUIET NO_MODULE)
if(NOT Eigen3_FOUND)
  message(STATUS "Eigen not found, fetching with FetchContent")

  set(EIGEN_BUILD_TESTS
      OFF
      CACHE BOOL "" FORCE)
  FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0)

  FetchContent_MakeAvailable(eigen)

endif()

add_library(tdsreader STATIC
        cpp/include/tdsreader/reader.hpp
        cpp/include/tdsreader/system.hpp
        cpp/src/reader.cpp
        cpp/src/utility.hpp
        cpp/src/utility.cpp
        cpp/src/system.cpp)
target_include_directories(tdsreader PUBLIC cpp/include)
target_compile_features(tdsreader PUBLIC cxx_std_20)
target_link_libraries(tdsreader PUBLIC Eigen3::Eigen)
