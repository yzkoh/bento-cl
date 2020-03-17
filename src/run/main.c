#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CL/cl.h>
#include <time.h>
#include <unistd.h>

// #include "../util/clUtils/core.h"
#include "../util/clUtils/verbose.h"
#include "../util/clUtils/interface.h"
#include "../util/clUtils/core.h"
#include "../util/clUtils/variable.h"

cl_device_id device;
cl_context context;

void printArray(cl_ulong *arr, int N){
    for(int i=0; i<5; i++){
        printf("%ld, ",arr[i]);
    }
    printf(" ... ");
    for(int i=N-6;i<(N-1); i++){
        printf("%ld, ", arr[i]);
    }
    printf("%ld\n", arr[N-1]);
}

int main(void){

    // Disable GPU cache
    putenv("CUDA_CACHE_DISABLE=1");
    verboseBox("GPU CACHE DISABLED");


    // List all of the available devices in all platforms
    listAllDevices();
    verbose("");

    // User input to select device, if more than one device / platform is available.
    selectDevice(&device, &context);

    // Get command queue
    cl_command_queue queue = getCommandQueue(context, device);

    // Get kernel
    char *fileNames[] = {PROJECT_DIR "/kernels/sum.cl"}; // Add more files to combine dependencies
    cl_kernel sum = getKernel(device, context, fileNames, 1, "sum");


    verbose("");
    // Example
    // - Create buffer
    
    struct timespec start, end;
    double delta_us;
    char output[100];

    int ret;
    cl_ulong N = 20e6;
    cl_int iterations = 50;
    cl_ulong local_work_size = 1;

    b_var a, b, res;
    a = b_ulong(context, N);
    b = b_ulong(context, N);
    res = b_ulong(context, N);

    for(int i=0;i<N;i++){
        ((cl_ulong *) a.host)[i] = i+i;
        ((cl_ulong *) b.host)[i] = i+i;
    }

    // // Run with CPU.
    // verbose("[RUN] Running on CPU ... ");
    // clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    
    // for(int i=0;i<N;i++){
    //     for(int j=0;j<iterations;j++){host_res[i] = host_a[i] + host_b[i];}
    // }
    
    // clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    // delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    // sprintf(output, "Time used w/ CPU: %.3f ms\n", delta_us);
    // verbose(output);
    
    // Reset array
    for(int i=0;i<N;i++){((cl_ulong *) res.host)[i] = 0;}
    

    // Run on GPU
    verbose("[RUN] Running on GPU ... ");
    // clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    // Write variable to device
    writeVar(queue, a);
    writeVar(queue, b);
    writeVar(queue, res);

    // Set function argument
    void *args[] = {&a.device, &b.device, &res.device, &iterations};
    size_t args_size[] = {sizeof(cl_mem), sizeof(cl_mem), sizeof(cl_mem), sizeof(cl_int)}; 
    bclSetKernelArg(sum, 4, args_size, args);

    // Run function
    ret = clEnqueueNDRangeKernel(queue, sum, 1, NULL, &N, &local_work_size, 0, NULL, NULL);

    // Read variable from device
    ret = 0;
    readVar(queue, res);
    // clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    // delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    // sprintf(output, "Time used w/ GPU: %.3f ms", delta_us);
    // verbose(output);

    // // Print computed result.
    printArray(((cl_ulong *) res.host), N);

    return 0;
}