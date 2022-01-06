#include <stdio.h>

#include <mpi.h>

#include <string.h>


int main(int argc, char ** argv) {
  int rank, size, sum1 = 0, sum2, sum = 0, s = 0, n, n2, i, n3;
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

    if (n % 2 == 0) {
      n3 = n / 2;
      MPI_Send( & n3, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send( & a[n / 2], n / 2, MPI_INT, 1, 1, MPI_COMM_WORLD);

    } else {
      n3 = (n + 1) / 2;
      MPI_Send( & n3, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send( & a[(n + 1) / 2], n / 2, MPI_INT, 1, 1, MPI_COMM_WORLD);

    }
    MPI_Recv( & sum2, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, & status);
    if (n % 2 == 0) {
      for (i = 0; i < (n / 2); i++) {
        sum1 += a[i];
      }
    } else {
      for (i = 0; i <= (n / 2); i++) {
        sum1 += a[i];
      }
    }
    sum = sum1 + sum2;
    printf("Sum = %d \n", sum);
  }

  if (rank == 1) {
    MPI_Recv( & n1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, & status);
    MPI_Recv( & b[0], n1, MPI_INT, 0, 1, MPI_COMM_WORLD, & status);
    for (i = 0; i < n1; i++) {
      s += b[i];
    }
    MPI_Send( & s, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
