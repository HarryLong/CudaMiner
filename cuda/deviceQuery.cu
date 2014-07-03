/* NOTE: This file contains sections of code taken from the NVIDIA_CUDA-5.0_Samples
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda_runtime.h>

#include "deviceQuery.h"

// 32-bit floating-point add, multiply, multiply-add Operations per Clock Cycle per Multiprocessor
// http://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#arithmetic-instructions__throughput-native-arithmetic-instructions
SMVal opsF32_A_M_MAD_perMPperCC[] =
{
    { 0x10, 8 },      // Tesla  Generation (SM 1.0) G80 class
    { 0x11, 8 },      // Tesla  Generation (SM 1.1) G8x class
    { 0x12, 8 },      // Tesla  Generation (SM 1.2) G9x class
    { 0x13, 8 },      // Tesla  Generation (SM 1.3) GT200 class
    { 0x20, 32 },     // Fermi  Generation (SM 2.0) GF100 class
    { 0x21, 48 },     // Fermi  Generation (SM 2.1) GF10x class
    { 0x30, 192 },    // Kepler Generation (SM 3.0) GK10x class
    { 0x35, 192 },    // Kepler Generation (SM 3.5) GK11x class
    { -1, -1 }
};

// 64-bit floating-point add, multiply, multiply-add Operations per Clock Cycle per Multiprocessor
// http://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#arithmetic-instructions__throughput-native-arithmetic-instructions
SMVal opsF64_A_M_MAD_perMPperCC[] =
{
    { 0x10, 0 },      // Tesla  Generation (SM 1.0) G80 class
    { 0x11, 0 },      // Tesla  Generation (SM 1.1) G8x class
    { 0x12, 0 },      // Tesla  Generation (SM 1.2) G9x class
    { 0x13, 1 },      // Tesla  Generation (SM 1.3) GT200 class
    { 0x20, 16 },     // Fermi  Generation (SM 2.0) GF100 class
    { 0x21, 4 },      // Fermi  Generation (SM 2.1) GF10x class
    { 0x30, 8 },      // Kepler Generation (SM 3.0) GK10x class
    { 0x35, 64 },     // Kepler Generation (SM 3.5) GK11x class
    { -1, -1 }
};


// Defined number of cores for SM of specific compute versions
SMVal coresPerSM[] =
//TODO 8 - replace all 'FIND_REAL_VALUE_IN_REFRENCE' by the correct value source from a reference (try Appendix F of the CUDA C PROGRAMMING GUIDE v5.0)
{
    { 0x10, 8 },      // Tesla Generation  (SM 1.0) G80   class
    { 0x11, 8 },      // Tesla Generation  (SM 1.1) G8x   class
    { 0x12, 8 },      // Tesla Generation  (SM 1.2) G9x   class
    { 0x13, 8 },      // Tesla Generation  (SM 1.3) GT200 class
    { 0x20, 32 },     // Fermi Generation  (SM 2.0) GF100 class
    { 0x21, 48 },     // Fermi Generation  (SM 2.1) GF10x class
    { 0x30, 192 },    // Kepler Generation (SM 3.0) GK10x class
    { 0x35, 192 },    // Kepler Generation (SM 3.5) GK11x class
    { -1, -1 }
};

int getValFromSMVer(int major, int minor, SMVal* vals)
{
  int index = 0;

  while (vals[index].SM != -1)
  {
    int thisSM = ((major << 4) + minor);
    int testSM = vals[index].SM;

    if (vals[index].SM == ((major << 4) + minor))
      return vals[index].value;

    index++;
  }
  
  // If we get here we didn't find the value in the array
  return -1;
}

int printDeviceInfo()
{
  printf( " --== GPGPU workshop CUDA Device Query (Runtime API) ==--\n\n");
  cudaError_t return_status;
  int currentDevice;
  int deviceCount;
  char pciBusId[1024];
  cudaFuncCache cacheConfig;
  float maxGflops;

  // NUMBER OF DEVICES
  {
    CUDA_SAFE_CALL( cudaGetDeviceCount(&deviceCount) , "Failed to get device count cusing cudaGetDeviceCount");
  }

  if (deviceCount > 0)
  {
    printf("There are %i CUDA enabled devices on this node\n", deviceCount);

    int driverVersion = 0, runtimeVersion = 0;
    // DRIVER VERSION + RUNTIME VERSION
    {
      CUDA_SAFE_CALL( cudaDriverGetVersion ( &driverVersion ) , "Failed to get driver version using cudaDriverVersion");
      CUDA_SAFE_CALL( cudaRuntimeGetVersion ( &runtimeVersion ) , "Failed to get runtime version using cudaRuntimeGetVersion");
    }

    printf("  CUDA Driver Version    %d.%d \n", driverVersion / 1000,
        (driverVersion % 100) / 10);
    printf("  Runtime Version        %d.%d \n", runtimeVersion / 1000,
        (runtimeVersion % 100) / 10);

    for (int device = 0; device < deviceCount; device++)
    {
      cudaDeviceProp deviceProp;

      {
        CUDA_SAFE_CALL( cudaGetDevice(&currentDevice), "Failed to get device using cudaGetDevice" );
      }

      // Check if the the current device is 'device'
      if ( currentDevice != device)
      {
        fprintf(stderr, "ERROR: Device not set.\n");
        exit(EXIT_FAILURE);
      }

      {
        CUDA_SAFE_CALL( cudaGetDeviceProperties(&deviceProp, device), "Failed to get device properties using cudaGetDeviceProperties" );
      }

      {
        CUDA_SAFE_CALL( cudaDeviceGetPCIBusId(pciBusId, 1024, device), "Failed to get pci bus id using cudaDeviceGetPCIBusId" );
      }

      // Check if pciBusId has been set
      if ( strncmp(pciBusId, "Set me", 6) == 0 )
      {
        int ln = atoi(&(pciBusId[6]));
        fprintf(stderr, "ERROR: The variable 'pciBusId' has not been instantiated. Pleas correct line %d in '%s' by using an API call to get a relevant value.\n", ln, __FILE__); \
        exit(EXIT_FAILURE);
      }

      {
        CUDA_SAFE_CALL( cudaDeviceGetCacheConfig(&cacheConfig), "Failed to get pci bus id using cudaDeviceGetPCIBusId" );
      }

      printf("\nDevice %d: \"%s\"\n", device, deviceProp.name);
      printf("  CUDA Capability Major.Minor version number:    %d.%d\n",
          deviceProp.major, deviceProp.minor);

      char msg[256];
      sprintf(msg,
          "  Total amount of global memory:                 %.1f GBytes (%llu bytes)\n",
          (float) deviceProp.totalGlobalMem / 1073741824.0f,
          (unsigned long long) deviceProp.totalGlobalMem);
      printf("%s", msg);

      printf(
          "  (%2d) Multiprocessors x (%3d) CUDA Cores/MP:    %d CUDA Cores\n",
          deviceProp.multiProcessorCount,
          getValFromSMVer(deviceProp.major, deviceProp.minor, coresPerSM),
          getValFromSMVer(deviceProp.major, deviceProp.minor, coresPerSM)
              * deviceProp.multiProcessorCount);
      printf(
          "  GPU Clock rate:                                %.0f MHz (%0.2f GHz)\n",
          deviceProp.clockRate * 1e-3f, deviceProp.clockRate * 1e-6f);

      // TODO 7 : Calculate Theoretical max GFLOPS's
      {
        // Number of 32-bit Floating-point operations per clock cycle per Multiprocessor
        // 1.x --> 8
        // 2.0 --> 32
        // 2.1 --> 48
        // 3.x --> 192
        int flops_per_clockcycle_per_mp;
        switch(deviceProp.major){
          case 1:
            flops_per_clockcycle_per_mp = 8;
            break;
          case 2:
            switch(deviceProp.minor){
              case 0:
                flops_per_clockcycle_per_mp = 32;
                break;
              case 1:
                flops_per_clockcycle_per_mp = 48;
                break;
            }
            break;
          case 3:
            flops_per_clockcycle_per_mp = 192;
            break;
        }
        
        printf( " floating point operations per clock cycle per multiprocessor: %d\n",
          flops_per_clockcycle_per_mp);
        maxGflops = ((flops_per_clockcycle_per_mp*deviceProp.multiProcessorCount)*(deviceProp.clockRate*1e-6f)); // clockRate in KiloHertz (i.e n thousand clock cycles per second)

        // Well you can easily find this value, try -->  http://www.nvidia.com/object/tesla-servers.html
        // But how is it calculated?
        // This is going to involve some thinking and some research
        // Hint: have a look at Table 2 of the  CUDA C PROGRAMMING GUIDE v5.0 ( http://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html )
      }

      // Check if maxGflops has been set
      // if ( maxGflops < 0 )
      // {
      //   fprintf(stderr, "ERROR: The variable 'maxGflops' has not been calculated. Pleas correct line %d in '%s'. Calculate this value don't hard code it!\n", (int)(-1*maxGflops), __FILE__); \
      //   exit(EXIT_FAILURE);
      // }

      printf("  Max Gigaflops :                                %.1f Gflops\n",
           maxGflops);

      // This is supported in CUDA 5.0 (runtime API device properties)
      printf("  Memory Clock rate:                             %.0f Mhz\n",
          deviceProp.memoryClockRate * 1e-3f);
      printf("  Memory Bus Width:                              %d-bit\n",
          deviceProp.memoryBusWidth);

      if (deviceProp.l2CacheSize)
      {
        printf("  L2 Cache Size:                                 %d bytes (%0.1f KBytes)\n",
            deviceProp.l2CacheSize, deviceProp.l2CacheSize / 1024.0f );
      }

      printf(
          "  Max Texture Dimension Size (x,y,z)             1D=(%d), 2D=(%d,%d), 3D=(%d,%d,%d)\n",
          deviceProp.maxTexture1D, deviceProp.maxTexture2D[0],
          deviceProp.maxTexture2D[1], deviceProp.maxTexture3D[0],
          deviceProp.maxTexture3D[1], deviceProp.maxTexture3D[2]);
      printf(
          "  Max Layered Texture Size (dim) x layers        1D=(%d) x %d, 2D=(%d,%d) x %d\n",
          deviceProp.maxTexture1DLayered[0], deviceProp.maxTexture1DLayered[1],
          deviceProp.maxTexture2DLayered[0], deviceProp.maxTexture2DLayered[1],
          deviceProp.maxTexture2DLayered[2]);

      printf("  Total amount of constant memory:               %lu bytes (%0.1f KBytes)\n",
          deviceProp.totalConstMem, deviceProp.totalConstMem / 1024.0f );
      printf("  Total amount of shared memory per block:       %lu bytes (%0.1f KBytes)\n",
          deviceProp.sharedMemPerBlock, deviceProp.sharedMemPerBlock / 1024.0f );
      printf("  Total number of registers available per block: %d\n",
          deviceProp.regsPerBlock );
      printf("  Warp size:                                     %d\n",
          deviceProp.warpSize);
      printf("  Maximum number of threads per multiprocessor:  %d\n",
          deviceProp.maxThreadsPerMultiProcessor);
      printf("  Maximum number of threads per block:           %d\n",
          deviceProp.maxThreadsPerBlock);
      printf("  Maximum sizes of each dimension of a block:    %d x %d x %d\n",
          deviceProp.maxThreadsDim[0], deviceProp.maxThreadsDim[1],
          deviceProp.maxThreadsDim[2]);
      printf("  Maximum sizes of each dimension of a grid:     %d x %d x %d\n",
          deviceProp.maxGridSize[0], deviceProp.maxGridSize[1],
          deviceProp.maxGridSize[2]);
      printf("  Maximum memory pitch:                          %lu bytes (%0.1f GBytes)\n",
          deviceProp.memPitch, deviceProp.memPitch / 1073741824.0f );
      printf("  Texture alignment:                             %lu bytes\n",
          deviceProp.textureAlignment );
      printf(
          "  Concurrent copy and kernel execution:          %s with %d copy engine(s)\n",
          (deviceProp.deviceOverlap ? "Yes" : "No"),
          deviceProp.asyncEngineCount);
      printf("  Run time limit on kernels:                     %s\n",
          deviceProp.kernelExecTimeoutEnabled ? "Yes" : "No");
      printf("  Integrated GPU sharing Host Memory:            %s\n",
          deviceProp.integrated ? "Yes" : "No");
      printf("  Support host page-locked memory mapping:       %s\n",
          deviceProp.canMapHostMemory ? "Yes" : "No");
      printf("  Alignment requirement for Surfaces:            %s\n",
          deviceProp.surfaceAlignment ? "Yes" : "No");
      printf("  Device has ECC support:                        %s\n",
          deviceProp.ECCEnabled ? "Enabled" : "Disabled");
#ifdef WIN32
      printf("  CUDA Device Driver Mode (TCC or WDDM):         %s\n", deviceProp.tccDriver ? "TCC (Tesla Compute Cluster Driver)" : "WDDM (Windows Display Driver Model)");
#endif
      printf("  Device supports Unified Addressing (UVA):      %s\n",
          deviceProp.unifiedAddressing ? "Yes" : "No");
      printf("  PCI Bus:                                       %s\n",
          pciBusId);
      printf("  Device PCI Bus ID / PCI location ID:           %d / %d\n",
          deviceProp.pciBusID, deviceProp.pciDeviceID);

      const char *sComputeMode[] =
          {
              "Default (multiple host threads can use ::cudaSetDevice() with device simultaneously)",
              "Exclusive (only one host thread in one process is able to use ::cudaSetDevice() with this device)",
              "Prohibited (no host thread can use ::cudaSetDevice() with this device)",
              "Exclusive Process (many threads in one process is able to use ::cudaSetDevice() with this device)",
              "Unknown", NULL };

      printf("  Device Cache Configuration:                    ");
      if ( cacheConfig == cudaFuncCachePreferNone)
        printf("Default function cache configuration, no preference\n");
      else if ( cacheConfig == cudaFuncCachePreferShared)
        printf("Prefer larger shared memory and smaller L1 cache\n");
      else if ( cacheConfig == cudaFuncCachePreferShared)
        printf("Prefer larger L1 cache and smaller shared memory\n");
      else if ( cacheConfig == cudaFuncCachePreferEqual)
        printf("Prefer equal size L1 cache and shared memory\n");

      printf("  Compute Mode:\n");
      printf("     < %s >\n", sComputeMode[deviceProp.computeMode]);
    }
  }
  else
  {
    printf("There are no CUDA enabled devices in this node\n");
  }

  return 0;
}

// int main(int argc, char *argv[])
// {
//   printDeviceInfo();
// }
