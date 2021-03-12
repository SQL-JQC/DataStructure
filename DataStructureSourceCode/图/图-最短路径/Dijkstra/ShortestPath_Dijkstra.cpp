# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <limits.h>

# include "MGraphFunction.cpp"

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef VRType ShortPathTable[MAX_VERTEX_NUM];

void ShortestPath_Dijkstra(MGraph, int, PathMatrix, ShortPathTable);

int main(void)
{
	MGraph G;
	PathMatrix P;
	ShortPathTable D;
	int i;
	
	CreateDN(G);
	Display(G);
	ShortestPath_Dijkstra(G, 0, P, D);
	printf("%s到各顶点的最短路径长度为：\n", G.vexs[0]);
	for(i = 0; i < G.vexnum; ++i)
	{
		if(i != 0)
		{
			printf("%s-%s:%d\n", G.vexs[0], G.vexs[i], D[i]);
		}
	}

	DestroyGraph(G);
	
	return 0;
}

void ShortestPath_Dijkstra(MGraph G, int v0, PathMatrix P, ShortPathTable D)
{
	int v, w, i, j;
	VRType min;
	bool final[MAX_VERTEX_NUM];
	
	for(v = 0; v < G.vexnum; ++v)
	{
		final[v] = false;
		D[v] = G.arcs[v0][v].adj;
		for(w = 0; w < G.vexnum; ++w)
		{
			P[v][w] = false;
		}
		if(D[v] < INFINITY)
		{
			P[v][v0] = P[v][v] = true;
		}
	}
	
	D[v0] = 0;
	final[v0] = true;
	
	for(i = 1; i < G.vexnum; ++i)
	{
		min = INFINITY;
		
		for(w = 0; w < G.vexnum; ++w)
		{
			if(!final[w] && D[w] < min)
			{
				v = w;
				min = D[w];
			}
		}
		
		final[v] = true;
		
		for(w = 0; w < G.vexnum; ++w)
		{
			if(!final[w] && min < INFINITY && G.arcs[v][w].adj < INFINITY && (min + G.arcs[v][w].adj < D[w]))
			{
				D[w] = min + G.arcs[v][w].adj;
				for(j = 0; j < G.vexnum; ++j)
				{
					P[w][j] = P[v][j];
				}
				P[w][w] = true;
			}
		}
	}
}

