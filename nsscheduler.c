#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


struct process
{
    	char a[100];
	int quant;
    	int atime;
    	int used;
    	int turnaroundTime;
    	int waitingTime;
    	int quantUsed;
};


struct process cur_process[100];
struct process cur_process2[100];
struct process cur_process3[100];

int main(void) {

    FILE *myfile = fopen("Prog3inputfileF22.txt", "r");
    if (myfile == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }
    else {
        //Check for number of line
            char ch;
            int count = 0;
            
        do
	{
	ch = fgetc(myfile);
	if (ch == '\n') count++;
	} while (ch != EOF);
        rewind(myfile);
	
	
        //Now scan all the line inside the text
        int i;
	for (i = 0; i < count; i++) 
	{
	
	    fscanf(myfile, "%s %d %d\n", cur_process[i].a, &cur_process[i].quant,
	    &cur_process[i].atime);
	    
	    
	}
	rewind(myfile);
	
	for (i = 0; i < count; i++) 
	{
	
	fscanf(myfile, "%s %d %d\n", cur_process2[i].a, &cur_process2[i].quant,
	    &cur_process2[i].atime);
	    
	}
	rewind(myfile);
	
	for (i = 0; i < count; i++) 
	{
	
	    fscanf(myfile, "%s %d %d\n", cur_process3[i].a, &cur_process3[i].quant,
	    &cur_process3[i].atime);
	    
	}
	count--;
	int totalTurnaround= 0;
	int totalWaitTime = 0;
	int arrivalTimeCounter = 0;
	int process = count; //so when all our process' reach zero we stop
	int waitTime = 0; //how long a process was waiting
	
	printf("\nOS PROGRAM 3\n"); 
	printf("\nShortest Remaining Time \n"); 
	int temp2= 0;//least time
	int q = 0; //current quantum time
	int temp3= 0;
	while(process !=0)
	{
		
		int temp = 0;//holder first value gets loaded to temp2 this checks if a value has been loaded
		//loop array
		for(i = 0; i < count; i++)//loop the entire input data set
		{
		
		//use atime to check if the value has arrived and then the quantum to check if it is currently the lowest 	 
		//quantum
		if(cur_process[i].atime <= q && cur_process[i].quant>0)
		{
			//fill if empty
			if(temp == 0)//set empty value
			{
			temp = 1;
			temp2 = i;
			
			}//check for process with least time remaining
			else if (cur_process[temp2].quant > cur_process[i].quant)
			{
			
			temp2= i;
			}
			
		
		}
		
		}
		
		cur_process[temp2].quant --;
		cur_process[temp2].quantUsed ++;
		if(cur_process[temp2].quant == 0)
		{
		cur_process[temp2].waitingTime = (q - cur_process[temp2].atime);
		cur_process[temp2].turnaroundTime = (cur_process[temp2].waitingTime + cur_process[temp2].quantUsed);
		int temp4 = q- cur_process[temp2].quant; //get process arrival to running
		printf("%d %s  Process terminated\n",temp4, cur_process[temp2].a);
		totalTurnaround += cur_process[temp2].turnaroundTime;
		totalWaitTime += cur_process[temp2].waitingTime;
		process--;
		temp2 = 0;
		}
		else
		{
		
		
		//sleep(2);
		}
		temp = 0;
		
		fflush(stdout);
		q++;
		
		//printf("uh");
	}
	q--;
	printf("%d Complete\n", q);
	fflush(stdout);
	printf("Process		Turnaround	Waiting\n");
	for(i=0; i<count; i++)
		{
		
		printf("%s 		%d 		%d\n", cur_process[i].a, cur_process[i].turnaroundTime,cur_process[i].waitingTime);
		
		
		}
		int values=8;
		float AverageTurn = (float)totalTurnaround/values;
		float AverageWait = (float)totalWaitTime/values;
		printf("Average         %d/8 = %.3f %d/8 = %.3f\n", totalTurnaround, AverageTurn, totalWaitTime, AverageWait);
	fflush(stdout);
	
			int rr= 3;
	arrivalTimeCounter = 0;
	int process1 = count;
	waitTime = 0;
	totalTurnaround = 0;
	printf("-------------------------------------------\n");
	printf("\n ROUND ROBIN \n");
	while(process1 != 0)
	{
		for(i = 0; i < count; i++)
		{
			
			if(cur_process2[i].quant > 0 && cur_process2[i].quant > 3 && cur_process2[i].atime <= arrivalTimeCounter)
			{
			cur_process2[i].quant -= rr;
			printf("%d %s Quantum Expired \n", arrivalTimeCounter, cur_process2[i].a);
			waitTime +=3;
			arrivalTimeCounter+=3;
			
			}
			else if(cur_process2[i].quant > 0 && cur_process2[i].quant <= 3 && cur_process2[i].atime <= arrivalTimeCounter)
			{
			cur_process2[i].waitingTime = (waitTime - cur_process2[i].atime);
			cur_process2[i].turnaroundTime = (waitTime + cur_process2[i].quant);
			totalTurnaround += cur_process2[i].turnaroundTime;
			cur_process2[i].quant =0;
			printf("%d %s Process terminated \n", arrivalTimeCounter, cur_process2[i].a);
			process1 -= 1;
			waitTime += rr-cur_process2[i].quant;
			arrivalTimeCounter+=3;
			}
			
		}
		
		
	}
	printf("Process		Turnaround	Waiting\n");
	printf("-------------------------------------------\n");
	for(i=0; i<count; i++)
		{
		
		printf("%s 		%d 		%d\n", cur_process2[i].a, cur_process2[i].turnaroundTime,cur_process2[i].waitingTime);
		
		
		}
		
		AverageTurn = (float)totalTurnaround/values;
		AverageWait = (float)arrivalTimeCounter/values;
		printf("-------------------------------------------\n");
		printf("Average         %d/8 = %.3f  %d/8 = %.3f\n", totalTurnaround, AverageTurn, arrivalTimeCounter, AverageWait);
		printf("-------------------------------------------\n");
	
	arrivalTimeCounter = 0;
	process = count; //so when all our process' reach zero we stop
	waitTime = 0; //how long a process was waiting
	printf("\nShortest Remaining Time \n"); 
	int currentShortest= 0;//shortest Job
	totalTurnaround= 0;
	totalWaitTime = 0;
	q=0;
	while(process !=0)
	{
		int baseIsSet = 0;
		//loop array
		for(i = 0; i < count; i++)//loop the entire input data set
		{
			if(cur_process3[i].atime <= arrivalTimeCounter && cur_process3[i].used == 0)
			{
		
				if(baseIsSet == 0)
				{
				baseIsSet = 1;
				currentShortest = i;
				
				}
				else if (cur_process3[currentShortest].quant > cur_process3[i].quant)
				{
				currentShortest = i;
				}
			}
	
		}
		cur_process3[currentShortest].used = 1;
		cur_process3[currentShortest].waitingTime = (waitTime - cur_process3[currentShortest].atime);
		
		cur_process3[currentShortest].turnaroundTime = cur_process3[currentShortest].waitingTime + cur_process3[currentShortest].quant;
		totalTurnaround += cur_process3[currentShortest].turnaroundTime;
		printf("%d %s process terminated\n",q, cur_process3[currentShortest].a);
		totalWaitTime += cur_process3[currentShortest].waitingTime;
		waitTime += cur_process3[currentShortest].quant;
		arrivalTimeCounter++;
		process--;
		
		q+=cur_process3[currentShortest].quant;
	
	}
		printf("Process		Turnaround	Waiting\n");
	for(i=0; i<count; i++)
		{
		
		printf("%s 		%d 		%d\n", cur_process3[i].a, cur_process3[i].turnaroundTime,cur_process3[i].waitingTime);
		
		
		}
		
		AverageTurn = (float)totalTurnaround/values;
		AverageWait = (float)totalWaitTime/values;
		printf("Average         %d/8 = %.3f    %d/8 = %.3f\n", totalTurnaround, AverageTurn, totalWaitTime, AverageWait);
	
	
    }
}
