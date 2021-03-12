# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# include "ALGraphFunction.cpp"
# include "TopoStack.cpp"

void FindInDegree(ALGraph, int indegree[]);
bool TopologicalSort(ALGraph);

int main(void)
{
	ALGraph G;
	
	printf("请选择有向图\n");
	CreateGraph(G);
	Display(G);
	TopologicalSort(G);
	
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

bool TopologicalSort(ALGraph G)
{
	int i, k;
	int count = 0;
	int indegree[MAX_VERTEX_NUM];
	Stack s;
	ArcNode * p;
	
	FindInDegree(G, indegree);
	
	initStack(&s);
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(!indegree[i])
		{
			push(&s, i);
		}
	}
	
	while(!emptyStack(&s))
	{
		pop(&s, &i);
		
		printf("%s ", G.vertices[i].data);
		
		count++;
		
		for(p = G.vertices[i].firstarc; p; p = p->nextarc)
		{
			k = p->e.adjvex;
			if(!(--indegree[k]))
			{
				push(&s, k);
			}
		}
	}
	
	destroyStack(&s);
	
	if(count < G.vexnum)
	{
		printf("此有向图有回路\n");
		return false;
	}
	else
	{
		printf("为一个拓扑序列。\n");
		return true;
	}
}

