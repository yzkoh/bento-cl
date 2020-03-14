#include <string.h>
#include "verbose.h"

void verbose(char *output){
    #ifdef VERBOSE
    printf("[VERBOSE] %s\n", output);
    #endif
}

void verboseBox(char *output){
    verbose("--------------");
    verbose(output);
    verbose("--------------");
}

void verboseList(cl_uint order, cl_uint subOrder, char *label, char *value ){
    char output[100];
    sprintf(output, "%d.%d %s: %s", order, subOrder, label ,value);
    verbose(output);
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