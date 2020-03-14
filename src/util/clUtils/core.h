#ifndef BENTOCL_CORE_H
#define BENTOCL_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

cl_platform_id *getPlatforms(cl_int *platformCount);
cl_device_id *getDevices(cl_platform_id platform, cl_uint *deviceCount);
cl_context getContext(cl_device_id **devices, cl_uint num_devices, cl_int *ret);

#endif