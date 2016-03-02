//#define NDEBUG 
#include"eliminate.h"
#include"graph.h"
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>

/* create a eliminate order and put the result in array EliminateOrder */
void InitOrder(int *EliminateOrder)
{
	printf("Init Order......\n");
	inv_loop = graph_size;
	min_inv_loop = graph_size/2;
    for(int i=0; i<graph_size; ++i)
	{
        EliminateOrder[i] = i;
		indexEliminateOrder[i] = i;
	}
}

inline static void SwapEliminateOrder(int** order1, int** order2)
{
	int *temp = *order1;
	*order1 = *order2;
	*order2 = temp;
}

inline static void SwapVertex(int *v1, int* v2)
{
	int temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

/*inline static int ProcessingHash(int *EliminateOrder)
{
	//clock_t t = clock();
	char tempEliminateOrder[MaxGraphSize*4+1];
	char *temp =(char*) EliminateOrder;
    int index_temp = 0;
	int index_tempEliminateOrder = 0;
	while(index_temp < graph_size*4)
	{
		tempEliminateOrder[index_tempEliminateOrder] = temp[index_temp]+'0';
		//assert(tempEliminateOrder[index_tempEliminateOrder] != '\0');
		index_tempEliminateOrder++;
		index_temp++;
	}
	tempEliminateOrder[index_tempEliminateOrder] = '\0';
	
	string s(tempEliminateOrder, graph_size*4+1);
	//printf("zdz.....%ld\n", clock() - t);
	
	if(hash_table.hashed(s) == true)
	{
		//printf("hashed\n");
		return 0;
	}
	if(recordEliminateOrder[index_recordEliminateOrder] == "")
	{
		recordEliminateOrder[index_recordEliminateOrder] = s;
		hash_table.hash(s);
	}
	else
	{
		//clock_t t = clock();
		hash_table.unHash(recordEliminateOrder[index_recordEliminateOrder]);
		recordEliminateOrder[index_recordEliminateOrder] = s;
		hash_table.hash(s);
		//printf("zdz....%ld\n", clock()-t);
	}
	if(++index_recordEliminateOrder == recordEliminateOrderSize)
		index_recordEliminateOrder = 0;
	return 1;
}*/

inline static int MinTreeWidthNeighbourOrder(int* min_neighbour_EliminateOrder)
{
	int no_improve = 0;
	int cause_max_clique_vertex;
	int init_mintreewidth = TreeWidthWithMaxCliqueVertex(min_neighbour_EliminateOrder, &cause_max_clique_vertex);

	int mintreewidth = 10000;

	//clock_t t = clock();

	while(no_improve < inv_loop)
	{
		int v1_index = indexEliminateOrder[cause_max_clique_vertex];
	    srand(clock());
		//srand(rand());
	    int v2_index = rand()%graph_size;

	    if(v1_index == v2_index)
			continue;
		
		SwapVertex(min_neighbour_EliminateOrder + v1_index, min_neighbour_EliminateOrder + v2_index);
        
		
		int temptreewidth = TreeWidthWithMaxCliqueVertex(min_neighbour_EliminateOrder, &cause_max_clique_vertex);

		if(temptreewidth <= mintreewidth)
		{
			mintreewidth = temptreewidth;
			//no_improve = 0;
			//printf("%d     %ld\n", mintreewidth, clock()); 
		}
		else
		{
			++no_improve;
			SwapVertex(min_neighbour_EliminateOrder + v1_index, min_neighbour_EliminateOrder + v2_index);
		}
	}
	return mintreewidth;
} 

inline static void RandomChange(int* EliminateOrder,int loop_num)
{
	int v1_index;
	int v2_index;
	//int num = 0;
	for(int i = 0; i < loop_num; ++i)
	{
	    srand(clock());
	    v1_index = rand()%graph_size;
	    do{
		    //++num;
	        srand(clock());
		    //srand(rand());
	        v2_index = rand()%graph_size;
	    }while(v1_index == v2_index);
	    SwapVertex(EliminateOrder + v1_index, EliminateOrder + v2_index);
	}
}

/* After InitOrder swap some point in array EliminateOrder by some rules and make a new eliminate order */
void ChoosePointAndSwap(int *EliminateOrder)
{
	printf("Choose point and swap to get a better eliminate order.....\n");
	int best_treewidth = TreeWidth(EliminateOrder);

	int* e0 = (int*)malloc(sizeof(int)*(graph_size));
    int* e1 = (int*)malloc(sizeof(int)*(graph_size));
	int* e2 = (int*)malloc(sizeof(int)*(graph_size));

	int * best, *candidate, *min_neighbour;
	candidate = best = e0;
	min_neighbour = e2;
	memcpy(candidate, EliminateOrder, sizeof(int)*(graph_size));

	int new_swap_num = 1;
	int slightly_worse = 0;
	int worse = 0;

	int init_worse_neighbour = 3;
	int max_worse_neighbour = 4;
	int worse_neighbour = init_worse_neighbour;

	int* space[3] = {e0, e1, e2};
	int index_min_neighbour_in_space = 2;
    	
	while(clock() < 3600000000)
	{
		new_swap_num++;

		memcpy(min_neighbour, candidate, sizeof(int)*(graph_size));
        int min_neighbour_width = MinTreeWidthNeighbourOrder(min_neighbour);
        
		if(min_neighbour_width < best_treewidth)
		{
			best_treewidth = min_neighbour_width;
			best = candidate = min_neighbour;

			index_min_neighbour_in_space = (index_min_neighbour_in_space+1)%3;
			min_neighbour = space[index_min_neighbour_in_space];
			printf(" new tree width %d, cpu time %ld\n", best_treewidth, clock());

			worse_neighbour = init_worse_neighbour;
		}
		else if(min_neighbour_width == best_treewidth)
		{
			worse_neighbour = init_worse_neighbour;

			best = candidate = min_neighbour;

			index_min_neighbour_in_space = (index_min_neighbour_in_space+1)%3;
			min_neighbour = space[index_min_neighbour_in_space];
		}
		else /*if(min_neighbour_width < best_treewidth + worse_neighbour)*/
		{
			slightly_worse++;

			if(candidate == best)
			{
			    candidate = min_neighbour;

				index_min_neighbour_in_space = (index_min_neighbour_in_space+1)%3;
			    while(space[index_min_neighbour_in_space] == best)
				{
					index_min_neighbour_in_space = (index_min_neighbour_in_space+1)%3;
				}
				min_neighbour = space[index_min_neighbour_in_space];
			}
			/*else
			{
				while(space[index_min_neighbour_in_space] != candidate)
				{
					index_min_neighbour_in_space = (index_min_neighbour_in_space+1)%3;
				}
				//SwapEliminateOrder(&candidate, &min_neighbour);
			}*/
			int temp_tree_width;
			do{
			    memcpy(candidate, best, sizeof(int)*graph_size);
				RandomChange(candidate, 3);
				temp_tree_width = TreeWidth(candidate);
			}while(temp_tree_width > best_treewidth);
		}
		/*else
		{
			worse++;

		    candidate = best;
		}
		if(worse > 8)
		{
			if(worse_neighbour < max_worse_neighbour)
				worse_neighbour++;
			//if(inv_loop > min_inv_loop)
				//--inv_loop;
			if(candidate != best)
			    RandomChange(candidate);
		}*/
	}

	memcpy(EliminateOrder, best, sizeof(int)*graph_size);
	free(e0);
	free(e1);
	free(e2);
}

void PrintEliminateOrder(int *EliminateOrder)
{
	  printf("eliminate order is: ");
      for(int i=0; i<graph_size; ++i)
	  {
		  printf("%d,", EliminateOrder[i]);
	  }
	  printf("\n---------------------------------------------------------------------------------\n");
	  printf("\n---------------------------------------------------------------------------------\n");

}



