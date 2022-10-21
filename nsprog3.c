#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE *file = fopen("inputfile", "r");
	
	int valuesRead[2];
	int x = 0;
	//valuesRead holds our scanned values while x is our position pointer for the loop.
	
	// loops lines of the file
	while(!feof(file)){
	int i = 0;
	fscanf(file,"%d",&i);
	if(i != 0){
		valuesRead[x] = i;
		x++;
		}
	}
	//print file results
	printf("%d multiply by %d\n",valuesRead[0],valuesRead[1]);
	//do math and print
	int G = valuesRead[0] * valuesRead[1];
	printf("= %d\n",G);
	//close file
	fclose (file);
}

