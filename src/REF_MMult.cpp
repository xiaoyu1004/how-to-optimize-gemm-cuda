// CUDA runtime
#include "helper.h"
#include <cublas_v2.h>
#include <cuda_runtime.h>

#include <intrin.h>
#include <assert.h>
#include <stdlib.h>

// #ifdef _MSC_VER_ // for MSVC
// #define forceinline __forceinline
// #elif defined __GNUC__ // for gcc on Linux/Apple OS X
// #define forceinline __inline__ __attribute__((always_inline))
// #else
// #define forceinline
// #endif

// /* Create macros so that the matrices are stored in row-major order */
// #define A(i, j) a[(i)*lda + (j)]
// #define B(i, j) b[(i)*ldb + (j)]
// #define C(i, j) c[(i)*ldc + (j)]

// CUDA and CUBLAS functions
void REF_MMult(cublasHandle_t handle, int m, int n, int k,
              float *d_A, int lda,
              float *d_B, int ldb,
              float *d_C, int ldc)
{
    const float alpha = 1.0f;
    const float beta = 0.0f;
    checkCudaErrors(cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, n, m, k, &alpha,
                                d_B, n, d_A, m, &beta, d_C, k));
}