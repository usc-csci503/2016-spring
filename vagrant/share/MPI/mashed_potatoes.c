#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

int world_size;
int my_rank;
char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

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
  int i;

  for (i = 1; i < world_size; i++) {
    int potatoSize = rand() % 10 + 1;
    MPI_Send(&potatoSize, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  int count = world_size;

  /* the boss receives from any source */
  while (count > 1) {
    int potatoSize;
    MPI_Recv(&potatoSize, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, 
             &status);
    int worker_id = status.MPI_SOURCE;
    int *array = (int*)malloc(sizeof(int) * potatoSize);
    MPI_Recv(array, potatoSize, MPI_INT, worker_id, 0, MPI_COMM_WORLD, 
             &status);
    printf("Received from %02d ", worker_id);
    printArray(array, potatoSize);
    count--;
  }
}

void doWorker()
{
  MPI_Status status;
  int master_id = 0;
  int i = 0;
  int potatoSize = 0;

  MPI_Recv(&potatoSize, 1, MPI_INT, master_id, 0, MPI_COMM_WORLD, &status);
  int *array = (int*)malloc(sizeof(int) * potatoSize);

  for (i = 0; i < potatoSize; i++) {
     int salt_level = rand() % 1000;
     array[i] = salt_level;
  }

  /* sleep is implemented here to show that workers completion time varies */
  sleep(rand() % 5);

  MPI_Send(&potatoSize, 1, MPI_INT, master_id, 0, MPI_COMM_WORLD);
  MPI_Send(array, potatoSize, MPI_INT, master_id, 0, MPI_COMM_WORLD);

  /* printArray(array, potatoSize); */
}

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Get_processor_name(processor_name, &name_len);

  srand((int)getpid());

  if (my_rank == 0) {
    doBoss();
  } else {
    doWorker();
  }

  MPI_Finalize();

  return 0;
}
