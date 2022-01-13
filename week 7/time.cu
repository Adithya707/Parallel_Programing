#include <cuda.h>
#include <stdlib.h>
#define N 4096 // size of array
int main(int argc, char *argv[])
{
cudaEvent_t start, stop; // using cuda events to measure time
float elapsed_time_ms;
cudaEventCreate( &start );
cudaEventCreate( &stop );
cudaEventRecord( start, 0 ); // instrument code to measure start time
vectorAdd<<<B,T>>>(dev_a,dev_b,dev_c);
cudaMemcpy(c,dev_c, N*sizeof(int), cudaMemcpyDeviceToHost);
    cudaEventRecord( stop, 0 ); // instrument code to measure end time
    cudaEventSynchronize( stop);
    cudaEventElapsedTime( &elapsed_time_ms, start, stop );
    printf("Time to calculate results: %f ms.\n", elapsed_time_ms);
}