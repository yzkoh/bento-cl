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

cl_context getContext(cl_device_id **devices, cl_uint num_devices, cl_int *ret) {
    // Create OpenCL context
    cl_context context = NULL;
    context = clCreateContext(NULL, num_devices, *devices, NULL, NULL, ret);
    return context;
}