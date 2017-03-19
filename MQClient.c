/****************************************/
/*   Titel : Assignment2_Client_mq.c    */
/*        Author: Khanjan Desai         */
/*         Date : Feb 15, 2016          */
/* Message queue in client server model */
/* Implementation of mathematical engine*/
/****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>


int mq_id;


int main(int argc,char *argv[])
{
	char message[3];	// Message buffer
	key_t key;
	int i;
	// Get unique PID
	if((key=ftok("Assignment2_Server_mq.c",35))==-1)
	{
		perror("Error ftok: ");
		exit(1);
	}
	// Create IPC
	if((mq_id=msgget(key,0666|IPC_CREAT))==-1)
	{
		perror("Error IPC:");
		exit(1);
	}
	// Read messade from argv
	for(i=0;i<3;i++)
	{
		message[i] = *argv[i+1];
	}
	// Send message
	if(msgsnd(mq_id,message,3,0)==-1)
	{
		perror("Error Send:");
		exit(1);
	}
	
}
