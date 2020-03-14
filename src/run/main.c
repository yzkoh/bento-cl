#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CL/cl.h>

// #include "../util/clUtils/core.h"
#include "../util/clUtils/verbose.h"
#include "../util/clUtils/interface.h"

cl_device_id device;
cl_context context;

int main(void){

    // List all of the available devices in all platforms
    listAllDevices();
    verbose("");

    // User input to select device, if more than one device / platform is available.
    selectDevice(&device, &context);



    return 0;
}