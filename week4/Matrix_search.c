#include <stdio.h>
#include <mpi.h>
#include <string.h>



int main(int argc, char **argv)
{
  int rank,size,len,l,i,j,fact=0,search,n;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int a[size][size],b[size];
  if(rank==0){
    printf("Rnter 9 elements\n");
    for(i=0;i<3;i++){
       for(j=0;j<3;j++){
          scanf("%d",&a[i][j]);
       }
    }
    printf("Enter search element\n");
    scanf("%d",&search);
  }
  MPI_Bcast(&search,1,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Scatter(&a[0],3,MPI_INT,&b[0],3,MPI_INT,0,MPI_COMM_WORLD);
  for(i=0;i<3;i++){
    printf("%d \n",b[i]);
    if(b[i]==search){
       fact++;
    }
  }
  MPI_Scan(&fact,&n,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
  if(rank==(size-1)){
     printf("Number of occurances of %d = %d \n",search,n);
  }
  MPI_Finalize();
  return 0;
}
