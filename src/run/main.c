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

    cl_ulong *host_a, *host_b, *host_res;
    host_a = (cl_ulong *) malloc(sizeof(cl_ulong)*N);
    host_b = (cl_ulong *) malloc(sizeof(cl_ulong)*N);
    host_res = (cl_ulong *) malloc(sizeof(cl_ulong)*N);
    for(int i=0;i<N;i++){host_a[i] = i+i; host_b[i] = i+i;}

    // Run with CPU.
    verbose("[RUN] Running on CPU ... ");
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<iterations;j++){host_res[i] = host_a[i] + host_b[i];}
    }
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    sprintf(output, "Time used w/ CPU: %.3f ms\n", delta_us);
    verbose(output);
    
    // Reset array
    for(int i=0;i<N;i++){host_res[i] = 0;}
    

    // Run on GPU
    verbose("[RUN] Running on GPU ... ");
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    // Create device buffer
    cl_mem device_a, device_b, device_res;
    device_a = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_ulong)*N, NULL, &ret);
    device_b = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_ulong)*N, NULL, &ret);
    device_res = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_ulong)*N, NULL, &ret);

    // Copy variables from host to device
    ret = clEnqueueWriteBuffer(queue, device_a, CL_TRUE, 0, sizeof(cl_ulong)*N, host_a, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(queue, device_b, CL_TRUE, 0, sizeof(cl_ulong)*N, host_b, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(queue, device_res, CL_TRUE, 0, sizeof(cl_ulong)*N, host_res, 0, NULL, NULL);

    // - Set function argument
    ret = clSetKernelArg(sum, 0, sizeof(cl_mem), &device_a);
    ret = clSetKernelArg(sum, 1, sizeof(cl_mem), &device_b);
    ret = clSetKernelArg(sum, 2, sizeof(cl_mem), &device_res);
    ret = clSetKernelArg(sum, 3, sizeof(cl_int), &iterations);

    // Run function
    ret = clEnqueueNDRangeKernel(queue, sum, 1, NULL, &N, &local_work_size, 0, NULL, NULL);

    // - Read from device
    ret = 0;
    ret = clEnqueueReadBuffer(queue, device_res, CL_TRUE, 0, sizeof(cl_ulong)*N, host_res, 0, NULL, NULL);
    if(ret) verbose("FAILED");
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    sprintf(output, "Time used w/ GPU: %.3f ms", delta_us);
    verbose(output);

    // Print computed result.
    // printArray(host_res, N);

    return 0;
}