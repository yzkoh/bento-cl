#ifndef BENTOCL_INTERFACE_H
#define BENTOCL_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

void listAllDevices();
int requestInteger(int lowerBound, int upperBound);
cl_device_id selectDevice();

#endif