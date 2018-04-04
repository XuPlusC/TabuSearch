#include <iostream>
#include "graph.h"
#include "TS.h"

extern const int colorNum_Max;

int main()
{
	HeadNodePtr G;
    int length = CreateGraph(G);
    int i, j;
    //printf("%d\n", G->degree);
    //DSATUR_start(G, length);

    //random_init(G, length);
    //printf("initial ok!\n");
    int ACT[length][colorNum_Max];
    int TTT[length][colorNum_Max];
    //generate_ACT(G, ACT, length);
    //printf("generate oK!\n");

    TabuSearch(G, length, ACT, TTT);

    ArcNodePtr tempPtr;
    int sum = 0, thisColor;
    for(i = 0; i < length; ++i)
    {
        tempPtr = (G+i)->arc;
        thisColor = (G+i)->color;
        while(tempPtr != NULL)
        {
            if(thisColor == (G+tempPtr->name)->color)
                sum++;
            tempPtr = tempPtr->next;
        }
    }
    printf("%d\n", sum);
    return 0;
}
