#include <stdio.h>
#include <mpi.h>
#include "matrix.h"

int R[N][N];
// only the corresponding part
void multiply_matrix(int start, int end){
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            R[i][j] = 0;
            for (int k = 0; k < N; k++) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


int main(int argc, char *argv[]){
  int id, nprocs, start, end, part, i;
  MPI_Status status;
  MPI_Request r;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  part = N / nprocs;
  start = part * id;
  end = start + part;
  if(id == nprocs-1)
    end = end + N % nprocs;

  multiply_matrix(start, end);

  if(id == 0){
  	for(i = 1; i < nprocs; i ++){
  		// printf("Process %d\n", i);
	  	start = part * i;
	  	end = start + part;
	  	if(id == nprocs-1)
			end = end + N % nprocs;
		MPI_Irecv(&R[start], (end-start)*N, MPI_INT, i, 0, MPI_COMM_WORLD, &r);
		MPI_Wait(&r, MPI_STATUS_IGNORE);
  	}
  	/*
  	for(i = 0; i < N; i ++){
  		for(int j = 0; j < N; j ++){
  			printf("%d ", R[i][j]);
  		}
  		printf("\n");
  	}
  	*/
  }
  else{
   	MPI_Isend(&R[start], (end-start)*N, MPI_INT, 0, 0, MPI_COMM_WORLD, &r);
	MPI_Wait(&r, MPI_STATUS_IGNORE);
  }
  MPI_Finalize();
  return 0;
}

