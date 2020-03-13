#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CL/cl.h>

#include "../util/clUtils/core.h"

#define VERBOSE


cl_device_id *device;
cl_context *context;

int main(void){

    // Get platforms
    cl_platform_id *platforms;
    cl_int platformCount;
    getPlatforms(platforms, &platformCount);

    #ifdef VERBOSE
        if(platformCount == 0) printf("No OpenCL platforms available.\n");
        else printf("Number of OpenCL platforms: %d\n",platformCount);
    #endif

    return 0;
}