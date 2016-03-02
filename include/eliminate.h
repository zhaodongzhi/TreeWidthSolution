#ifndef _ELIMINATE_H_
#define _ELIMINATE_H_

#include"graph.h"
#include<sstream>


/* ==========================globla variable=========================== */
extern int EliminateOrder[];
extern int indexEliminateOrder[];
extern int inv_loop;
extern int min_inv_loop;
/* ======================globla variable end=========================== */


/* ===========================Function================================= */

/* creat a eliminate order and put the result in array EliminateOrder */
extern void InitOrder(int* EliminateOrder);  

/* After InitOrder swap some point in array EliminateOrder by some rules and make a new eliminate order */
extern void ChoosePointAndSwap(int* EliminateOrder);

extern void PrintEliminateOrder(int *EliminateOrder);

/*=========================Function end================================ */

#endif


