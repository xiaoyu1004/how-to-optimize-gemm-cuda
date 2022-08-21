set(cuda_srcs compare_matrices.cpp
              copy_matrix.cpp
              dclock.cpp
              print_matrix.cpp
              random_matrix.cpp
              REF_MMult.cpp
              test_MMult.cpp)

list(APPEND cuda_srcs MMult_cuda_11.cu)

add_executable(MMult_cuda ${cuda_srcs})
target_link_libraries(MMult_cuda PRIVATE cudart cublas)