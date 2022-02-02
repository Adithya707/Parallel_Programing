#include<stdio.h>
#define BLOCK_SIZE 16

__global__ void gpu_matrix_mult(int *a,int *b, int *c,int n)
{ 
    int row = blockIdx.y * blockDim.y + threadIdx.y; 
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int sum = 0;
    if( col < n && row < n) 
    {
        for(int i = 0; i < n; i++) 
        {
            sum += a[row * n + i] * b[i * n + col];
        }
        c[row * n + col] = sum;
    }
} 

__global__ void gpu_matrix_add(int *a,int *b, int *d, int n)
{ 
    int row = blockIdx.y * blockDim.y + threadIdx.y; 
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    d[row*blockDim.x+col]=a[row*blockDim.x+col]+b[row*blockDim.x+col];
} 


int main(int argc, char const *argv[])
{
    int n;
    printf("Please type in n\n");
    scanf("%d",&n);

    // allocate memory in host RAM
    int *h_a, *h_b, *h_c, *h_d;
    cudaMallocHost((void **) &h_a, sizeof(int)*n*n);
    cudaMallocHost((void **) &h_b, sizeof(int)*n*n);
    cudaMallocHost((void **) &h_c, sizeof(int)*n*n);
cudaMallocHost((void **) &h_d, sizeof(int)*n*n);

    // random initialize matrix A
    printf("enter matrix A:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        	scanf("%d",&h_a[i * n + j]);
        }
    }

    // random initialize matrix B
    printf("enter matrix B:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
        	scanf("%d",&h_b[i * n + j]);
        }
    }

    float gpu_elapsed_time_ms;

    // some events to count the execution time
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // start to count execution time of GPU version
    cudaEventRecord(start, 0);
    // Allocate memory space on the device 
    int *d_a, *d_b, *d_c , *d_d;
    cudaMalloc((void **) &d_a, sizeof(int)*n*n);
    cudaMalloc((void **) &d_b, sizeof(int)*n*n);
    cudaMalloc((void **) &d_c, sizeof(int)*n*n);
 cudaMalloc((void **) &d_d, sizeof(int)*n*n);

    // copy matrix A and B from host to device memory
    cudaMemcpy(d_a, h_a, sizeof(int)*n*n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, sizeof(int)*n*n, cudaMemcpyHostToDevice);

    unsigned int grid_rows = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned int grid_cols = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    dim3 dimGrid(grid_cols, grid_rows);
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
   
    gpu_matrix_mult<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, n);  
 gpu_matrix_add<<<dimGrid, dimBlock>>>(d_a, d_b, d_d,n);
  
    
    // Transfer results from device to host 
    cudaMemcpy(h_c, d_c, sizeof(int)*n*n, cudaMemcpyDeviceToHost);
cudaMemcpy(h_d, d_d, sizeof(int)*n*n, cudaMemcpyDeviceToHost);
    cudaThreadSynchronize();
    // time counting terminate
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    // compute time elapse on GPU computing
    cudaEventElapsedTime(&gpu_elapsed_time_ms, start, stop);
    printf("Time elapsed on matrix multiplication of %dx%d . %dx%d on GPU: %f ms.\n\n", n, n, n, n, gpu_elapsed_time_ms);


    // validate results computed by GPU
    printf("resultant matrix C:\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", h_c[i*n + j]);
        }
        printf("\n");
    }


printf("resultant matrix D:\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", h_d[i*n + j]);
        }
        printf("\n");
    }

    // free memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    cudaFreeHost(h_a);
    cudaFreeHost(h_b);
    cudaFreeHost(h_c);
    return 0;
}
