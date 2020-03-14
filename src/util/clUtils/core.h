#ifndef BENTOCL_CORE_H
#define BENTOCL_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

#define MAX_SOURCE_SIZE (0x100000)

cl_platform_id *getPlatforms(cl_int *platformCount);
cl_device_id *getDevices(cl_platform_id platform, cl_uint *deviceCount);
cl_context getContext(cl_device_id **devices, cl_uint num_devices, int *ret);
cl_kernel getKernel(cl_device_id device, cl_context context, char **fileNames, int numFiles, char *kernelName);

#endif