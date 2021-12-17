#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define MAX 25

int main(int argc,char** argv){
	int rank, size,i, j, chunk=0;
	char data[MAX], dataRecv[MAX], dataRecvSum[MAX];
	double t1, t2, maxTime, diffTime;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0){
		//read the word of the size N
		printf("Please enter the word of size N=%d :", size);
		scanf("%s", data);
	}

	t1=MPI_Wtime();

	//scatter the string with count=1
	MPI_Scatter(data, 1, MPI_CHAR, dataRecv, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	
	//repeat the char recieved for rank+1 times
	for(i=0; i<rank+1; i++)
		dataRecv[i]=dataRecv[0];

	//printf("\nThis is the data in the proc %d:", rank);
	//for(i=0; i<rank+1; i++)
	//	printf("%c ",dataRecv[i]);

	MPI_Gather(dataRecv, size, MPI_CHAR, dataRecvSum, size, MPI_CHAR, 0, MPI_COMM_WORLD); 
	
	
	t2=MPI_Wtime();
	diffTime=t2-t1;
	printf("\nThis is the process %d and time taken=%f\n", rank, diffTime);

	//the total time taken by the program is the maximum time taken
	MPI_Reduce(&diffTime, &maxTime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank==0){
		printf("\nThe input pattern is:%s\n", data);

		printf("\nThe Output pattern is:%d", rank);
		for(i=0; i<size; i++){
			for(j=i*size; j<=(i*size) + chunk; j++)
				printf("%c",dataRecvSum[j]);
			chunk++;
	
		}
	printf("\nThe time taken by the whole process is %f", maxTime);
	}

	MPI_Finalize();
	return 0;
	
}
