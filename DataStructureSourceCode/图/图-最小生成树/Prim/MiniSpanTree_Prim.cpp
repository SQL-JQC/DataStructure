# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

# include "MGraphFunction.cpp"

typedef struct Node
{
	VertexType adjvex;
	VRType lowcost;
} minside[MAX_VERTEX_NUM];

int minimum(minside, MGraph);
void MiniSpanTree_Prim(MGraph, VertexType);

int main(void)
{
	MGraph G;
	
	CreateUDN(G);
	Display(G);
	MiniSpanTree_Prim(G, G.vexs[0]);
	
	DestroyGraph(G);
	
	return 0;
}

int minimum(minside SZ, MGraph G)
{
	int i = 0;
	int j, k;
	VRType min;
	
	while(!SZ[i].lowcost)
	{
		i++;
	}
	
	min = SZ[i].lowcost;
	k = i;
	
	for(j = i + 1; j < G.vexnum; ++j)
	{
		if(SZ[j].lowcost > 0 && SZ[j].lowcost < min)
		{
			min = SZ[j].lowcost;
			k = j;
		}
	}
	
	return k;
}

void MiniSpanTree_Prim(MGraph G, VertexType u)
{
	int i, j, k;
	minside closedge;
	
	k = LocateVex(G, u);
	
	for(j = 0; j < G.vexnum; ++j)
	{
		strcpy(closedge[j].adjvex, u);
		closedge[j].lowcost = G.arcs[k][j].adj;
	}
	
	closedge[k].lowcost = 0;
	
	printf("最小代价生成树的各条边为：\n");
	for(i = 1; i < G.vexnum; ++i)
	{
		k = minimum(closedge, G);
		
		printf("(%s-%s)\n", closedge[k].adjvex, G.vexs[k]);
		
		closedge[k].lowcost = 0;
		
		for(j = 0; j < G.vexnum; ++j)
		{
			if(G.arcs[k][j].adj < closedge[j].lowcost)
			{
				strcpy(closedge[j].adjvex, G.vexs[k]);
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
	}
}

