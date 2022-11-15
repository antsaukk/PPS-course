#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  int my_id, your_id, bufsize=10000;

  int* sendbuf = (int*)malloc(bufsize * sizeof(int));
  int* recvbuf = (int*)malloc(bufsize * sizeof(int));

  double start;
  double end;
  MPI_Status status;

  printf("Initializing MPI...\n");

  printf("Buffer size is %d\n", bufsize);

  /* Initialize the MPI execution environment */
  MPI_Init(&argc,&argv);

  /* Ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  your_id = 1 - my_id;
  printf("Rank %d here, hello!\n",my_id);

  if (my_id == 0) {
    printf("Initiating send to rank %d\n",your_id);

    start = MPI_Wtime();
    MPI_Send(sendbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD); 
    MPI_Recv(recvbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD,&status); 
    end = MPI_Wtime();

    printf("Receive finished from %d\n",your_id);

    printf("Communication between processes %d and %d has taken this much time: %e.\n", my_id, your_id, end-start);
  } else if (my_id == 1) {
    printf("Initiating send to rank %d\n",your_id);

    start = MPI_Wtime();
    MPI_Recv(recvbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD,&status);
    MPI_Send(sendbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD); 
    end = MPI_Wtime();

    printf("Receive finished from %d\n",your_id);

    printf("Communication between processes %d and %d has taken this much time: %e.\n", my_id, your_id, end-start);
  }
  
  /* Finalize the MPI environment. */
  MPI_Finalize();

  free(sendbuf);
  free(recvbuf);
}