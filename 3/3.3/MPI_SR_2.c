#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  int my_id, your_id, bufsize=100000000;
  int* sendbuf = (int*)malloc(bufsize * sizeof(int));
  int* recvbuf = (int*)malloc(bufsize * sizeof(int));

  double start;
  double end;
  MPI_Status status;
  MPI_Request request;

  sendbuf[5]=5;

  printf("Buffer size is %d\n", bufsize);
  
  /* Initialize the MPI execution environment */
  MPI_Init(&argc,&argv);

  /* Ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  your_id = 1 - my_id;

  printf("Rank %d Initiating send to rank %d\n",my_id,your_id);

  if (my_id == 0) {
   start = MPI_Wtime();

   MPI_Irecv(recvbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD,&request);
   MPI_Isend(sendbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD,&request);
   MPI_Wait(&request,MPI_STATUS_IGNORE);

   end = MPI_Wtime();

   printf("Rank %d has received this %d from  %d\n",my_id,recvbuf[5],your_id);
   printf("Communication between processes %d and %d has taken this much time: %e.\n", my_id, your_id, end-start);
} else if (my_id == 1) {
   start = MPI_Wtime();

   MPI_Irecv(recvbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD,&request);
   MPI_Isend(sendbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD,&request);
   MPI_Wait(&request,MPI_STATUS_IGNORE);

   end = MPI_Wtime();

   printf("Rank %d has received this %d from  %d\n",my_id,recvbuf[5],your_id);
   printf("Communication between processes %d and %d has taken this much time: %e.\n", my_id, your_id, end-start);
}

  MPI_Finalize();

  free(sendbuf);
  free(recvbuf);
}