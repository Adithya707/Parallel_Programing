#include <stdio.h>
#include <mpi.h>
#include <string.h>



int main(int argc, char **argv)
{
   int rank,size,len,l,i;
   char a[50],b[50],c[50],d[50],ch;
   MPI_Status status;
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   if(rank == 0){
      printf("In process %d \n",rank);
      printf("Enter a string\n");
      scanf("%s",a);
      len = strlen(a);
      MPI_Ssend(&len,1,MPI_INT,1,0,MPI_COMM_WORLD);
      MPI_Ssend(a,len,MPI_CHAR,1,1,MPI_COMM_WORLD);
      MPI_Recv(b,len,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);
    }
    if(rank == 1){
       MPI_Recv(&l,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
       MPI_Recv(c,l,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
       printf("In process %d \n",rank);
       for(i=0;i<l;i++){
          ch = islower(c[i]) ? toupper(c[i]) : tolower(c[i]);
          putchar(ch);
          d[i] = ch;
       }
       MPI_Ssend(d,l,MPI_CHAR,0,2,MPI_COMM_WORLD);
       printf("\n");
   }
   MPI_Finalize();
   return 0;
}
