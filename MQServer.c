/****************************************/
/*   Titel : Assignment2_Server_mq.c    */
/*        Author: Khanjan Desai         */
/*         Date : Feb 15, 2016          */
/* Message queue in client server model */
/* Implementation of mathematical engine*/
/****************************************/



#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int mq_id=0;

int main(void)
{
	int i;
	struct msqid_ds buffer;
	FILE *fp;			//file poirnter
	char message[3]={0,0,0};	//message buffer

	// get unique PID for server and errorcheck
	key_t key;
	if((key = ftok("Assignment2_Server_mq.c",35))==-1)	
	{
		perror("Error ftok:");
		exit(1);
	}
	//Create Inter processes communication using msgget with error check
	if((mq_id = msgget(key,0666|IPC_CREAT))==-1)		
	{
		perror("Error IPC:");
		exit(1);
	}
	
	printf("Message queue running...\n");
	while(1)
	{
		//Get size of message
		if((msgctl(mq_id,IPC_STAT,&buffer))==-1)
		{
			perror("Error:");		
			exit(1);
		}
		// Check for message if available
		if (buffer.msg_qnum > 0)
		{	
			// Get client process ID
			int client_id = buffer.msg_lrpid;
			// Recieve message in server
			if(msgrcv(mq_id,message,3,0,IPC_NOWAIT)==-1) 
			{
				perror("Error Recieve:");
				exit(1);
			}
			// Covert ASCII to Int
			message[0]-='0';
			message[2]-='0';
			// Open result file
			fp = fopen("result.txt","a");
			// Check for operator and perform accordingly for multiply need to use \* insted of * in cmdline
			switch(message[1])
			{
				case '+':
				{
					fprintf(fp,"%d:\t%d\n",client_id,message[0]+message[2]);
					printf("%d\n",message[0]+message[2]);
					break;
				}
				case '-':
				{
					fprintf(fp,"%d:\t%d\n",client_id,message[0]-message[2]);
					printf("%d\n",message[0]-message[2]);
					break;					
				}
				case '*':
				{
					fprintf(fp,"%d:\t%d\n",client_id,message[0]*message[2]);
					printf("%d\n",message[0]*message[2]);
					break;
				}
				case '/':
				{
					fprintf(fp,"%d:\t%d\n",client_id,message[0]/message[2]);
					printf("%d\n",message[0]/message[2]);
					break;
				}
				case '%':
				{
					fprintf(fp,"%d:\t%d\n",client_id,message[0]%message[2]);
					printf("%d\n",message[0]%message[2]);
					break;
				}
				default:
				{
					fprintf(fp,"%d:\tWrong Input\n",client_id);
					printf("Wrong Input\n");
					break;
				}
			}
			// Close file
			fclose(fp);
		}
	}
}
