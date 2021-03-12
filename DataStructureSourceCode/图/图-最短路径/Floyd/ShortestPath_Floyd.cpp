# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <limits.h>

# include "MGraphFunction.cpp"

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef VRType DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void ShortestPath_Floyd(MGraph, PathMatrix, DistancMatrix);

int main(void)
{
	MGraph G;
	int i, j;
	PathMatrix P;
	DistancMatrix D;
	
	CreateDN(G);
	for(i = 0; i < G.vexnum; ++i)
	{
		G.arcs[i][i].adj = 0;
	}
	Display(G);
	ShortestPath_Floyd(G, P, D);
	printf("D矩阵：\n");
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			printf("%6d", D[i][j]);
		}
		printf("\n");
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			if(i != j)
			{
				printf("%s到%s的最短距离为%d\n", G.vexs[i], G.vexs[j], D[i][j]);
			}
		}
	}
	
	DestroyGraph(G);
	
	return 0;
}

void ShortestPath_Floyd(MGraph G, PathMatrix P, DistancMatrix D)
{
	int u, v, w, i;
	
	for(v = 0; v < G.vexnum; ++v)
	{
		for(w = 0; w < G.vexnum; ++w)
		{
			D[v][w] = G.arcs[v][w].adj;
			for(u = 0; u < G.vexnum; ++u)
			{
				P[v][w][u] = false;
			}
			if(D[v][w] < INFINITY)
			{
				P[v][w][v] = P[v][w][w] = true;
			}
		}
	}
	
	for(u = 0; u < G.vexnum; ++u)
	{
		for(v = 0; v < G.vexnum; ++v)
		{
			for(w = 0; w < G.vexnum; ++w)
			{
				if(D[v][u] < INFINITY && D[u][w] < INFINITY && D[v][u] + D[u][w] < D[v][w])
				{
					D[v][w] = D[v][u] + D[u][w];
					for(i = 0; i < G.vexnum; ++i)
					{
						P[v][w][i] = P[v][u][i] || P[u][w][i];
					}
				}
			}
		}
	}
}

