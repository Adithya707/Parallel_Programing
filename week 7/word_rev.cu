#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<string.h>

__global__ void wr(char* a,char* c,int n){
    int i = threadIdx.x;
    if(c[i]!=32){
       c[i] = a[n-i-1];
    }
    else{
        c[i] = 32;
    }
    
}

int main(void){
    
    char *d_a,*d_c,*d_b;
    int n;
    int size = sizeof(char);
    char a[20],c[20];
    printf("Enter string \n");
    scanf("%s",a);
    n = strlen(a);
    cudaMalloc((void**)&d_a,(size*n));
    cudaMalloc((void**)&d_c,(size*n));
    cudaMalloc((void**)&d_b,(size*n));
    cudaMemcpy(d_a,&a,(size*n),cudaMemcpyHostToDevice);
    cudaEvent_t start, stop; // using cuda events to measure time
float elapsed_time_ms;
cudaEventCreate( &start );
cudaEventCreate( &stop );
cudaEventRecord( start, 0 ); // instrument code to measure start time
    wr<<<1,n>>>(d_a,d_c,n);
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