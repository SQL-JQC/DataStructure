# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# include "ALGraphFunction.cpp"
# include "CritiStack.cpp"

void FindInDegree(ALGraph, int indegree[]);
bool TopologicalOrder(ALGraph, Stack *);
bool CriticalPath(ALGraph);

int main(void)
{
	ALGraph G;
	
	printf("请选择有向网\n");
	CreateGraph(G);
	Display(G);
	CriticalPath(G);
	
	DestroyGraph(G);
	
	return 0;
}

void FindInDegree(ALGraph G, int indegree[])
{
	int i;
	ArcNode * p;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		indegree[i] = 0;
	}
	
	for(i = 0; i < G.vexnum; ++i)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			indegree[p->e.adjvex]++;
			p = p->nextarc;
		}
	}
}

InfoType ve[MAX_VERTEX_NUM];

bool TopologicalOrder(ALGraph G, Stack * T)
{
	int i, k;
	int count = 0;
	int indegree[MAX_VERTEX_NUM];
	Stack s;
	ArcNode * p;
	
	FindInDegree(G, indegree);
	
	initStack(&s);
	
	printf("拓扑序列：");
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(!indegree[i])
		{
			push(&s, i);
		}
	}
	
	initStack(T);
	
	for(i = 0; i < G.vexnum; ++i)
	{
		ve[i] = 0;
	}
	
	while(!emptyStack(&s))
	{
		pop(&s, &i);
		
		printf("%s ", G.vertices[i].data);
		
		push(T, i);
		
		count++;
		
		for(p = G.vertices[i].firstarc; p; p = p->nextarc)
		{
			k = p->e.adjvex;
			if(!(--indegree[k]))
			{
				push(&s, k);
			}
			
			if(ve[i] + *(p->e.info) > ve[k])
			{
				ve[k] = ve[i] + *(p->e.info);
			}
		}
	}
	
	destroyStack(&s);
	
	if(count < G.vexnum)
	{
		printf("此有向网有回路\n");
		return false;
	}
	else
	{
		return true;
	}
}

bool CriticalPath(ALGraph G)
{
	InfoType vl[MAX_VERTEX_NUM];
	Stack T;
	int i, k;
	InfoType j, ee, el, dut;
	ArcNode * p;
	
	if(!TopologicalOrder(G, &T))
	{
		return false;
	}
	
	j = ve[0];
	for(i = 1; i < G.vexnum; ++i)
	{
		if(ve[i] > j)
		{
			j = ve[i];
		}
	}
	
	for(i = 0; i < G.vexnum; ++i)
	{
		vl[i] = j;
	}
	
	while(!emptyStack(&T))
	{
		for(pop(&T, &j), p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->e.adjvex;
			dut = *(p->e.info);
			if(vl[k] - dut < vl[j])
			{
				vl[j] = vl[k] - dut;
			}
		}
	}
	
	destroyStack(&T);
	
	printf("\ni ve[i] vl[i]\n");
	for(i = 0; i < G.vexnum; ++i)
	{
		printf("%d   %d     %d", i, ve[i], vl[i]);
		if(ve[i] == vl[i])
		{
			printf(" 关键路径经过的顶点"); 
		}
		printf("\n");
	}
	
	printf("j   k  权值  ee  el\n");
	for(j = 0; j < G.vexnum; ++j)
	{
		for(p = G.vertices[j].firstarc; p; p = p->nextarc)
		{
			k = p->e.adjvex;
			dut = *(p->e.info);
			ee = ve[j];
			el = vl[k] - dut;
			
			printf("%s->%s %3d %3d %3d ", G.vertices[j].data, G.vertices[k].data, dut, ee, el);
			if(ee == el)
			{
				printf("关键活动"); 
			}
			printf("\n");
		}
	}
	
	return true;
}

