#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int ShmID;
	int *ShmPTR;
	pid_t pid;
	key_t key = 0;
	
	key = ftok("shmfile", 63);
	printf("Worker\n");
	
	ShmID = shmget(key, 22*sizeof(char), IPC_CREAT | 0666);

	if (ShmID < 0)
	{
		perror("error: ");
		exit(1);
	}
	
	ShmPTR = (int *) shmat(ShmID, NULL, 0);

	if (*ShmPTR != 0)
	{
		printf("Worker: Shared memory value doesn't equal 0, exiting...\n");
		return -1;
	}
	else
	{
		printf("Worker: Shared memory equals 0, continuing...\n");	







	}
	
	while(*ShmPTR != 0)
	{
		sleep(1);
	}
	
	if(*ShmPTR == 0)
	{
		printf("Worker: Shared memory has been set to 0\n");
	}
	
	
	return 0;
}
