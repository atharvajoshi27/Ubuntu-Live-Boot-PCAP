#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>

#define MESSAGE_SIZE 7

void random_message_generator(char *char_array, int size, int seed){
	srand(seed + time(NULL));
	short selector, i;
	for(i = 0; i < size; i ++){
		selector = rand() % 2;
		if(selector){
			char_array[i] = 'A' + rand() % 26;
		}
		else{
			char_array[i] = 'a' + rand() % 26;
		}
	}
	return;
}

void print_char_array(char *char_array, int size){
	int i;
	for(i = 0; i < size; i += 1){
		printf("%c", char_array[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  
  int id, num_procs, sender, receiver;
  
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  
  sender = ((id - 1) % num_procs + num_procs) % num_procs; // process sending message to this process
  receiver = (id + 1) % num_procs; // to which process we are sending message
  char message[MESSAGE_SIZE];
  if(id & 1){
   // Send first and then receive
   // int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type, int destination_ID, int tag, MPI_Comm comm);
   random_message_generator(message, MESSAGE_SIZE, id);
   printf("%d sending message \"%s\" to %d ....\n", id, message, receiver);
   MPI_Send(message, MESSAGE_SIZE, MPI_CHAR, receiver, 0, MPI_COMM_WORLD);
   MPI_Recv(message, MESSAGE_SIZE, MPI_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   printf("%d received message \"%s\" from %d.\n", id, message, sender);
  }
  else{
  	// Receive first and then send
   // int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type, int destination_ID, int tag, MPI_Comm comm);
   
   printf("%d waiting for message from %d ....\n", id, sender);
   MPI_Recv(message, MESSAGE_SIZE, MPI_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   printf("%d received message \"%s\" from %d.\n", id, message, sender);
   random_message_generator(message, MESSAGE_SIZE, id);
   printf("%d sending message \"%s\" to %d ....\n", id, message, receiver);
   MPI_Send(message, MESSAGE_SIZE, MPI_CHAR, receiver, 0, MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
  return 0;
}



/*
SYNTAX

int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type, 
      int destination_ID, int tag, MPI_Comm comm); 

    data_to_send: variable of a C type that corresponds to the send_type supplied below
    send_count: number of data elements to be sent (nonnegative int)
    send_type: datatype of the data to be sent (one of the MPI datatype handles)
    destination_ID: process ID of destination (int)
    tag: message tag (int)
    comm: communicator (handle) 
    
    
int MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type, 
      int sender_ID, int tag, MPI_Comm comm, MPI_Status *status); 
      
*/
