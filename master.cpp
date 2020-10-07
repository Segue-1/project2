#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char *argv[])
{
	int c;
	int hflg = 0, nflg = 0, sflg = 0, tflg = 0;
	
	while((c = getopt(argc, argv, "hn:s:t:")) != -1) 
	{
		switch(c)
		{
			case 'h':
				hflg = 1;
				break;
			case 'n':
				nflg = 1;
				break;
			case 's':
				sflg = 1;
				break;
			case 't':
				tflg = 1;
				break;
			case '?':
				if(optopt == 'n' || optopt == 's' || optopt == 't')
				{
					fprintf(stderr, "Put integer argument after -%c \n", optopt);
				}
				else
					fprintf(stderr, "Unkown option -%c  \n", optopt);
			default:
				fprintf(stderr, "Error getting option. \n");
				fprintf(stderr, "Valid options: -h -n x -s x -t x \nx is an integer\n");
				fprintf(stderr, "-h for help \n-n x for total child processes (Default 4) \n");
				fprintf(stderr, "-s x for number of children allowed to exist (Default 2) \n)");
				fprintf(stderr, "-t x for time in seconds after which process terminates (Default 100)\n");
				break;
		}
	
	}



	return 0;
}
