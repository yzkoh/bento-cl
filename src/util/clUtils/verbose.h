#ifndef BENTOCL_VERBOSE_H
#define BENTOCL_VERBOSE_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

#define VERBOSE

void verbose(char *output);
void verboseBox(char *output);
void verboseList(cl_uint order, cl_uint subOrder, char *label, char *value );
char *deviceInfoFieldLabel(cl_uint field);

#endif