cmake_minimum_required(VERSION 3.15)
project(spectral_c)

set(CMAKE_CXX_STANDARD 14)

add_library(fft3d fft3d.cpp fft3d.h)
add_library(data data.cpp data.h)
add_executable(spectral_main main.cpp data fft3d)
target_link_libraries(spectral_main fftw3)
add_subdirectory(gtest)
