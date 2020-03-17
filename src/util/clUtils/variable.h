#ifndef BENTOCL_VAR_H
#define BENTOCL_VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <stdbool.h>

typedef struct b_var{
    void *host;
    cl_mem device;
    size_t size;
} b_var;

b_var b_ulong(cl_context context, int N);
void writeVar(cl_command_queue queue, b_var var);
void readVar(cl_command_queue queue, b_var var);

#endif