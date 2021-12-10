#include "mpi.h"
#include<stdio.h>
#include "math.h"

 

int main(int argc, char* argv[])
{
    int rank, size,z, m = 0, a[100],b[100],c[100], i, size1 = 0 ;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        fprintf(stdout, "Enter the value for 'M': \n");
        fflush(stdout);
        scanf("%d", &m);
        size1 = m * size;
        fprintf(stdout, "Enter %d elements : \n", size1);
        fflush(stdout);
        for (i = 0;i < size1;i++)
        {
            scanf("%d", &a[i]);
            c[i] = a[i];
        }
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, m, MPI_INT, b, m, MPI_INT, 0, MPI_COMM_WORLD);

 

    for (i = 0;i < m;i++)
        b[i] = (int)pow((float)b[i],rank+2);
    MPI_Gather(b, m, MPI_INT, a, m, MPI_INT, 0, MPI_COMM_WORLD);

 

    if (rank == 0)
    {
        printf("\n");
        for (i = 0;i <size1;i++)
        {
            z = ((i / m) + 2);
            fprintf(stdout, "The %d power of %d is %d \n",z,c[i],a[i]);
            fflush(stdout); } }
    MPI_Finalize();
    return 0; }
