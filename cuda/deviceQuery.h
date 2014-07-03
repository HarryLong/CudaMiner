#ifndef DEVICE_QUERY_H
#define DEVICE_QUERY_H

#include "cudaHeader.h"

int getValFromSMVer(int major, int minor, SMVal* vals);
int printDeviceInfo();

#endif //DEVICE_QUERY_H 
