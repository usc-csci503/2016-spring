#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int world_size;
int my_rank;
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void printArray(int *N, int size)
{
  int i = 0;
  printf("[%s] %d/%d N = [ ", processor_name, my_rank, world_size);
  for (i = 0; i < size; i++) {
    printf("%d ", N[i]);
  }
  printf("]\n");
}

int main(int argc, char** argv)
{
  MPI_Status status;

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Get_processor_name(processor_name, &name_len);

  int right = (my_rank + 1) % world_size;
  int size = (argc > 1 ? atoi(argv[1]) : 2);
  int *N = NULL;
  int i = 0;

  if (my_rank == 0) {
    int left = world_size - 1;
    // allocate an array N with random numbers between 0 and 10
    N = (int*) malloc(sizeof(int) * size);
    for (i = 0; i < size; i++) {
      N[i] = rand() % 10;
    }

    printArray(N, size);

    // send size and array to my right
    MPI_Send(&size, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    MPI_Send(N, size, MPI_INT, right, 0, MPI_COMM_WORLD);

    // receive size and array from my right
    MPI_Recv(&size, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(N, size, MPI_INT, left, 0, MPI_COMM_WORLD, &status);

    printArray(N, size);
  } else {
    int left = my_rank - 1;

    // receive size from my left
    MPI_Recv(&size, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);

    // allocate array N of size
    N = (int*) malloc(sizeof(int) * size);
    MPI_Recv(N, size, MPI_INT, left, 0, MPI_COMM_WORLD, &status);
    printArray(N, size);

    // increment the array of potatoes by +1 for each element
    for (i = 0; i < size; i++) {
      N[i]++;
    }

    // send the +1 values to the right
    MPI_Send(&size, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    MPI_Send(N, size, MPI_INT, right, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
