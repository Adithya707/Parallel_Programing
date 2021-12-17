#include <stdio.h>
#include <mpi.h>
#include <string.h>



int main(int argc, char **argv)
{
  int rank,size,len,l,i,j,fact=0,search,n;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int a[size][size],b[size],c[size],d[size][size];
  if(rank==0){
    printf("Rnter 16 elements\n");
    for(i=0;i<size;i++){
      for(j=0;j<size;j++){
         scanf("%d",&a[i][j]);
      }
    }
  }
  MPI_Scatter(&a[0],4,MPI_INT,&b[0],4,MPI_INT,0,MPI_COMM_WORLD);

  MPI_Scan(&b,&c,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

  for(i=0;i<4;i++){
    printf("%d ",c[i]);
  }
  printf("\n");
  MPI_Finalize();
  return 0;
}
