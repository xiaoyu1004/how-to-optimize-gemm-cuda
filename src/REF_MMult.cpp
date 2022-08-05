#include <intrin.h>
#include <assert.h>
#include <stdlib.h>

/* Create macros so that the matrices are stored in row-major order */
#define A(i, j) a[(i)*lda + (j)]
#define B(i, j) b[(i)*ldb + (j)]
#define C(i, j) c[(i)*ldc + (j)]

#define nc 256
#define kc 128

void REF_MMult(int m, int n, int k,
               float *a, int lda,
               float *b, int ldb,
               float *c, int ldc)
{
    for (int i = 0; i < m; i += 4)
    {
        for (int j = 0; j < n; j += 4)
        {
            __m128 regs[4] = {_mm_setzero_ps()};
            for (int p = 0; p < k; ++p)
            {
                __m128 mb = _mm_load_ps(&B(p, j));

                __m128 ma_r0 = _mm_load_ps1(&A(i, p));
                regs[0] = _mm_fmadd_ps(ma_r0, mb, regs[0]);

                __m128 ma_r1 = _mm_load_ps1(&A(i + 1, p));
                regs[1] = _mm_fmadd_ps(ma_r1, mb, regs[1]);

                __m128 ma_r2 = _mm_load_ps1(&A(i + 2, p));
                regs[2] = _mm_fmadd_ps(ma_r2, mb, regs[2]);

                __m128 ma_r3 = _mm_load_ps1(&A(i + 3, p));
                regs[3] = _mm_fmadd_ps(ma_r3, mb, regs[3]);
            }
            // store c
            __m128 mc_r0 = _mm_add_ps(_mm_load_ps(&C(i, j)), regs[0]);
            __m128 mc_r1 = _mm_add_ps(_mm_load_ps(&C(i + 1, j)), regs[1]);
            __m128 mc_r2 = _mm_add_ps(_mm_load_ps(&C(i + 2, j)), regs[2]);
            __m128 mc_r3 = _mm_add_ps(_mm_load_ps(&C(i + 3, j)), regs[3]);

            _mm_store_ps(&C(i, j), mc_r0);
            _mm_store_ps(&C(i + 1, j), mc_r1);
            _mm_store_ps(&C(i + 2, j), mc_r2);
            _mm_store_ps(&C(i + 3, j), mc_r3);
        }
    }
}

// void REF_MMult(int m, int n, int k,
//                float *a, int lda,
//                float *b, int ldb,
//                float *c, int ldc)
// {
//     for (int p = 0; p < k; p += kc)
//     {
//         for (int j = 0; j < n; j += nc)
//         {

//         }
//     }
// }