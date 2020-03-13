#include <string.h>
#include "verbose.h"

void verbose(char *output){
    #ifdef VERBOSE
    printf("[VERBOSE] %s\n", output);
    #endif
}

void verbosePlatform(cl_uint id){
    char output[100];
    verbose("--------------");
    sprintf(output, " PLATFORM %d ", id);
    verbose(output);
    verbose("--------------");
}

// Get device details: field label
char *_deviceInfoFieldLabel(cl_uint field){
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