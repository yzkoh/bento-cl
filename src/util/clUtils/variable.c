#include <CL/cl_platform.h>
#include "variable.h"
#include "verbose.h"

b_var b_ulong(cl_context context, int N){
    int ret;
    b_var res;
    res.size = sizeof(cl_ulong)*N;
    res.host = (cl_ulong *) malloc(sizeof(cl_ulong)*N);
    res.device = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_ulong)*N, NULL, &ret);
    if(ret){
        verbose("Error");
        exit(0);
    }
    return res;
}

// Write to device: blocking
void writeVar(cl_command_queue queue, b_var var){
    int ret;
    ret = clEnqueueWriteBuffer(queue, var.device, CL_TRUE, 0, var.size, var.host, 0, NULL, NULL);
    if(ret){
        verbose("Error");
        exit(0);
    }
}

// Read from device: blocking
void readVar(cl_command_queue queue, b_var var){
    int ret;
    ret = clEnqueueReadBuffer(queue, var.device, CL_TRUE, 0, var.size, var.host, 0, NULL, NULL);
    if(ret){
        verbose("Error");
        exit(0);
    }
}