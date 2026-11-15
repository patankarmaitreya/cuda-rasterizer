#include <cstdio>
#include <cuda_ops.hpp>

__global__ void fill_values(const int* input, int* output, int count, int multiplier){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < count)
    {
        output[index] = input[index] * multiplier;
    }
}

bool multiplyValues(const int* input, int* output, int count, int multiplier){
    bool success = true;

    constexpr int threadsPerBlock = 32;

    int* d_input = nullptr;
    int* d_output = nullptr;

    int blocks = (count + threadsPerBlock - 1) / threadsPerBlock;
    size_t size = count * sizeof(int);

    cudaError_t err_alloc_in;
    cudaError_t err_alloc_out;
    cudaError_t err_cpy_in;
    cudaError_t err_launch;
    cudaError_t err_sync;
    cudaError_t err_cpy_out;
    
    err_alloc_in = cudaMalloc(reinterpret_cast<void**>(&d_input), size);
    
    if(err_alloc_in != cudaSuccess){
        fprintf(stderr, "%s\n", cudaGetErrorString(err_alloc_in));
        success = false;
        goto cleanup;
    } 
    
    err_alloc_out = cudaMalloc(reinterpret_cast<void**>(&d_output), size);
    
    if(err_alloc_out != cudaSuccess){
        fprintf(stderr, "%s\n", cudaGetErrorString(err_alloc_out));
        success = false;
        goto cleanup;
    } 

    err_cpy_in = cudaMemcpy(d_input, input, size, cudaMemcpyHostToDevice);

    if(err_cpy_in != cudaSuccess){
        fprintf(stderr, "%s\n", cudaGetErrorString(err_cpy_in));
        success = false;
        goto cleanup;
    } 
    
    fill_values<<<blocks,threadsPerBlock>>>(d_input, d_output, count, multiplier);
    
    err_launch = cudaGetLastError();

    if(err_launch != cudaSuccess){
        fprintf(stderr, "%s\n", cudaGetErrorString(err_launch));
        success = false;
        goto cleanup;
    } 

    err_sync =cudaDeviceSynchronize();

    if(err_sync != cudaSuccess){
        fprintf(stderr, "%s\n", cudaGetErrorString(err_sync));
        success = false;
        goto cleanup;
    } 

    err_cpy_out = cudaMemcpy(output, d_output, size, cudaMemcpyDeviceToHost);

    if(err_cpy_out != cudaSuccess){
        fprintf(stderr, "%s\n", cudaGetErrorString(err_cpy_out));
        success = false;
        goto cleanup;
    } 

    cleanup:
        if(d_input != nullptr){
            cudaError_t err_free_in = cudaFree(d_input);

            if (err_free_in != cudaSuccess){
                fprintf(stderr, "%s\n", cudaGetErrorString(err_free_in));
                success = false;
            }
        }

        if(d_output != nullptr){                 
            cudaError_t err_free_out = cudaFree(d_output);

            if(err_free_out != cudaSuccess){
                fprintf(stderr, "%s\n", cudaGetErrorString(err_free_out));
                success = false;
            }
        }

    return success;
}