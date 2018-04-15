#include "TS.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern const int colorNum_Max;
#define MaxIter 100000000		//????

void random_init(HeadNodePtr &G, int length)
{
	srand((unsigned)time(NULL));
	int i;
	for(i = 0; i < length; ++i)
	{
		(G+i)->color = rand()%(colorNum_Max-1);
	}
}

void generate_ACT(HeadNodePtr G, int ACT[][colorNum_Max], int length)
{
	int i, j, colorMark[colorNum_Max] = {0};
	ArcNodePtr tempPtr;
	/*
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < colorNum_Max; ++j)
			colorMark[j] = 0;

		tempPtr = (G+i)->arc;
		while(tempPtr != NULL)
		{
			++(colorMark[(G+tempPtr->name)->color]);
			tempPtr = tempPtr->next;
		}
		for(j = 0; j < colorNum_Max; ++j)
			ACT[i][j] = colorMark[j];
	}
	*/
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < colorNum_Max; ++j)
			ACT[i][j] = 0;
	}
	for(i = 0; i < length; ++i)
	{
		tempPtr = (G+i)->arc;
		while(tempPtr != NULL)
		{
			ACT[i][(G+tempPtr->name)->color] += 1;
			tempPtr = tempPtr->next;
		}
	}

}

void TabuSearch(HeadNodePtr &G, int length,
		int ACT[][colorNum_Max], int TTT[][colorNum_Max])
{
	int u, vi, vj, delt, iter = 1, min_f = 0;
	random_init(G, length);
	generate_ACT(G, ACT, length);
	int f = calculate_F(G, length);
	printf("original f:%d\n",f);
	min_f = f;

	//4.15 update
	int i;
	int sol[length];
	for(i = 0; i < length;++i)
	{
		sol[i] = (G+i)->color;
	}

	//end of 4.15 update



	for(; f > 0; iter++)
	{
		FindMove(u, vi, vj, delt, f, min_f, iter, G, sol, length, ACT, TTT);
		MakeMove(u, vi, vj, delt, f, iter, G, sol, length, ACT, TTT);
		//printf("iter %d: move : vex %d from color %d to %d.current f is :%d\n", iter, u, vi, vj,f);
		if(f < min_f)
			min_f = f;
        //if(iter % 10000 == 0)
         //  printf("f now :%d\n", f);
	}
}

void FindMove(int &u, int &vi, int &vj, int &delt, int f, int min_f, int iter, HeadNodePtr &G, int sol[],
	int length, int ACT[][colorNum_Max], int TTT[][colorNum_Max])
{
	int i, k, loc_delt;

	int tabu_best_u ,tabu_best_vi, tabu_best_vj, tabu_best_delt = 100000;
	int non_t_best_u, non_t_best_vi, non_t_best_vj, non_t_best_delt = 100000;


	/*
	int tabu_best_u = rand()%length;
	int tabu_best_vi = (G+tabu_best_u)->color;
	int tabu_best_vj = rand()%colorNum_Max;
	int tabu_best_delt = ACT[tabu_best_u][tabu_best_vj]-ACT[tabu_best_u][tabu_best_vi];

	int non_t_best_u = rand()%length;
	int non_t_best_vi = (G+non_t_best_u)->color;
	int non_t_best_vj = rand()%colorNum_Max;
	int non_t_best_delt = ACT[non_t_best_u][non_t_best_vj]-ACT[non_t_best_u][non_t_best_vi];
	*/

	u = rand()%length;
	vi = sol[u];//vi = (G+u)->color;
	vj = rand()%colorNum_Max;
	delt = ACT[u][vj]-ACT[u][vi];


	for(i = 0; i < length; ++i)		//i refers to vex
	{
		if(ACT[i][sol[i]] > 0)		//vex i has confliction
		{								//checking all critical one move of vex i
			for(k = 0; k < colorNum_Max; ++k)	//k refers to color
			{
				if(k != sol[i])	//move the color of vex i from original color to color k
				{
					//calculate delt value of the move <i, Sol[i], k>
					loc_delt = ACT[i][k]-ACT[i][sol[i]];

					if(iter < TTT[i][k])
					{
						//update tabu best move
						if(loc_delt < tabu_best_delt)
						{
							tabu_best_delt = loc_delt;
							tabu_best_u = i;
							tabu_best_vi = sol[i];
							tabu_best_vj = k;
						}
					}
					else
					{
						//update non-tabu best move
						if(loc_delt < non_t_best_delt)
						{
							non_t_best_delt = loc_delt;
							non_t_best_u = i;
							non_t_best_vi = sol[i];
							non_t_best_vj = k;
						}
					}
				}
			}
		}
	}		//end of checking all critical one move
	if( f + tabu_best_delt < min_f)
	{
		//<u, vi, vj, delt> = the tabu best move;
		u = tabu_best_u;
		vi = tabu_best_vi;
		vj = tabu_best_vj;
		delt = tabu_best_delt;
		//printf("current min_f is %d, but tabu can be %d\n", min_f, f+tabu_best_delt);
	}
	else
	{
		//<u, vi, vj, delt> = the non-tabu best move;
		u = non_t_best_u;
		vi = non_t_best_vi;
		vj = non_t_best_vj;
		delt = non_t_best_delt;
	}
}

void MakeMove(int u, int vi, int vj, int delt, int &f, int iter, HeadNodePtr &G, int sol[],
	int length, int ACT[][colorNum_Max], int TTT[][colorNum_Max])
{
	sol[u] = vj;
	f = f + delt;
	//need to srand?
	//srand((unsigned)time(NULL));
	TTT[u][vi] = iter+f+rand()%10;
	//printf("\t\ttabu update:%d\n", TTT[u][vi]);
	//update ACT
	ArcNodePtr tempPtr = (G+u)->arc;
	while(tempPtr != NULL)
	{
		--(ACT[tempPtr->name][vi]);
		++(ACT[tempPtr->name][vj]);
		tempPtr = tempPtr->next;
	}
}

int calculate_F(HeadNodePtr G, int length)
{
	ArcNodePtr tempPtr;
	int i, j, sum = 0, thisColor;
	for(i = 0; i < length; ++i)
	{
		tempPtr = (G+i)->arc;
		thisColor = (G+i)->color;
		while(tempPtr != NULL)
		{
			if((G+tempPtr->name)->color == thisColor)
				++sum;
			tempPtr = tempPtr->next;
		}
	}
	sum /= 2;
	return sum;
}
