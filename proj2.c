#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#define MAX_LINE 80
#define MAX_HIST 10


static char buffer[MAX_LINE];
char history[MAX_LINE][MAX_HIST];
int location = 0;
void handle_SIGTSTP() { 
	for(int i=0; i<location; i++)
	printf("\n%s",history[i]);
}

void addHistory(char Buffer[], int Length)

{ int i;

if(Length > 1)

for(i=0; i<Length && i<MAX_LINE-2; i++) {

history[location%MAX_HIST][i]=Buffer[i];

} history[location%MAX_HIST][i]='\0';
location++;
} 


void setup (char inputBuffer[], char *args[], int *background)
{
int length, /* # of characters in the command line */

    i,      /* loop index for accessing inputBuffer array */
    start,  /* index where beginning of next command parameter is */
    ct;     /* index of where to place the next parameter into args[] */
    ct = 0;
    /* read what the user enters on the command line */
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE); 
    start = -1;
    addHistory(inputBuffer,length);
    if (length == 0)

        exit(0);            /* ^d was entered, end of user command stream */

    if (length < 0){

        perror("error reading the command");

        exit(-1);           /* terminate with error code of -1 */

    }

    /* examine every character in the inputBuffer */

    for (i=0;i<length;i++) {

        switch (inputBuffer[i]){

          case ' ':

          case '\t' :               /* argument separators */

            if(start != -1){

                    args[ct] = &inputBuffer[start];    /* set up pointer */

                ct++;

            }

            inputBuffer[i] = '\0'; /* add a null char; make a C string */

            start = -1;

            break;

 

          case '\n':                 /* should be the final char examined */

            if (start != -1){

                    args[ct] = &inputBuffer[start];    

                ct++;

            }

                inputBuffer[i] = '\0';

                args[ct] = NULL; /* no more arguments to this command */

            break;

 

          default :             /* some other character */

            if (start == -1)

                start = i;

            if (inputBuffer[i] == '&'){

                *background  = 1;

                start = -1;

                inputBuffer[i] = '\0';

            }

          }

     }   

     args[ct] = NULL; /* just in case the input line was > 80 */
}
int main (void){
char inputBuffer[MAX_LINE] ; /* buffer to hold command entered */
int background; /* equals 1 if a command is followed by ‘& ’ */
char *args [MAX_LINE/2 + 1]; /* command line arguments */
int comCounter = 0;
char* str1= "yell";
char* str2= "exit";
char* repeat= "r";
/*
int result1;
int result2;
char* str3[20];*/
int uPid = getpid();
int f = 1;

	struct sigaction handler;
	handler.sa_handler = handle_SIGTSTP;
	handler.sa_flags=SA_RESTART; 
	sigaction (SIGTSTP, &handler, NULL);
	//main body
	while (1) {
	
	
	
	
	background = 0 ;
	

	printf("\n");
	printf ("Welcome to nsshell. My pid is %d\n", uPid);
	printf("Total commands so far %d\n", comCounter);
	printf ("COMMAND -> ");
	fflush( stdout );
	printf("\n");
	setup(inputBuffer, args, &background) ;
	/** the steps are:
	(0) If command is built-in, print command results to terminal. If command is exit, print
	statistics and exit()
	(1) fork a child process using fork( )
	(2) the child process will invoke execvp( )
	(3) if background == 0, the parent will wait(),
	otherwise it will invoke the setup( ) function again. */
	comCounter++;


		if (strcmp(str1, args[0]) == 0) 
			{
			printf("\n");
			fflush( stdout );
			int i = 0;
			//check string length then loop through outputting the characters after capitalizing
			char c;
			while(args[f]){
			for(i = 0; i < (strlen(args[f])); i++)
			{
			c = args[f][i];
			putchar(toupper(c));
			}
			f++;
			printf("\n");
			}

			}
		else if (strcmp(str2, args[0]) == 0) 
			{

			char exitStr[1000];
			sprintf(exitStr, "ps -p %d -o pid,ppid,pcpu,pmem,etime,user,command", uPid);
			system(exitStr);
			exit(0);
			}
		else if(strcmp(repeat, args[0]) == 0) 
		{
		
			//check the input if there is an integer value representing the 
			//user input theyd like to repeat
			if(isdigit(args[1]))
			{
				int v = atoi(args[1]);
				printf("worked");
				fflush( stdout );
				execvp(history[v],args);
					
				
			}
			//we just get the last position available in the array
			else
			{
			//if there is not then we will just take the last location and load it and 					
				//execute the string
				printf("%s\n",history[location]);
				
			
			}
		
		
		}
		else{
			
			uPid = fork();
			int newPid = getpid();
			if (uPid < 0) { /* error occurred */
				fprintf(stderr, "Fork Failed");
				
			}
			else if (uPid == 0) { /* child process */
			
				
				char* backgroundFlag;

				if(background)

				{

				backgroundFlag = "TRUE";

				}

				else

				{

				backgroundFlag = "FALSE";

				}
				printf("[Child pid = %d, background = %s]\n", newPid, backgroundFlag);
				execvp(args[0],args);

				putchar('\n');

				exit(0);
				//119			
			 }

			else

				{

				if(!background)

				{

				wait(0);

				printf("Child complete\n");

				}
			
			
			}
		}
		


	     /* set up the signal handler */
	      


	}
	
}



	
