#include <stdio.h>

#include <mpi.h>

#include <string.h>


int main(int argc, char ** argv) {
  int rank, size, j, i, search;
  int n, n1;
  MPI_Status status;
  MPI_Init( & argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, & rank);
  MPI_Comm_size(MPI_COMM_WORLD, & size);
  if (rank == 0) {
    printf("2 is prime number from processor %d\n", rank);
    for (i = 3; i <= 50; i++) {
      n = 0;
      for (j = 2; j < i; j++) {
        if (i % j == 0) {
          n = 1;
        }
      }
      if (n == 0) {
        printf("%d is a prime number from processor %d\n", i, rank);
      }
    }
  }

  if (rank == 1) {
    for (i = 51; i <= 100; i++) {
      n = 0;
      for (j = 2; j < i; j++) {
        if (i % j == 0) {
          n = 1;
        }
      }
      if (n == 0) {
        printf("%d is a prime number from processor %d\n", i, rank);
      }
    }
  }

  MPI_Finalize();
  return 0;
}
