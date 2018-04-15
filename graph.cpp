#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int CreateGraph(HeadNodePtr &headPtr)
{
	HeadNodePtr head, G;
	int target, arc, i, length;
    FILE *fp = fopen("arc.txt", "r");
	fscanf(fp, "%d", &length);

    G = (HeadNodePtr)malloc(length*sizeof(HeadNode));
    head = G;

    for(i = 0; i < length; ++i)
    {
    	(G+i)->degree = 0;
    	(G+i)->color = 0;
    	(G+i)->arc = NULL;
    }

    while(!feof(fp))
    {
        fscanf(fp, "%d%d", &target, &arc);
        InsertArc(head, target-1, arc-1);
        //printf("arc added! %d--%d\n", target, arc);
    }

    headPtr = head;
	return length;
}

void InsertArc(HeadNodePtr &G, int start, int target)
{
	ArcNodePtr arcPtr;
	HeadNodePtr vex = G + start;
	if(vex->arc == NULL)
	{
		vex->arc = (ArcNodePtr)malloc(sizeof(ArcNode));
		vex->arc->name = target;
		vex->arc->next = NULL;
		vex->degree++;
	}
	else
	{
		arcPtr = vex->arc;
		while(arcPtr->next != NULL)
			arcPtr = arcPtr->next;
		arcPtr->next = (ArcNodePtr)malloc(sizeof(ArcNode));
		arcPtr->next->name = target;
		arcPtr->next->next = NULL;
		vex->degree++;
	}

	vex = G+target;
	if(vex->arc == NULL)
	{
		vex->arc = (ArcNodePtr)malloc(sizeof(ArcNode));
		vex->arc->name = start;
		vex->arc->next = NULL;
		vex->degree++;
	}
	else
	{
		arcPtr = vex->arc;
		while(arcPtr->next != NULL)
			arcPtr = arcPtr->next;
		arcPtr->next = (ArcNodePtr)malloc(sizeof(ArcNode));
		arcPtr->next->name = start;
		arcPtr->next->next = NULL;
		vex->degree++;
	}
}
