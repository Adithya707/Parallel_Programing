#include<stdio.h>

#define BLOCK_SIZE 16

__global__ void gpu_matrix_mult(int * a, int n) {
  int idx = blockIdx.x;
  int idy = blockIdx.y;

  int element_replace;
  if (idx == idy) {
    element_replace = 0;
  } else if (idx > idy) {
    int fact = 1;
    int element = a[idy * n + idx];
    for (int i = 1; i <= element; i++) {
      fact = fact * i;
    }
    element_replace = fact;
  } else {
    int sum = 0, rem;
    int element = a[idy * n + idx];
    while (element > 0) {
      rem = element % 10;
      sum = sum + rem;
      element = element / 10;
    }
    element_replace = sum;
  }
  a[idy * n + idx] = element_replace;
}

int main(int argc, char
  const * argv[]) {
  int n;
  printf("please type in n\n");
  scanf("%d", & n);
  // allocate memory in host RAM
  int * h_a;
  cudaMallocHost((void ** ) & h_a, sizeof(int) * n * n);
  // random initialize matrix A
  printf("enter matrix A:\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", & h_a[i * n + j]);
    }
  }

  // Allocate memory space on the device
  int * d_a;
  cudaMalloc((void ** ) & d_a, sizeof(int) * n * n);

  // copy matrix A and B from host to device memory
  cudaMemcpy(d_a, h_a, sizeof(int) * n * n, cudaMemcpyHostToDevice);

  dim3 dimGrid(n, n);
  dim3 dimBlock(1, 1);

  gpu_matrix_mult << < dimGrid, dimBlock >>> (d_a, n);

  // Transfer results from device to host
  cudaMemcpy(h_a, d_a, sizeof(int) * n * n, cudaMemcpyDeviceToHost);

  // validate results computed by GPU
  printf("resultant matrix C:\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d ", h_a[i * n + j]);
    }
    printf("\n");
  }

  // free memory
  cudaFree(d_a);

  cudaFreeHost(h_a);

  return 0;
}
