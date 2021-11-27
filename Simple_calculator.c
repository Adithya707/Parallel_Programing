#include <stdio.h>
#include <mpi.h>



int main(int argc, char **argv)
{
    int rank,size,a,b,c,d,choice,ans,temp;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
       printf("Enter 1st number\n");
       scanf("%d",&a);
       printf("Enter 2nd number\n");
       scanf("%d",&b);
       printf("Enter 1:addition 2:Subtraction 3:Multiplication 4:Division \n");
       scanf("%d",&choice);
       if(choice == 1){
           MPI_Send(&a,1,MPI_INT,1,0,MPI_COMM_WORLD);
           MPI_Send(&b,1,MPI_INT,1,1,MPI_COMM_WORLD);
           MPI_Recv(&ans,1,MPI_INT,1,2,MPI_COMM_WORLD,&status);
           printf("The answer after addition is: %d \n",ans);
           MPI_Finalize();
       }
       else if(choice == 2){
          MPI_Send(&a,1,MPI_INT,2,0,MPI_COMM_WORLD);
          MPI_Send(&b,1,MPI_INT,2,1,MPI_COMM_WORLD);
          MPI_Recv(&ans,1,MPI_INT,2,2,MPI_COMM_WORLD,&status);
          printf("The answer after Subtraction is: %d \n",ans);
          MPI_Finalize();
       }
       else if(choice == 3){
          MPI_Send(&a,1,MPI_INT,3,0,MPI_COMM_WORLD);
          MPI_Send(&b,1,MPI_INT,3,1,MPI_COMM_WORLD);
          MPI_Recv(&ans,1,MPI_INT,3,2,MPI_COMM_WORLD,&status);
          printf("The answer after Multiplication is: %d \n",ans);
          MPI_Finalize();
       } 
       else if(choice == 4){
         MPI_Send(&a,1,MPI_INT,4,0,MPI_COMM_WORLD);
         MPI_Send(&b,1,MPI_INT,4,1,MPI_COMM_WORLD);
         MPI_Recv(&ans,1,MPI_INT,4,2,MPI_COMM_WORLD,&status);
         printf("The answer after division is: %d \n",ans);
         MPI_Finalize();
       }
       else{
         printf("Invalid Choice \n");
       }
    } 
    if(rank == 1){
       MPI_Recv(&c,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
       MPI_Recv(&d,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
       temp = c+d;
       MPI_Send(&temp,1,MPI_INT,0,2,MPI_COMM_WORLD);
     }
     else if(rank == 2){
       MPI_Recv(&c,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
       MPI_Recv(&d,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
       temp = c-d;
       MPI_Send(&temp,1,MPI_INT,0,2,MPI_COMM_WORLD);
     }
     else if(rank == 3){
       MPI_Recv(&c,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
       MPI_Recv(&d,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
       temp = c*d;
       MPI_Send(&temp,1,MPI_INT,0,2,MPI_COMM_WORLD);
     }
     else if(rank == 4){
       MPI_Recv(&c,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
       MPI_Recv(&d,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
       temp = c/d;
       MPI_Send(&temp,1,MPI_INT,0,2,MPI_COMM_WORLD);
     }

     return 0;
}
