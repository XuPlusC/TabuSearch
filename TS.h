#ifndef TABUSEARCH_H_INCLUDED
#define TABUSEARCH_H_INCLUDED

#include "graph.h"

extern const int colorNum_Max;

//int DSATUR_start(HeadNodePtr G, int length);
//int degs(HeadNodePtr G, int vertex, int colorNum_Max);
void random_init(HeadNodePtr &G, int length);
void generate_ACT(HeadNodePtr G, int ACT[][colorNum_Max], int length);
void TabuSearch(HeadNodePtr &G, int length, int ACT[][colorNum_Max], int TTT[][colorNum_Max]);
void FindMove(int &u, int &vi, int &vj, int &delt, int f, int min_f, int iter, HeadNodePtr &G, int length, int ACT[][colorNum_Max], int TTT[][colorNum_Max]);
void MakeMove(int u, int vi, int vj, int delt, int &f, int iter, HeadNodePtr &G, int length, int ACT[][colorNum_Max], int TTT[][colorNum_Max]);
int calculate_F(HeadNodePtr G, int length);
#endif // TABUSEARCH_H_INCLUDED
