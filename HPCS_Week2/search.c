#include <stdio.h>

#include <mpi.h>

#include <string.h>


int main(int argc, char ** argv) {
  int rank, size, sum1 = 0, sum2, sum = 0, s, n, n2, i, n3, search;
  int a[50], b[50], c[50], d[50], n1;
  MPI_Status status;
  MPI_Init( & argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, & rank);
  MPI_Comm_size(MPI_COMM_WORLD, & size);
  if (rank == 0) {
    printf("Enter size of the array\n");
    scanf("%d", & n);
    printf("Enter array Elements\n");
    for (i = 0; i < n; i++) {
      scanf("%d", & a[i]);
    }
    printf("Enter element to be serached \n");
    scanf("%d", & search);
    if (n % 2 == 0) {
      n3 = n / 2;
      MPI_Send( & n3, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send( & a[n / 2], n / 2, MPI_INT, 1, 1, MPI_COMM_WORLD);
      MPI_Send( & search, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
    } else {
      n3 = (n + 1) / 2;
      MPI_Send( & n3, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send( & a[(n + 1) / 2], n / 2, MPI_INT, 1, 1, MPI_COMM_WORLD);
      MPI_Send( & search, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
    }

    if (n % 2 == 0) {
      for (i = 0; i < (n / 2); i++) {
        if (a[i] == search) {
          printf("Element present in %d location identified by %d processor\n", (i + 1), rank);
        }
      }
    } else {
      for (i = 0; i <= (n / 2); i++) {
        if (a[i] == search) {
          printf("Element present in %d location identified by %d processor\n", (i + 1), rank);
        }
      }
    }
  }

  if (rank == 1) {
    MPI_Recv( & n1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, & status);
    MPI_Recv( & b[0], n1, MPI_INT, 0, 1, MPI_COMM_WORLD, & status);
    MPI_Recv( & s, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, & status);
    for (i = 0; i < n1; i++) {
      if (b[i] == s) {
        printf("Element present in %d location identified by %d processor\n", (n1 + i), rank);
      }
    }
  }

  MPI_Finalize();
  return 0;
}
