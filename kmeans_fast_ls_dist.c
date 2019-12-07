#include <stdio.h>
#include <math.h>
#include "fast_code_utils.h"
#include <immintrin.h>
#include <stdlib.h>
#include <malloc.h>
#define SIMD_FMADD(dest,src2,src1) \
__asm__ __volatile__( \
    "VFMADD231PD %[rsrca], %[rsrcb], %[rdest]\n" \
    : [rdest] "+x" (dest) \
    : [rsrcb] "x" (src2), [rsrca] "x" (src1) \
)

#define SIMD_SUB(dest,src2,src1) \
__asm__ __volatile__( \
    "VSUBPD %[rsrca], %[rsrcb], %[rdest]\n" \
    : [rdest] "+x" (dest) \
    : [rsrcb] "x" (src2), [rsrca] "x" (src1) \
)



// Registers m256 
// Store - K, N, D
// Subtraction - NK/4, N major order, (N,K) - [00,10,20,30], [40,50,60,70],[01,11,21,31],[41,51,61,71],[02,12,22,32],[42,52,62,72] - 6 registers
// Dist - NK/4 - Same order
// 
// 
// Init Square
// for i=0:D
// Load X - 2 registers
// Load C - 1 register
// for j=0:N
// for k=0:K
// Broadcast C
// Compute Subtract
// Update Square
//
//


void label_assignment(double *X, double *C, double *dist, int *labels)
{

    __m256d dist00_3={0},dist04_7={0},dist10_3={0},dist14_7={0},dist20_3={0},dist24_7={0},dist30_3={0},dist34_7={0};     
    __m256d x0_3,x4_7,c,ck,sub00_3={0},sub04_7={0},sub10_3={0},sub14_7={0},sub20_3={0},sub24_7={0},sub30_3={0},sub34_7={0};

    // D = 0
    x0_3 = _mm256_load_pd(X);
    x4_7 = _mm256_load_pd(X+4);
    c = _mm256_load_pd(C);

    ck = _mm256_set1_pd(c[0]);
    SIMD_SUB(sub00_3,x0_3,ck);
    SIMD_SUB(sub04_7,x4_7,ck);
    ck = _mm256_set1_pd(c[1]);
    SIMD_SUB(sub10_3,x0_3,ck);
    SIMD_SUB(sub14_7,x4_7,ck);
    ck = _mm256_set1_pd(c[2]);
    SIMD_SUB(sub20_3,x0_3,ck);
    SIMD_SUB(sub24_7,x4_7,ck);
    ck = _mm256_set1_pd(c[3]);
    SIMD_SUB(sub30_3,x0_3,ck);
    SIMD_SUB(sub34_7,x4_7,ck);
    //dist00_3 += sub00_3*sub00_3;
    SIMD_FMADD(dist00_3,sub00_3,sub00_3);
    //dist04_7 += sub04_7*sub04_7;
    SIMD_FMADD(dist04_7,sub04_7,sub04_7);
    //dist10_3 += sub10_3*sub10_3;
    SIMD_FMADD(dist10_3,sub10_3,sub10_3);
    //dist14_7 += sub14_7*sub14_7;
    SIMD_FMADD(dist14_7,sub14_7,sub14_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist20_3,sub20_3,sub20_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist24_7,sub24_7,sub24_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist30_3,sub30_3,sub30_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist34_7,sub34_7,sub34_7);


    // D = 1
    x0_3 = _mm256_load_pd(X+8);
    x4_7 = _mm256_load_pd(X+12);
    c = _mm256_load_pd(C+4);

    ck = _mm256_set1_pd(c[0]);
    //sub00_3 = x0_3 - ck;
    SIMD_SUB(sub00_3,x0_3,ck);
    //sub04_7 = x4_7 - ck;
    SIMD_SUB(sub04_7,x4_7,ck);
    ck = _mm256_set1_pd(c[1]);
    //sub10_3 = x0_3 - ck;
    SIMD_SUB(sub10_3,x0_3,ck);
    //sub14_7 = x4_7 - ck;
    SIMD_SUB(sub14_7,x4_7,ck);
    ck = _mm256_set1_pd(c[2]);
    //sub20_3 = x0_3 - ck;
    SIMD_SUB(sub20_3,x0_3,ck);
    //sub24_7 = x4_7 - ck;
    SIMD_SUB(sub24_7,x4_7,ck);
    ck = _mm256_set1_pd(c[3]);
    SIMD_SUB(sub30_3,x0_3,ck);
    SIMD_SUB(sub34_7,x4_7,ck);
    //dist00_3 += sub00_3*sub00_3;
    SIMD_FMADD(dist00_3,sub00_3,sub00_3);
    //dist04_7 += sub04_7*sub04_7;
    SIMD_FMADD(dist04_7,sub04_7,sub04_7);
    //dist10_3 += sub10_3*sub10_3;
    SIMD_FMADD(dist10_3,sub10_3,sub10_3);
    //dist14_7 += sub14_7*sub14_7;
    SIMD_FMADD(dist14_7,sub14_7,sub14_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist20_3,sub20_3,sub20_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist24_7,sub24_7,sub24_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist30_3,sub30_3,sub30_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist34_7,sub34_7,sub34_7);



    // D = 2
    x0_3 = _mm256_load_pd(X+16);
    x4_7 = _mm256_load_pd(X+20);
    c = _mm256_load_pd(C+8);

    ck = _mm256_set1_pd(c[0]);
    //sub00_3 = x0_3 - ck;
    SIMD_SUB(sub00_3,x0_3,ck);
    //sub04_7 = x4_7 - ck;
    SIMD_SUB(sub04_7,x4_7,ck);
    ck = _mm256_set1_pd(c[1]);
    //sub10_3 = x0_3 - ck;
    SIMD_SUB(sub10_3,x0_3,ck);
    //sub14_7 = x4_7 - ck;
    SIMD_SUB(sub14_7,x4_7,ck);
    ck = _mm256_set1_pd(c[2]);
    //sub20_3 = x0_3 - ck;
    SIMD_SUB(sub20_3,x0_3,ck);
    //sub24_7 = x4_7 - ck;
    SIMD_SUB(sub24_7,x4_7,ck);
    ck = _mm256_set1_pd(c[3]);
    SIMD_SUB(sub30_3,x0_3,ck);
    SIMD_SUB(sub34_7,x4_7,ck);
    //dist00_3 += sub00_3*sub00_3;
    SIMD_FMADD(dist00_3,sub00_3,sub00_3);
    //dist04_7 += sub04_7*sub04_7;
    SIMD_FMADD(dist04_7,sub04_7,sub04_7);
    //dist10_3 += sub10_3*sub10_3;
    SIMD_FMADD(dist10_3,sub10_3,sub10_3);
    //dist14_7 += sub14_7*sub14_7;
    SIMD_FMADD(dist14_7,sub14_7,sub14_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist20_3,sub20_3,sub20_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist24_7,sub24_7,sub24_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist30_3,sub30_3,sub30_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist34_7,sub34_7,sub34_7);



    // D = 3
    x0_3 = _mm256_load_pd(X+24);
    x4_7 = _mm256_load_pd(X+28);
    c = _mm256_load_pd(C+12);

    ck = _mm256_set1_pd(c[0]);
    //sub00_3 = x0_3 - ck;
    SIMD_SUB(sub00_3,x0_3,ck);
    //sub04_7 = x4_7 - ck;
    SIMD_SUB(sub04_7,x4_7,ck);
    ck = _mm256_set1_pd(c[1]);
    //sub10_3 = x0_3 - ck;
    SIMD_SUB(sub10_3,x0_3,ck);
    //sub14_7 = x4_7 - ck;
    SIMD_SUB(sub14_7,x4_7,ck);
    ck = _mm256_set1_pd(c[2]);
    //sub20_3 = x0_3 - ck;
    SIMD_SUB(sub20_3,x0_3,ck);
    //sub24_7 = x4_7 - ck;
    SIMD_SUB(sub24_7,x4_7,ck);
    ck = _mm256_set1_pd(c[3]);
    SIMD_SUB(sub30_3,x0_3,ck);
    SIMD_SUB(sub34_7,x4_7,ck);
    //dist00_3 += sub00_3*sub00_3;
    SIMD_FMADD(dist00_3,sub00_3,sub00_3);
    //dist04_7 += sub04_7*sub04_7;
    SIMD_FMADD(dist04_7,sub04_7,sub04_7);
    //dist10_3 += sub10_3*sub10_3;
    SIMD_FMADD(dist10_3,sub10_3,sub10_3);
    //dist14_7 += sub14_7*sub14_7;
    SIMD_FMADD(dist14_7,sub14_7,sub14_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist20_3,sub20_3,sub20_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist24_7,sub24_7,sub24_7);
    //dist20_3 += sub20_3*sub20_3;
    SIMD_FMADD(dist30_3,sub30_3,sub30_3);
    //dist24_7 += sub24_7*sub24_7;
    SIMD_FMADD(dist34_7,sub34_7,sub34_7);
}


int main()
{
    double *X, *C, *dist;
    posix_memalign((void*)&X, 64, 8*4*sizeof(double));
    posix_memalign((void*)&C, 64, (4*4)*sizeof(double));
    posix_memalign((void*)&dist, 64, 8*3*sizeof(double));

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            dist[i*3+j] = 0.0;
        }
    }

    int *labels;
    posix_memalign((void*)&labels, 64, 8*sizeof(int));

    unsigned long long int st,et;
    double gflops = 0.0;

    for (int i = 0; i < 10000; i++)
    {
        st = rdtsc();
        label_assignment(X,C,dist,labels);
        et = rdtsc();
        gflops += (4*8*4*3)*(2.4/3.3)/((et-st)*10000.0);
    }
    printf("%f\n",gflops);
    return 0;
}

