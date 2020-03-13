#ifndef BENTOCL_CORE_H
#define BENTOCL_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

void getPlatforms(cl_platform_id *platforms, cl_int *platformCount);

#endif