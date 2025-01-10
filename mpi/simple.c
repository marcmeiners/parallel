#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int rank;
    int data[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        data[4] = 3;
        MPI_Send(data, 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if(rank == 1){
        MPI_Recv(data, 100, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("received number:%d\n", data[4]);
    }
}

//mpicc simple.c -o simple  
//mpirun -np 2 ./simple