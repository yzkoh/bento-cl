#include <string.h>
#include "verbose.h"

void verbose(char *output){
    #ifdef VERBOSE
    printf(".. %s\n", output);
    #endif
}

void verboseInline(char *output){
    #ifdef VERBOSE
    printf(".. %s", output);
    #endif
}

void verbosePrint(char *output){
    #ifdef VERBOSE
    printf("%s", output);
    #endif
}

void verboseBox(char *output){
    int outputLength = strlen(output);
    verbose(_generateDash(outputLength));
    verbose(output);
    verbose(_generateDash(outputLength));
}

void verboseList(cl_uint order, char *label, char *value ){
    char output[100];
    sprintf(output, "%d. %s: %s", order, label ,value);
    verbose(output);
}

void getDeviceDetails(cl_device_id device){
    cl_uint k=1;
    char output[100];

    verboseList(k++, deviceInfoFieldLabel(CL_DEVICE_NAME), getDeviceName(device));
    verboseList(k++, deviceInfoFieldLabel(CL_DEVICE_VERSION), getDeviceHardwareVersion(device));
    verboseList(k++, deviceInfoFieldLabel(CL_DRIVER_VERSION), getDeviceSoftwareVersion(device));
    verboseList(k++, deviceInfoFieldLabel(CL_DEVICE_TYPE), getDeviceType(device));
    sprintf(output, "%u", getDeviceCores(device));
    verboseList(k++, deviceInfoFieldLabel(CL_DEVICE_MAX_WORK_GROUP_SIZE), output);
    sprintf(output, "%u MHz", getDeviceFrequency(device));
    verboseList(k++, deviceInfoFieldLabel(CL_DEVICE_MAX_CLOCK_FREQUENCY), output);
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

// Get device details: field label
char *deviceInfoFieldLabel(cl_uint field){
    switch(field){
        case CL_DEVICE_NAME: return("Devices");
        case CL_DEVICE_VERSION: return("Hardware version");
        case CL_DRIVER_VERSION: return("Software version");
        case CL_DEVICE_OPENCL_C_VERSION: return("OpenCL C version");
        case CL_DEVICE_TYPE: return("Device type");
        case CL_DEVICE_MAX_COMPUTE_UNITS: return("Parallel compute units");
        case CL_DEVICE_MAX_WORK_GROUP_SIZE: return("Max work group size");
        case CL_DEVICE_MAX_WORK_ITEM_SIZES: return("Max work items");
        case CL_DEVICE_MAX_CLOCK_FREQUENCY: return("Max clock frequency");
        case CL_DEVICE_GLOBAL_MEM_SIZE: return("Device global memory");
        case CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE: return("Double precision supported");
        default: return("Unknown");
    }
}

// Generate dash 
char *_generateDash(int len){
    int i;
    char *output = malloc(sizeof(char)*len);
    for(i=0;i<len;i++){
        output[i] = '-';
    }
    output[i] = '\0';
    return output;
}