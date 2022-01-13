#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<string.h>

__global__ void st(char* a,char* c,int n){
    int i = threadIdx.x;
    if (a[i]>='A' && a[i]<='Z')
        c[i] = a[i] + 'a' - 'A';
    else if (a[i]>='a' && a[i]<='z')
        c[i] = a[i] + 'A' - 'a';
}

int main(void){
    
    char *d_a,*d_c;
    int n;
    int size = sizeof(char);
    char a[20],c[20];
    printf("Enter string \n");
    scanf("%s",a);
    n = strlen(a);
    cudaMalloc((void**)&d_a,(size*n));
    cudaMalloc((void**)&d_c,(size*n));
    cudaMemcpy(d_a,&a,(size*n),cudaMemcpyHostToDevice);
    cudaEvent_t start, stop;
    float elapsed_time_ms;
cudaEventCreate( &start );
cudaEventCreate( &stop );
cudaEventRecord( start, 0 );
    st<<<1,n>>>(d_a,d_c,n);
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