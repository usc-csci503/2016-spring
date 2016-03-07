#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

int world_size;
int my_rank;
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void doBoss();
void doWorker();
void printArray(int *N, int size);

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL); /* initialize the MPI universe */
  MPI_Comm_size(MPI_COMM_WORLD, &world_size); /* get number of processors */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* get my id */
  MPI_Get_processor_name(processor_name, &name_len); /* get my name */

  // initialize with a random seed base on the process id
  srand((int)getpid());

  // determine if I am the root node (boss)
  if (my_rank == 0) {
    doBoss();
  } else {
    doWorker();
  }

  // call the cleanup function
  MPI_Finalize();

  return 0;
}

void printArray(int *N, int size)
{
  int i = 0;
  printf(" N = [ ");
  for (i = 0; i < size; i++) {
    printf("%d ", N[i]);
  }
  printf("]\n");
}

void doBoss()
{
  MPI_Status status;

  // reserve memory for array of size N_size
  const int N_size = 20;
  int *N = (int*) malloc(sizeof(int) * N_size);

  // assign random numbers between 1 and 1000 to each element in array
  int i;
  for (i = 0; i < N_size; i++) {
    N[i] = rand() % 1000 + 1;
  }

  printArray(N, N_size);

  // send to total number of workers - 1
  int start, worker_id, worker_count = world_size - 1;

  if (N_size % worker_count == 0) {
    int sub_array_size = N_size/worker_count;
    for (i = 0; i < worker_count; i++) {
      worker_id = i + 1;
      start = i * sub_array_size;
      MPI_Send(&sub_array_size, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
      MPI_Send(&N[start], sub_array_size, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
    }
  } else {
    int sub_array_size = N_size/worker_count;
    for (i = 0; i < worker_count - 1; i++) {
      worker_id = i + 1;
      start = i * sub_array_size;
      MPI_Send(&sub_array_size, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
      MPI_Send(&N[start], sub_array_size, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
    }
    // send to the last one
    worker_id = worker_count;
    start = (worker_id - 1) * sub_array_size;
    int sub_array_size_sm = N_size - (sub_array_size * (worker_count - 1));
    MPI_Send(&sub_array_size_sm, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
    MPI_Send(&N[start], sub_array_size_sm, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
  }

  /* the boss receives from any source */
  int count = world_size;
  int total = 0;

  while (count > 1) {
    int n = 0;
    MPI_Recv(&n, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
    int worker_id = status.MPI_SOURCE;
    printf("Received from worker %02d numberOdds = %d\n", worker_id, n);
    total = total + n;
    count = count - 1;
  }

  printf("Total odd count = %d\n", total);

  free(N); // free up memory -- it's the right thing to do
  return;
}

void doWorker()
{
  MPI_Status status;
  int master_id = 0;
  int i = 0;
  int n = 0;

  // receive size of array from boss
  MPI_Recv(&n, 1, MPI_INT, master_id, 0, MPI_COMM_WORLD, &status);

  // worker must allocate private array (i.e. where to put data when receiving)
  int *array = (int*) malloc(sizeof(int) * n);

  // receive subarray from boss
  MPI_Recv(array, n, MPI_INT, master_id, 0, MPI_COMM_WORLD, &status);

  // count up the number of odds
  int count = 0;
  for (i = 0; i < n; i++) {
    if (array[i] % 2 == 1) {
      count++;
    }
  }

  /* sleep is implemented here to show that workers completion time varies */
  sleep(rand() % 5);

  // printf("[%s.%d] received %d ", processor_name, my_rank, n);
  // printArray(array, n);

  // send back to boss odd count see line 91
  MPI_Send(&count, 1, MPI_INT, master_id, 0, MPI_COMM_WORLD);

  free(array); // free up memory -- it's the right thing to do
  return;
}
