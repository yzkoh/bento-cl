#include <CL/cl_platform.h>

#include "core.h"

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

char *getDeviceName(cl_device_id device){
    char *value;
    size_t valueSize;

    clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &valueSize);
    value = (char *) malloc(valueSize);
    clGetDeviceInfo(device, CL_DEVICE_NAME, valueSize, value, NULL);
    return value;
}

char *getDeviceSoftwareVersion(cl_device_id device){
    char *value;
    size_t valueSize;

    clGetDeviceInfo(device, CL_DRIVER_VERSION, 0, NULL, &valueSize);
    value = (char *) malloc(valueSize);
    clGetDeviceInfo(device, CL_DRIVER_VERSION, valueSize, value, NULL);
    return value;
}

char *getDeviceHardwareVersion(cl_device_id device){
    char *value;
    size_t valueSize;

    clGetDeviceInfo(device, CL_DEVICE_VERSION, 0, NULL, &valueSize);
    value = (char *) malloc(valueSize);
    clGetDeviceInfo(device, CL_DEVICE_VERSION, valueSize, value, NULL);
    return value;
}

char *getDeviceType(cl_device_id device){
    cl_device_type deviceType;
    clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(deviceType), &deviceType, NULL);
    if (deviceType == CL_DEVICE_TYPE_CPU) return("CPU");
    else if (deviceType == CL_DEVICE_TYPE_GPU) return ("GPU");
    else if (deviceType == CL_DEVICE_TYPE_ACCELERATOR) return ("ACCELERATOR");
}

cl_uint getDeviceCores(cl_device_id device){
    size_t deviceCores;
    clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(deviceCores), &deviceCores, NULL);
    return (cl_uint)deviceCores;
}

cl_uint getDeviceFrequency(cl_device_id device){
    cl_uint deviceFrequency;
    clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(deviceFrequency), &deviceFrequency, NULL);
    return deviceFrequency;
}