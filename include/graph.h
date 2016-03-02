#ifndef _GRAPH_H_
#define _GRAPH_H_

// ==============================constant============================== 
#define MaxGraphSize 500
// ===========================constant end============================= 


// ==========================global variable=========================== 

extern int graph[][MaxGraphSize];

extern bool adjacent[][MaxGraphSize];
extern int numNeighbour[];
extern int graph_size;

extern bool EliminateVertex[];


extern bool temp_adjacent[][MaxGraphSize];
extern int temp_numNeighbour[];

// ======================global variable end=========================== 


// ===========================Function================================= 
// creat graph
extern void CreateGraph(char *GraphFileName);

extern int TreeWidthWithMaxCliqueVertex(int* EliminateOrder, int* CauseMaxCliqueVertex);

extern int TreeWidth(int* EliminateOrder);

//=========================Function end================================

#endif
