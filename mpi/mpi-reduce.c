
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// MPI_Reduce(
//     void* send_data,
//     void* recv_data, (The recv_data array contains the reduced result and has a size of sizeof(datatype) * count)
//     int count,
//     MPI_Datatype datatype,
//     MPI_Op op,
//     int root,
//     MPI_Comm communicator)

int main(int argc, char** argv){
    MPI_Init(NULL, NULL);

    int rank;
    int size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    float number = rand();
    printf("%f\n", number);
    float global_sum = 0;

    MPI_Reduce(&number, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){ 
        printf("%f", global_sum);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

}

//mpicc mpi-reduce.c -o mpi-reduce  
//mpirun -np 8 ./mpi-reduce