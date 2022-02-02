%%cu
#include <stdio.h>

#include <cuda.h>

__global__ void testKernel(int * in , int * out, int size) {

  bool oddeven = true;
  __shared__ bool swappedodd;
  __shared__ bool swappedeven;

  int temp;

  while (1) {

    if (oddeven == true) {
      __syncthreads();

      swappedeven = false;

      __syncthreads();


      if (threadIdx.y == 0) {

        int idx = threadIdx.x;

        
        if (idx < (size / 2)) {
          if ( in [2 * idx] > in [2 * idx + 1]) {
            temp = in [2 * idx]; in [2 * idx] = in [2 * idx + 1]; in [2 * idx + 1] = temp;
            swappedeven = true;

          }
        }
      }
      __syncthreads();
    } else {

      __syncthreads();

      swappedodd = false;

      __syncthreads();

      if (threadIdx.y == 0) {

        int idx = threadIdx.x;
        if (idx < (size / 2) - 1) {
          if ( in [2 * idx + 1] > in [2 * idx + 2]) {

            temp = in [2 * idx + 1]; in [2 * idx + 1] = in [2 * idx + 2]; in [2 * idx + 2] = temp;
            swappedodd = true;

          }

        }

      }

      __syncthreads();

    }
    if (!(swappedodd || swappedeven))
      break;

    oddeven = !oddeven; //switch phase of sorting

  }

  __syncthreads();

  //Store this phase's in[] array to out[] array
  int idx = threadIdx.x;

  if (idx < size)
    out[idx] = in [idx];

}

int main(void) {
  int i;
  int * a_sorted;
  int * d_a, * d_sorted;
  int n = 6; //make sure to keep this even
  int size = sizeof(int) * n;



  cudaMalloc((void ** ) & d_a, size);
  cudaMalloc((void ** ) & d_sorted, size);

  int a[n] = {6,5,4,3,2,1};
  a_sorted = (int * ) malloc(size);

  printf("Enter the unsorted numbers:\n");

  

  //d_a -> destination. a -> source.
  //Host to device array copy
  cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

  //<<< >>> CUDA semantic
  testKernel << < 1, n >>> (d_a, d_sorted, n);

  //Device to Host array for final display (I/O)
  cudaMemcpy(a_sorted, d_sorted, size, cudaMemcpyDeviceToHost);

  for (i = 0; i < n; i++) {
    printf("%d\t", a_sorted[i]);
  }

  printf("\n");

  //free memory allocated by malloc and cudamalloc
  free(a_sorted);
  cudaFree(d_sorted);
  cudaFree(d_a);
}
