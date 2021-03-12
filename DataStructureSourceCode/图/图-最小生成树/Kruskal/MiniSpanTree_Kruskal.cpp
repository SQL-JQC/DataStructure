# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <limits.h>

# include "MGraphFunction.cpp"

void MiniSpanTree_Kruskal(MGraph);

int main(void)
{
	MGraph G;
	
	CreateUDN(G);
	Display(G);
	MiniSpanTree_Kruskal(G);
	
	DestroyGraph(G);
	
	return 0;
}

void MiniSpanTree_Kruskal(MGraph G)
{
	int set[MAX_VERTEX_NUM];
	int i, j;
	int k = 0, a = 0, b = 0;
	VRType min = G.arcs[a][b].adj;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		set[i] = i;
	}
	
	printf("最小代价生成树的各条边为：\n");
	while(k < G.vexnum - 1)
	{
		for(i = 0; i < G.vexnum; ++i)
		{
			for(j = i + 1; j < G.vexnum; ++j)
			{
				if(G.arcs[i][j].adj < min)
				{
					min = G.arcs[i][j].adj;
					a = i;
					b = j;
				}
			}
		}
		
		min = G.arcs[a][b].adj = INFINITY;
		
		if(set[a] != set[b])
		{
			printf("(%s-%s)\n", G.vexs[a], G.vexs[b]);
			
			k++;
			
			for(i = 0; i < G.vexnum; ++i)
			{
				if(set[i] == set[b])
				{
					set[i] = set[a];
				}
			}
		}
	}
}

