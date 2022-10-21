#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
	int v1 = atoi(argv[1]);
	int v2 = atoi(argv[2]);
	printf("%d multiply by %d\n",v1,v2);
	int G = v1 * v2;
	printf("= %d\n",G);
	
	
}

