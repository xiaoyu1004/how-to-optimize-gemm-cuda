cmake_minimum_required(VERSION 3.14)

if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    set(CMAKE_CUDA_ARCHITECTURES 75)
endif()

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xptxas=-v")

project(how-to-optimize-gemm LANGUAGES CXX CUDA)

# set(OpenBLAS_DIR ${PROJECT_SOURCE_DIR}/OpenBLAS-0.2.20)
# include(${OpenBLAS_DIR})

# add_subdirectory(OpenBLAS-0.2.20)
add_subdirectory(src)