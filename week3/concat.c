#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
    char A[100], A1[100], B[50], B1[50], C[100], E[100];
    int rank, size, i, x = 0, len,jmpp=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        fprintf(stdout, "Enter the first string : ");
        fflush(stdout);
        scanf("%s",A);
        fprintf(stdout, "Enter the second string : ");
        fflush(stdout);
        scanf("%s",A1);
        len = strlen(A) / size;
    }
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, len, MPI_CHAR, B, len, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(A1, len, MPI_CHAR, B1, len, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (i = 0;i < len;i++)
    {
        C[x++] = B[i];
        C[x++] = B1[i];
    }
    MPI_Gather(C, (len * 2), MPI_CHAR, E, (len * 2), MPI_CHAR, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        fprintf(stdout, "the resultant string is \n");
        fflush(stdout);
        for (i = 0;i < (len * size * 2);i++)
        {
            fprintf(stdout, "%c", E[i]);
           
            fflush(stdout);
        }
    printf("\n");
     }
    MPI_Finalize();
    return 0; }
