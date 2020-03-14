#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CL/cl.h>

// #include "../util/clUtils/core.h"
#include "../util/clUtils/verbose.h"
#include "../util/clUtils/interface.h"

cl_device_id deviceSelected;

int main(void){

    listAllDevices();
    deviceSelected = selectDevice();

    return 0;
}