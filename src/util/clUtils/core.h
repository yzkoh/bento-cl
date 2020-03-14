#ifndef BENTOCL_CORE_H
#define BENTOCL_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

cl_platform_id *getPlatforms(cl_int *platformCount);
cl_device_id *getDevices(cl_platform_id platform, cl_uint *deviceCount);

char *getDeviceName(cl_device_id device);
char *getDeviceSoftwareVersion(cl_device_id device);
char *getDeviceHardwareVersion(cl_device_id device);
char *getDeviceType(cl_device_id device);
cl_uint getDeviceCores(cl_device_id device);
cl_uint getDeviceFrequency(cl_device_id device);

#endif