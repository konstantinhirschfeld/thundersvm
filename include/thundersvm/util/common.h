//
// Created by jiashuai on 17-9-21.
//

#ifndef THUNDERSVM_COMMON_H
#define THUNDERSVM_COMMON_H
#ifndef max

template<class T>
static inline T max(T x, T y) { return (x > y) ? x : y; }

#endif
#ifndef min

template<class T>
static inline T min(T x, T y) { return (x < y) ? x : y; }

#endif

inline int max2power(int n) {
    return int(pow(2, floor(log2f(float(n)))));
}
const int BLOCK_SIZE = 512;

const int NUM_BLOCKS = 32 * 56;

#define KERNEL_LOOP(i, n) \
  for (int i = blockIdx.x * blockDim.x + threadIdx.x; \
       i < (n); \
       i += blockDim.x * gridDim.x)

#ifdef USE_CUDA

#include "cuda_runtime_api.h"

#define CUDA_CHECK(condition) \
  /* Code block avoids redefinition of cudaError_t error */ \
  do { \
    cudaError_t error = condition; \
    CHECK_EQ(error, cudaSuccess) << " " << cudaGetErrorString(error); \
  } while (0)
#define SAFE_KERNEL_LAUNCH(kernel_name, ...)\
    kernel_name<<<NUM_BLOCKS,BLOCK_SIZE>>>(__VA_ARGS__);\
    CUDA_CHECK(cudaPeekAtLastError())
#else
#define __host__
#define __device__
#endif

#define NO_GPU \
LOG(FATAL)<<"Cannot use GPU when compiling without GPU"
#endif //THUNDERSVM_COMMON_H
