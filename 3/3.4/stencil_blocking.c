#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  int send_value, recv_value, my_id, next_id, prev_id, comm_size, bufsize=1000000;
  int* sendbuf = (int*)malloc(bufsize * sizeof(int));
  int* recvbuf = (int*)malloc(bufsize * sizeof(int));

  double start,end;
  MPI_Status status;

  //printf("---\nBuffer size is %d\n", bufsize);

  /* Initialize the MPI execution environment */
  MPI_Init(&argc,&argv);

  /* Ranks */
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  //printf("Communicator size is %d and I am processor %s\n", comm_size, processor_name);

  int num_chunks = bufsize/comm_size; // + 1; 

  //printf("Chunk size is %d \n", num_chunks);
  
  int Istart = my_id * num_chunks;
  int Iend = Istart + num_chunks >= bufsize ? bufsize : Istart + num_chunks - 1;

  printf("\n---Interval is [%d, %d] \n", Istart, Iend);

  next_id = my_id+1;
  prev_id = my_id-1;

  send_value = Istart + rand() % (100+1); //rand() % (100+1);

  if (my_id !=comm_size-1 && my_id != 0) {

  	printf("Process %d send to process %d \n", my_id, next_id);
  	printf("Process %d receives from the process %d \n", my_id, prev_id);

  	start=MPI_Wtime();
    MPI_Sendrecv(&send_value, 1, MPI_INT, next_id, 0, &recv_value, 1, MPI_INT, prev_id, 0, MPI_COMM_WORLD, &status);
    end=MPI_Wtime();

    printf("Received value is %d\n", recv_value);

    printf("Time elapsed %e for %d\n---",my_id,end-start);
  }

  if (my_id == 0) {

  	printf("Process %d send to process %d \n", my_id, next_id);
  	printf("Process %d receives from the process %d \n", my_id, comm_size-1);
    
    start=MPI_Wtime();
    MPI_Sendrecv(&send_value, 1, MPI_INT, next_id, 0, &recv_value, 1, MPI_INT, comm_size-1, 0, MPI_COMM_WORLD,&status);
    end=MPI_Wtime();

    printf("Received value is %d\n", recv_value);

    printf("Time elapsed %e for %d\n---",my_id,end-start);
  }

  if (my_id == comm_size-1) {

  	printf("Process %d send to process %d \n", my_id, 0);
  	printf("Process %d receives from the process %d \n", my_id, prev_id);

    start=MPI_Wtime();
    MPI_Sendrecv(&send_value, 1, MPI_INT, 0, 0, &recv_value, 1, MPI_INT, prev_id, 0, MPI_COMM_WORLD, &status);
    end=MPI_Wtime();

    printf("Received value is %d\n", recv_value);

    printf("Time elapsed %e for %d\n---",my_id,end-start);
  }

  MPI_Finalize();

  free(sendbuf);
  free(recvbuf);
}