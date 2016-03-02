#include"eliminate.h"
#include"graph.h"
#include<stdio.h>
#include<time.h>
#include<string.h>

void output()
{
	
	int tw = -1;

    //clock_t t = clock();
    tw = TreeWidth(EliminateOrder);
	//printf("zdz %ld\n", clock()-t);
	
	printf("The graph's tree width is: %d\n", tw);

	PrintEliminateOrder(EliminateOrder);

}

int main(int argc, char **argv)
{
	char name[255];
	if(argc!=2)
	{
		fprintf(stderr, "miss graph source file\n");
		return 1;
	}
	else
	{
		strcpy(name, argv[1]);
        
		printf("Processing the file as DIMACS standard format.\n");
	}

	CreateGraph(name);

	InitOrder(EliminateOrder);
 
    ChoosePointAndSwap(EliminateOrder);

	output();
	
	return 0;
}


