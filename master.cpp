#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdint>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

bool isPalindrome(char str[]);

int main (int argc, char *argv[])
{
	int c;
	int hflg = 0, nflg = 0, sflg = 0, tflg = 0;
	int ShmID;
	int *ShmPTR;
	pid_t pid;
	int status;
	key_t key = 0;

	key = ftok("shmfile", 63);

	ShmID = shmget(key, 22*sizeof(char), IPC_CREAT | 0666);
	
	if (ShmID < 0)
	{
		perror("error: ");
		exit(1);
	}

	printf("Server has received a shared memory of 22 chars...\n");

	ShmPTR = (int *) shmat(ShmID, NULL, 0);

	if ((intptr_t) ShmPTR == -1)
	{
		perror("error: ");
		exit(1);
	}
	
	printf("Shared memory has been attached...\n");
	
	for (int i = 0; i < 22; i++) 
	{
		ShmPTR[i] = 'a';
	}

	printf("Server has filled memory, here is ShmPTR[20]: %c\n", ShmPTR[20]);


	printf("Master is about to fork a child process...\n");

	pid = fork();
	if (pid < 0)
	{
		printf("Fork error (master)\n");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("Master: Fork call used to execv worker process\n");
		//char * argv_list[] = {"worker.exe", NULL, NULL};
		execv("worker.exe", NULL);
	}
	else
	{
		while(*ShmPTR == 0)
		{
			sleep(1);
		}
		if (*ShmPTR == -1)
		{
			printf("Section about valid args idk...\n");
		}
		if (*ShmPTR != 0 && *ShmPTR != -1)
		{
			printf("Something about the problem being solved...\n");
			*ShmPTR = 0;	
		}
		if (waitpid(pid, &status, 0) > 0)
		{
			if(WIFEXITED(status) && !WEXITSTATUS(status))
			{
				printf("Program executed successfully\n");
			}		
			else if (WIFEXITED(status) && WEXITSTATUS(status))
			{
				if(WEXITSTATUS(status) == 127)
				{
					printf("Master: execv has failed.\n");
				}
				else
				{
					printf("Normal worker termination.\n");
				}
			}
			else
			{
				printf("waitpid() failed\n");				
			}
		shmdt((void *) ShmPTR);
		shmctl(ShmID, IPC_RMID, NULL);
		return 0;
		}


	}	

	

	
	// Get options from user. 
	while((c = getopt(argc, argv, "hn:s:t:")) != -1) 
	{
		switch(c)
		{
			case 'h':
				hflg = 1;
				printf("Below are valid options.\n");
				printf("Note: x is an integer \n-n x is for total child processes (Default 4)\n");
				printf("-s x is for total number of children allowed to exist (Default 2)\n");
				printf("-t x is for time in seconds after which process terminates (Default 100)\n");
				break;
			case 'n':
				{
				nflg = 1;
				}
				break;
			case 's':
				sflg = 1;
				break;
			case 't':
				tflg = 1;
				break;
			case '?':
				// If no number with these options then output error.
				if(optopt == 'n' || optopt == 's' || optopt == 't')
				{
					fprintf(stderr, "-%c option must be followed by integer\n", optopt);
					perror("error: ");
				}
				else
				{
					fprintf(stderr, "Unkown option -%c \n Use -h option for help\n", optopt);
					perror("error: ");
				}
			default:
				fprintf(stderr, "-h for help \n");
				break;
		}
	
	}


	return 0;
}


bool isPalindrome(char str[])
{

	int l = 0;
	int count = 0;
	bool isTrue = true;
	
	// Removes spaces.
	for (int i = 0; str[i]; i++)
	{
		if (str[i] != ' ')
			str[count++] = str[i];

	}
	str[count] = '\0';
	

	
	// Check to see if string is palindrome.  Check left most char with right most and see if equal.
	int h = strlen(str) -1;
	while (h > 1)
	{
		if (str[l++] != str[h--])
		{
			isTrue = false;
			
		}
	}
	return isTrue;
}
