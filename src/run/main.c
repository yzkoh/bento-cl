#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <CL/cl.h>

#include "../util/clUtils/core.h"
#include "../util/clUtils/verbose.h"

int main(void){

    char output[100];

    verbose(""); // new line

    // Get platforms
    cl_platform_id *platforms;
    cl_int platformCount;

    verbose("Looking for platform ...");
    platforms = getPlatforms(&platformCount);

    if(platformCount==0) verbose("No OpenCL platform available.");
    else{
        sprintf(output, "Number of OpenCL platforms: %d", platformCount);
        verbose(output);
    }
    verbose("");


    // Get devices for each platform
    cl_device_id *devices;
    cl_uint deviceCount;

    for(cl_uint i=0; i< platformCount; i++){
        sprintf(output, " PLATFORM %d ",i+1);
        verboseBox(output);

        devices = getDevices(platforms[i], &deviceCount);

        if(deviceCount==0) verbose("No OpenCL device available for this platform.");
        for(cl_uint j=0; j< deviceCount; j++){
            cl_uint k=1;
            verboseList(j+1, k++, deviceInfoFieldLabel(CL_DEVICE_NAME), getDeviceName(devices[j]));
            verboseList(j+1, k++, deviceInfoFieldLabel(CL_DEVICE_VERSION), getDeviceHardwareVersion(devices[j]));
            verboseList(j+1, k++, deviceInfoFieldLabel(CL_DRIVER_VERSION), getDeviceSoftwareVersion(devices[j]));
            verboseList(j+1, k++, deviceInfoFieldLabel(CL_DEVICE_TYPE), getDeviceType(devices[j]));
            sprintf(output, "%u", getDeviceCores(devices[j]));
            verboseList(j+1, k++, deviceInfoFieldLabel(CL_DEVICE_MAX_WORK_GROUP_SIZE), output);
            sprintf(output, "%u MHz", getDeviceFrequency(devices[j]));
            verboseList(j+1, k++, deviceInfoFieldLabel(CL_DEVICE_MAX_CLOCK_FREQUENCY), output);
        }
    }

    return 0;
}