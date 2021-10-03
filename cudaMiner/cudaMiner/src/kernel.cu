#include "cuda_runtime.h"
#include <iostream>
#include "cudaMiner.h"

__global__ void mykernel()
{
	printf("Hello, World!\n");
}

void cudaMiner::doCuda()
{
	mykernel<<<1,1>>>();
	cudaDeviceSynchronize();
}