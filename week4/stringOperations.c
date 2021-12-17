#include<stdio.h>
#include<mpi.h>


int main(int argc, char *argv[]){
    int rank,size;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int i, totalLength;
    char S[size], sum[size], A[size*size], c;
    double t1,t2,absTime,totalTime;
    if(rank==0){
        printf("\nEnter String of length %d : ",size);
        scanf("%s",S);
    }
    t1 = MPI_Wtime();

    MPI_Scatter(&S, 1, MPI_CHAR, &c, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    for(i=0; i<size; i++)
        if(i<rank+1)
            sum[i]=c;
        else
            sum[i]='@';
    MPI_Gather(&sum, size, MPI_CHAR, &A, size, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    t2 = MPI_Wtime();
    absTime =t2-t1;

    printf("\nPROCESSOR %d | Time taken: %lf\n", rank, absTime);

    MPI_Reduce(&absTime, &totalTime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank==0){
        for(i=0; i<size*size; i++){
            if (A[i] != '@')
                printf("%c",A[i]);
        }

        printf("\nTotal time taken is %lf\n", totalTime);
    }
    MPI_Finalize();
    printf("\n");
    return 0;
}