#include <stdio.h>
#include <mpi.h>
#include <string.h>



int main(int argc, char **argv)
{
  int rank,size,len,l,i,fact,total,n;
  char a[50],b[50],c[50],d[50],ch;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  n = rank+1;
  MPI_Scan(&n,&fact,1,MPI_INT,MPI_PROD,MPI_COMM_WORLD);
  MPI_Scan(&fact,&total,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
  if(rank==(size-1)){
    printf("Total of addition of factorial of %d = %d \n",size,total);
  }
  MPI_Finalize();
  return 0;
}
