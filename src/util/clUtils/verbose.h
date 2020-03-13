#ifndef BENTOCL_VERBOSE_H
#define BENTOCL_VERBOSE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

#define VERBOSE

void verbose(char *output);
char *_deviceInfoFieldLabel(cl_uint field);

#endif