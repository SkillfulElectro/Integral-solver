#include <cuda_runtime.h>

// CUDA kernel function for computing the partial sum of the integral
template <typename T>
__global__ void IntegralKernel(T (*expression)(T), T x1, T x2, T distance, int Accurate_level, T* results) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    T local_sum = 0;

    for (int i = idx; i < Accurate_level; i += stride) {
        T x = x1 + i * distance;
        if (x < x2) {
            local_sum += distance * expression(x);
        }
    }

    results[idx] = local_sum;
}

// Example expression function to be used on the device
__device__ float deviceExpression(float x) {
    return sinf(x);
}

// Host function to call the CUDA kernel
template <typename T>
T Integral(T (*expression)(T), T x1, T x2, T Accurate_level) {
    int blockSize = 256;
    int numBlocks = (Accurate_level + blockSize - 1) / blockSize;

    T distance = (x2 - x1) / Accurate_level;
    T* results;
    cudaMallocManaged(&results, numBlocks * blockSize * sizeof(T));

    IntegralKernel<<<numBlocks, blockSize>>>(expression, x1, x2, distance, Accurate_level, results);
    cudaDeviceSynchronize();

    T sum = 0;
    for (int i = 0; i < numBlocks * blockSize; ++i) {
        sum += results[i];
    }

    cudaFree(results);

    return sum;
}
