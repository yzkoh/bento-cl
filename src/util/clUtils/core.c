#include <CL/cl_platform.h>

#include "core.h"

void getPlatforms(cl_platform_id *platforms, cl_int *platformCount){
    clGetPlatformIDs(0, NULL, platformCount);
    platforms = (cl_platform_id *) malloc(sizeof(cl_platform_id) * (*platformCount) );
    clGetPlatformIDs(*platformCount, platforms, NULL);
}

void getDevices(cl_platform_id platform, cl_device_id *devices, cl_uint *deviceCount){
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, deviceCount);
    devices = (cl_device_id *) malloc(sizeof(cl_device_id) * (*deviceCount) );
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, *deviceCount, devices, NULL);
}