#include <iostream>
#include <stdio.h>
#include <cuda_runtime.h>
#include <string>
#include "utils.hpp"
#include "timer.hpp"
#include "reduce.hpp"
#include <cstring>
#include <memory>
#include <cmath>

int seed;
int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: ./build/reduction [size] [block_size]" << std::endl;
        return -1;
    }
    
    Timer timer;
    char str[100];
    int size       = std::stoi(argv[1]);
    int block_size = std::stoi(argv[2]);
    int grid_size  = size / block_size;

    float* h_idata = nullptr;
    float* h_odata = nullptr;
    h_idata = (float*)malloc(size * sizeof(float));
    h_odata = (float*)malloc(grid_size * sizeof(float));
    
    seed = 1;
    initMatrix(h_idata, size, seed);
    memset(h_odata, 0, grid_size * sizeof(float));

    // CPU Reduction
    timer.start_cpu();
    float sumOnCPU = ReduceOnCPU(h_idata, size);
    timer.stop_cpu();
    std::sprintf(str, "reduce in cpu, results: %f", sumOnCPU);
    timer.duration_cpu<Timer::ms>(str);

    //GPU warmup
    timer.start_gpu();
    ReduceOnGPUWithDivergence(h_idata, h_odata, size, block_size);
    timer.stop_gpu();
    // timer.duration_gpu<Timer::ms>("reduce in gpu warmup");

    //GPU Reduction with Divergence
    timer.start_gpu();
    ReduceOnGPUWithDivergence(h_idata, h_odata, size, block_size);
    timer.stop_gpu();
    float sumOnGPUWithDivergence = 0;
    for (int i = 0; i < grid_size; i++)
    {
        sumOnGPUWithDivergence += h_odata[i];
    }
    std::sprintf(str, "reduce in gpu with divergence, results: %f", sumOnGPUWithDivergence);
    timer.duration_gpu(str);

    //GPU Reduction without Divergence
    timer.start_gpu();
    ReduceOnGPUWithoutDivergence(h_idata, h_odata, size, block_size);
    timer.stop_gpu();
    float sumOnGPUWithoutDivergence = 0;
    for (int i = 0; i < grid_size; i++)
    {
        sumOnGPUWithoutDivergence += h_odata[i];
    }
    std::sprintf(str, "reduce in gpu without divergence, results: %f", sumOnGPUWithoutDivergence);
    timer.duration_gpu(str);

    free(h_idata);
    free(h_odata);
    return 0;
}

/******************************************************************
PS C:\Users\22681\Desktop\project\cudalearn\test_warp> ./build/Release/reduction 33554432 512
reduce in cpu, results: 16777216.000000  uses 13.787900 ms
reduce in gpu with divergence, results: 16779780.000000      uses 21.777023 ms
reduce in gpu without divergence, results: 16779780.000000   uses 20.462015 ms
 *****************************************************************/