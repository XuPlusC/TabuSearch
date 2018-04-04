#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
const int colorNum_Max = 28;

typedef struct arcNode{
    int name;
    struct arcNode *next;
}ArcNode, *ArcNodePtr;

typedef struct headNode{
    int degree;
    int color;
    ArcNodePtr arc;
}HeadNode, *HeadNodePtr;

void InsertArc(HeadNodePtr &G, int start, int target);
int CreateGraph(HeadNodePtr &G);
#endif // GRAPH_H_INCLUDED
