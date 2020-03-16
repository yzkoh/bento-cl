#include <CL/cl_platform.h>

#include "core.h"
#include "verbose.h"

cl_platform_id *getPlatforms(cl_int *platformCount){
    clGetPlatformIDs(0, NULL, platformCount);
    cl_platform_id *platforms = (cl_platform_id *) malloc(sizeof(cl_platform_id) * (*platformCount) );
    clGetPlatformIDs(*platformCount, platforms, NULL);
    return platforms;
}

cl_device_id *getDevices(cl_platform_id platform, cl_uint *deviceCount){
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, deviceCount);
    cl_device_id *devices = (cl_device_id *) malloc(sizeof(cl_device_id) * (*deviceCount) );
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, *deviceCount, devices, NULL);
    return devices;
}

cl_context getContext(cl_device_id **devices, cl_uint num_devices, int *ret) {
    // Create OpenCL context
    cl_context context = NULL;
    context = clCreateContext(NULL, num_devices, *devices, NULL, NULL, ret);
    return context;
}

cl_command_queue getCommandQueue(cl_context context, cl_device_id device) {
    // Create command queue
    cl_int ret;
    char output[100];

    cl_command_queue queue = NULL;
    queue = clCreateCommandQueueWithProperties(context, device, NULL, &ret);
    verboseInline("[INIT] Create command queue: ");
    if ((int) ret == 0) {
        verbosePrint("SUCCESS\n");
    } else {
        sprintf(output, "Failed to create command queue. Error %i\n", ret);
        verbosePrint(output);
        return NULL;
    }
    return queue;
}

cl_kernel getKernel(cl_device_id device, cl_context context, char **fileNames, int numFiles, char *kernelName){
    FILE *fp;
    char *source_str;
    size_t source_size;
    cl_int ret;
    char output[100];
    char message[100];

    source_str = (char *) malloc(MAX_SOURCE_SIZE * numFiles);
    source_size = 0;

    for (int i = 0; i < numFiles; i++) {
        fp = fopen(fileNames[i], "r");
        if (!fp) {
            fprintf(stderr, "Failed to load file %s.\n", fileNames[i]);
            exit(1);
        }
        char *file_str = malloc(MAX_SOURCE_SIZE);
        size_t file_size = fread(file_str, 1, MAX_SOURCE_SIZE, fp);
        for (int j = 0; j < file_size; j++) {
            source_str[source_size + j] = file_str[j];
        }
        source_size += file_size;
        fclose(fp);
    }

    const char *strings[] = {source_str};
    const size_t sizes[] = {source_size};
    // Create kernel program from source
    cl_program program = NULL;
    program = clCreateProgramWithSource(context, 1, strings, sizes, &ret);
    verboseInline("[INIT] Create kernel program: ");
    if ((int) ret == 0) {
        verbosePrint("SUCCESS\n");
    } else {
        sprintf(output, "FAILED to create kernel program (%d)\n", ret);
        verbosePrint(output);
        return NULL;
    }

    cl_device_id devices[] = {device};
    // Build kernel program
    ret = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
    verboseInline("[INIT] Build kernel program: ");
    if ((int) ret == 0) {
        verbosePrint("SUCCESS\n");
    } else {
        sprintf(output, "FAILED to build kernel program (%d)\n", ret);
        verbosePrint(output);
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        // Allocate memory for the log
        char *log = (char *) malloc(log_size);

        // Get the log
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        // Print the log
        sprintf(output, "%s\n", log);
        verbose(output);
        return NULL;
    }

    // Create OpenCL kernel
    cl_kernel kernel = NULL;
    kernel = clCreateKernel(program, kernelName, &ret);
    verboseInline("[INIT] Create OpenCL kernel: ");
    if ((int) ret == 0) {
        verbosePrint("SUCCESS\n");
    } else {
        sprintf(output, "FAILED to create kernel (%d)\n", ret);
        verbosePrint(output);
        return NULL;
    }
    return kernel;
}