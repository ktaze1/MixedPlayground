﻿//#include <stdio.h>
//#include <stdlib.h>
//#include <device_launch_parameters.h>
//#include <cuda_runtime.h>
//
//__global__ void print_from_gpu(void) {
//    printf("Hello World! from thread [%d, %d] \
//        From device \n",
//        threadIdx.x, blockIdx.x);
//}
//
//int main(void) {
//    printf("Hello World from host!\n");
//    print_from_gpu<<<1,2>>> ();
//    cudaDeviceSynchronize();
//    return 0;
//}