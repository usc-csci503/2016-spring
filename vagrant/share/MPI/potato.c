#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv)
{
  MPI_Status status;

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  int N = 0;
  int right = (world_rank + 1) % world_size;

  if (world_rank == 0) {
    int left = world_size - 1;
    N = rand() % 10;
    MPI_Send(&N, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    MPI_Recv(&N, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);
    printf("[%s] %d/%d N=%d\n", processor_name, world_rank, world_size, N);
  } else {
    int left = world_rank - 1;
    MPI_Recv(&N, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);
    printf("[%s] %d/%d N=%d\n", processor_name, world_rank, world_size, N);
    N = N + 1;
    MPI_Send(&N, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
  }

  // Finalize the MPI environment.
  MPI_Finalize();

  return 0;
}
