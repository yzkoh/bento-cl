#include <CL/cl_platform.h>
#include <string.h>

#include "core.h"

void getPlatforms(cl_device_id *platforms, cl_int *platformCount){
    clGetPlatformIDs(0, NULL, platformCount);
    platforms = (cl_platform_id *) malloc(sizeof(cl_platform_id) * (*platformCount) );
    clGetPlatformIDs(*platformCount, platforms, NULL);

    #ifdef VERBOSE
    if(*platformCount == 0) printf("No OpenCL platforms available.\n");
    else printf("Number of OpenCL platforms: %d\n",*platformCount);
    #endif
}