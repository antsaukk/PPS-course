#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

  /* Blocking send and receive in between *two* processes */
  /* First send and receive */
  /* Start with bufsize 1, then keep on increasing it */
  int my_id, your_id, bufsize=1000000;
  int sendbuf[bufsize],recvbuf[bufsize];
  double start;
  double end;
  MPI_Status status;

  printf("Initializing MPI...\n");

  /* Initialize the MPI execution environment */
  MPI_Init(&argc,&argv);

  /* Ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  your_id = 1 - my_id;
  printf("Rank %d here, hello!\n",my_id);

  printf("Initiating send to rank %d\n",your_id);
  /* First send...*/
  start = MPI_Wtime();
  MPI_Send(&sendbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD);

  printf("Waiting to receive from rank %d\n",your_id);
  /* Then receive */
  MPI_Recv(&recvbuf,bufsize,MPI_INT,your_id,0,MPI_COMM_WORLD,&status);
  end = MPI_Wtime();
  printf("Receive finished from %d\n",your_id);

  printf("Communication between processes %d\n and %d\n has taken this much time: %.2fs.\n", my_id, your_id, end-start);
  /* Finalize the MPI environment. */
  MPI_Finalize();
}