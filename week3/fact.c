#include <stdio.h>
#include <mpi.h>
#include <string.h>



int main(int argc, char **argv)
{
   int rank,size,i,fact=1;
   int a[50],b;
   MPI_Status status;
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   if(rank==0){
      printf("Enter %d elements \n",size);
      for(i=0;i<size;i++){
         scanf("%d",&a[i]);
      }
   }
   MPI_Scatter(&a,1,MPI_INT,&b,1,MPI_INT,0,MPI_COMM_WORLD);
   for(i=1;i<=b;i++){
      fact*=i;
   }
   printf("Factorial of %d is %d \n",b,fact);
   MPI_Finalize();
   return 0;
}
