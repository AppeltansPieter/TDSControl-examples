cmake_minimum_required(VERSION 3.16)
project(tdsreader LANGUAGES "CXX")


add_library(tdsreader STATIC
        cpp/include/tdsreader/reader.hpp
        cpp/include/tdsreader/system.hpp
        cpp/src/reader.cpp
        cpp/src/utility.hpp
        cpp/src/utility.cpp
        cpp/src/system.cpp)
target_include_directories(tdsreader PUBLIC cpp/include)
target_compile_features(tdsreader PUBLIC cxx_std_20)
