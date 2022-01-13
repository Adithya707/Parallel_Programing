#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<string.h>

__global__ void Rev(char* a,char* c,int n){
    int i = threadIdx.x;
    int b = a[i];
    int r = 0;
    while (b > 0) {
        int digit = b % 10;
        r = r * 10 + digit;
        b /= 10;
    }
    c[i] = r;
}

int main(void){
    
    char *d_a,*d_c;
    int n;
    int size = sizeof(char);
    char a[20],c[20];
    printf("Enter string \n");
    scanf("%s",a);
    n = strlen(a);
    cudaEvent_t start, stop; // using cuda events to measure time
    float elapsed_time_ms;
    cudaEventCreate( &start );
    cudaEventCreate( &stop );
    cudaMalloc((void**)&d_a,(size*n));
    cudaMalloc((void**)&d_c,(size*n));
    cudaMemcpy(d_a,&a,(size*n),cudaMemcpyHostToDevice);
    cudaEventRecord( start, 0 ); // instrument code to measure start time
    Rev<<<1,n>>>(d_a,d_c,n);
    cudaMemcpy(&c,d_c,(size*n),cudaMemcpyDeviceToHost);
    cudaEventRecord( stop, 0 ); // instrument code to measure end time
cudaEventSynchronize( stop);
cudaEventElapsedTime( &elapsed_time_ms, start, stop );
printf("Time to calculate results: %f ms.\n", elapsed_time_ms);
    printf("Resultant array \n");
    for (int i = 0; i < n; i++)
        printf("%c ",c[i]);
    printf("\n");
    cudaFree(d_a);
    cudaFree(d_c);
    return 0;

    
}