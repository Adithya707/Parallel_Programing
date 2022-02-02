%%cu
#include<stdio.h>

#include<cuda.h>

__global__ void sum(int * A, int * B, int * C, int n) {
  int idx = blockIdx.y * blockDim.y + threadIdx.y; 
  int idy = blockIdx.x * blockDim.x + threadIdx.x;
  int row = 0;
  int col = 0;
  if (idx < n && idy < n) {
    for(int i=0;i<n;i++){
        row += A[idx * n + i]; 
        col += A[i * n + idy];
    }
    B[idx] += row;
    C[idy] += col;
  }
}

int main() {
  int b[100], c[100], i;
  int * d_a, * d_b, * d_c;
  int size = sizeof(int);
  int n = 3;
  cudaMalloc((void ** ) & d_a, size * n * n);
  cudaMalloc((void ** ) & d_b, size * n);
  cudaMalloc((void ** ) & d_c, size * n);
  printf("Enter array elements \n");
  int a[9] = {
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9
  };
  cudaMemcpy(d_a, & a, size * n * n, cudaMemcpyHostToDevice);
  dim3 dimBlock(n, n);
  dim3 dimGrid(1, 1);
  sum << < dimGrid, dimBlock >>> (d_a, d_b, d_c, n);
  cudaMemcpy( & b, d_b, size * n, cudaMemcpyDeviceToHost);
  cudaMemcpy( & c, d_c, size * n, cudaMemcpyDeviceToHost);
  for (i = 0; i < n; i++) {
    printf("Sum of row %d is %d \n", i + 1, b[i]);
    printf("Sum of column %d is %d \n", i + 1, c[i]);
  }
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
  return 0;
}
