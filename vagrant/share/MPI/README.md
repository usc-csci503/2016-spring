# Example MPI Programs

### `hello.c`

Prints out a simple hello message for each of the processors in the MPI application.   Note that there are no communications between the processors.

### `potato.c`

Simple program that passes a potato in a circular ring starting with rank `0`.

### `potatoes.c`

A slightly more complex program that passes a number of potatoes in a circular ring.  The number of potatoes or `size` is specified by the command line argument.  To run `potatoes`

```
mpirun -np 4 -f hostfile /share/MPI/potatoes 5
```

In the above example, 5 potatoes are being passed to the right.

### `mashed_potatoes.c`

This is a simple program where a manager gives potatoes of different size to its workers.  The worker creates an array of mashed pieces of potatoes, which is stored in an array.  This array has a random salt amount and is sent back to the master, who prints out the array that it has received from its worker.

```
mpirun -np 4 -f hostfile /share/MPI/mashed_potatoes 
```

Note that the random seed is `srand(get_pid())`;
