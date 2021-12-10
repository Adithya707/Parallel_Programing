#include <stdio.h>
#include <mpi.h>
#include <string.h>



int main(int argc, char **argv)
{
   int rank,size,i,j,fact=1;
   double sum0 =0.0,s[100],sum=0.0;
   int a[100],b[100],m;
   MPI_Status status;
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   if(rank==0){
     printf("Enter m value \n");
     scanf("%d",&m);
     printf("Enter %d values \n",(size*m));
     for(i=0;i<(size*m);i++){
       scanf("%d",&a[i]);
     }
   }
   MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
   MPI_Scatter(&a[0],m,MPI_INT,&b[0],m,MPI_INT,0,MPI_COMM_WORLD);
   for(i=0;i<m;i++){
     sum0+=b[i];
   }
   sum0 = sum0/m;
   MPI_Gather(&sum0,1,MPI_DOUBLE,&s,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
   if(rank==0){
      for(i=0;i<size;i++){
         sum += s[i];
      }
      printf("Total average is %lf \n",(sum)/size);
  }
  MPI_Finalize();
  return 0;
}
