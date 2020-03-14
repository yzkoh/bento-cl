#include <CL/cl_platform.h>

#include "core.h"
#include "interface.h"
#include "verbose.h"

void listAllDevices(){

    char output[100];

    // Get platforms
    cl_platform_id *platforms;
    cl_int platformCount;

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
        sprintf(output, "PLATFORM %d",i+1);
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
}

void selectDevice(cl_device_id *deviceSelected, cl_context *deviceContext){

    int select = 1;
    char output[100];

    cl_platform_id *platforms;
    cl_int platformCount;
    platforms = getPlatforms(&platformCount);
    if(platformCount > 1){
        sprintf(output, "Enter platform number: (%d - %d)", 1, platformCount);
        verbose(output);
        select = requestInteger(1,1+platformCount);
    }

    cl_device_id *devices;
    cl_uint deviceCount;
    devices = getDevices(platforms[select-1], &deviceCount);
    if(deviceCount > 1){
        sprintf(output, "Enter device number: (%d - %d)", 1, deviceCount);
        verbose(output);
        select = requestInteger(1,1+deviceCount);
    }

    *deviceSelected = devices[select-1];
    devices[0] = *deviceSelected;
    *deviceContext = getContext(&devices, 1);
}

int requestInteger(int lowerBound, int upperBound){

    bool valid = false;
    int input;
    while(!valid){
        if(scanf("%d", &input) > 0 && input < upperBound && input >= lowerBound){
            valid = true;
        } else {
            verbose("Invalid input. Please try again.");
        }
    }
    return input;
}