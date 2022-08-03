#include <stdlib.h>

#define A(i, j) a[(j)*lda + (i)]

float drand48();

void random_matrix(int m, int n, float *a, int lda)
{
    int i, j;

    for (j = 0; j < n; j++)
        for (i = 0; i < m; i++)
            A(i, j) = 2.f * drand48() - 1.f;
}

#ifdef WIN32
#define m 0x100000000LL
#define c 0xB16
#define a 0x5DEECE66DLL

static unsigned long long seed = 1;

float drand48()
{
    seed = (a * seed + c) & 0xFFFFFFFFFFFFLL;
    unsigned long long x = seed >> 16;
    return ((float)x / (float)m);
}

void srand48(unsigned int i)
{
    seed = (((long long int)i) << 16) | rand();
}
#endif // WIN32