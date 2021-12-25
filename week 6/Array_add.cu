#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void add(int *a, int *b, int *c, int n)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

int main(void)
{

    int *d_a, *d_b, *d_c, n;
    int size = sizeof(int);
    printf("Enter size of array \n");
    scanf("%d", &n);
    int a[n * 2], b[n * 2], c[n * 2], i;
    cudaMalloc((void **)&d_a, (size * n));
    cudaMalloc((void **)&d_b, (size * n));
    cudaMalloc((void **)&d_c, (size * n));
    printf("Enter value for a and b\n");
    for (i = 0; i < n; i++)
    {
        printf("Enter valur for a[%d] ", i);
        scanf("%d", &a[i]);
        printf("Enter valur for b[%d] ", i);
        scanf("%d", &b[i]);
    }
    printf("\n");
    cudaMemcpy(d_a, &a, (size * n), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &b, (size * n), cudaMemcpyHostToDevice);
    add<<<1, n>>>(d_a, d_b, d_c, n);
    cudaMemcpy(&c, d_c, (size * n), cudaMemcpyDeviceToHost);
    printf("Resultant array \n");
    for (int i = 0; i < n; i++)
        printf("%d ", c[i]);
    printf("\n");
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}