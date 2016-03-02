#include"graph.h"
#include"eliminate.h"
#include<stdio.h>
#include<string.h>
#include<memory.h>
#include<assert.h>
#include<time.h>


/* creat graph */
void CreateGraph(char *GraphFileName)
{
	FILE *pFile = fopen(GraphFileName, "r");
    /*The size of buf should be limited by the max line in the graph source file.*/
	char buf[100];
	memset(numNeighbour, 0, sizeof(int)*MaxGraphSize);
    while(fgets(buf, 100, pFile)!=NULL)
	{
        if (buf[0]!='e') 
		{
            continue;
        }
		int v1 = 0;
		int v2 = 0;
		sscanf(buf+2, "%d %d", &v1, &v2);
		int num = v2 > v1? v2:v1;
        if (num > graph_size) 
		{
            graph_size = num;
        }

		--v1;
		--v2;

		if(adjacent[v1][v2] == true)
			continue;

        int index_v1_v2 = numNeighbour[v1];
        graph[v1][index_v1_v2] = v2;
        adjacent[v1][v2] = true;
		numNeighbour[v1]++;

		int index_v2_v1 = numNeighbour[v2];
		graph[v2][index_v2_v1] = v1;
		adjacent[v2][v1] = true;
		numNeighbour[v2]++;
	}
	fclose(pFile);
}

inline static int MakeupClique(int vertex )
{
	int nUnerasedNeighbors = 0;
    int selectedNeighbor = -1;
    int selectedNeighborPosition = graph_size;

	int vertex_num_neighbour = temp_numNeighbour[vertex];

     for(int start = 0; start < vertex_num_neighbour; ++start)
	 {
		 int v1 = graph[vertex][start];

		 assert(v1 >= 0 && v1 < graph_size);
		 
		 if(EliminateVertex[v1] == true)
			 continue;
		 
		 ++nUnerasedNeighbors;

        if (indexEliminateOrder[v1] < selectedNeighborPosition) {
            selectedNeighbor = v1;
            selectedNeighborPosition = indexEliminateOrder[v1];
        }

	 }

	 int v1 = selectedNeighbor;

	 if(nUnerasedNeighbors >1){
		for(int end = 0; end < vertex_num_neighbour; ++end)
		{
			int v2 = graph[vertex][end];

			assert(v2 >= 0 && v2 < graph_size);

			if(EliminateVertex[v2] == true)
				continue;
			if(v1 == v2)
				continue;
			if(temp_adjacent[v1][v2] == false)
			{
				graph[v1][temp_numNeighbour[v1]++] = v2;
	            temp_adjacent[v1][v2] = true;

	            graph[v2][temp_numNeighbour[v2]++] = v1;
	            temp_adjacent[v2][v1] = true;
			}
		}
	 }
	return nUnerasedNeighbors;	 
}



int TreeWidthWithMaxCliqueVertex(int* EliminateOrder, int* CauseMaxCliqueVertex)
{
	memcpy(temp_adjacent, adjacent, sizeof(bool)*MaxGraphSize*MaxGraphSize);
	memcpy(temp_numNeighbour, numNeighbour, sizeof(int)*graph_size);
	memset(EliminateVertex, false, sizeof(bool)*graph_size);

	for(int i=0; i < graph_size; ++i)
	{
		indexEliminateOrder[EliminateOrder[i]] = i;
	}

	int treewidth = -1;

	for(int i = 0; i < graph_size; ++i)
	{
		if(treewidth > (graph_size - i))
			break;

		int v = EliminateOrder[i];
				
        int CliqueSize = MakeupClique(v);
			
        EliminateVertex[v] = true;
		
		if(treewidth < CliqueSize)
		{
			treewidth = CliqueSize;
			*CauseMaxCliqueVertex = v;
		}
	}

	return treewidth;
}
 

int TreeWidth(int *EliminateOrder)
{
	int temp;
	return TreeWidthWithMaxCliqueVertex(EliminateOrder, &temp);
}

