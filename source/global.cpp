#include"graph.h"
#include"eliminate.h"
#include<string>

int graph[MaxGraphSize][MaxGraphSize];
bool adjacent[MaxGraphSize][MaxGraphSize];
int numNeighbour[MaxGraphSize];
int graph_size;

int EliminateOrder[MaxGraphSize];

int inv_loop;
int min_inv_loop;

bool EliminateVertex[MaxGraphSize];
int indexEliminateOrder[MaxGraphSize];
bool temp_adjacent[MaxGraphSize][MaxGraphSize];
int temp_numNeighbour[MaxGraphSize];




