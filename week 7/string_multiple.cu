#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<string.h>

__global__ void sm(char* a,char* c,int n,int dup){
    int i = threadIdx.x;
    for(int j=0;j<dup;j++){
        c[i+j*n] = a[i];
    }
}

int main(void){
    
    char *d_a,*d_c;
    int n,dup;
    int size = sizeof(char);
    char a[200],c[200];
    printf("Enter string \n");
    scanf("%s",a);
    n = strlen(a);
    printf("Enter number of duplication \n");
    scanf("%d",&dup);
    cudaMalloc((void**)&d_a,(size*n*dup));
    cudaMalloc((void**)&d_c,(size*n*dup));
    cudaMemcpy(d_a,&a,(size*n),cudaMemcpyHostToDevice);
    cudaEvent_t start, stop; // using cuda events to measure time
float elapsed_time_ms;
cudaEventCreate( &start );
cudaEventCreate( &stop );
    sm<<<1,n>>>(d_a,d_c,n,dup);
    cudaMemcpy(&c,d_c,(size*n*dup),cudaMemcpyDeviceToHost);
    cudaEventRecord( stop, 0 ); // instrument code to measure end time
cudaEventSynchronize( stop);
cudaEventElapsedTime( &elapsed_time_ms, start, stop );
printf("Time to calculate results: %f ms.\n", elapsed_time_ms);
    printf("Resultant array \n");
    for (int i = 0; i <(n*dup); i++)
        printf("%c ",c[i]);
    printf("\n");
    cudaFree(d_a);
    cudaFree(d_c);
    return 0;    
}