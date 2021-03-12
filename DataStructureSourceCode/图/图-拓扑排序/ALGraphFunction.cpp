# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

# define MAX_NAME 3
# define MAX_VERTEX_NUM 20

typedef int InfoType;
typedef char VertexType[MAX_NAME];

typedef enum GraphKind
{
	DG, DN, UDG, UDN
} GraphKind;

typedef struct ElemType
{
	int adjvex;
	InfoType * info;
} ElemType;

typedef struct ArcNode
{
	ElemType e;
	struct ArcNode * nextarc;
} ArcNode;

typedef struct VexNode
{
	VertexType data;
	ArcNode * firstarc;
} VexNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph
{
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
} ALGraph;

# define LNode ArcNode
# define next nextarc
typedef ArcNode * LinkList;

int LocateVex(ALGraph, VertexType);
void CreateGraph(ALGraph &);
void DestroyGraph(ALGraph &);
void Display(ALGraph);

# include "ALGraphLinkList.cpp"

int LocateVex(ALGraph G, VertexType u)
{
	int i;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(strcmp(u, G.vertices[i].data) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

void CreateGraph(ALGraph & G)
{
	int i, j, k, w;
	VertexType va, vb;
	ElemType e;
	
	printf("请输入图的类型(有向图:0, 有向网:1, 无向图:2, 无向网:3)：");
	scanf("%d", &G.kind);
	
	printf("请输入图的顶点数，边数：");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	printf("请输入%d个顶点的值(<%d个字符)：\n", G.vexnum, MAX_NAME);
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%s", G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	
	if(G.kind%2)
	{
		printf("请输入每条弧(边)的权值，弧尾(顶点1)和弧头(顶点2)：\n");
	}
	else
	{
		printf("请输入每条弧(边)的弧尾(顶点1)和弧头(顶点2)：\n");
	}
	for(k = 0; k < G.arcnum; ++k)
	{
		if(G.kind%2)
		{
			scanf("%d%s%s", &w, va, vb);
		}
		else
		{
			scanf("%s%s", va, vb);
		}
		
		i = LocateVex(G, va);
		j = LocateVex(G, vb);
		e.adjvex = j;
		e.info = NULL;
		
		if(G.kind%2)
		{
			e.info = (int *)malloc(sizeof(int));
			*(e.info) = w;
		}
		
		ListInsert(G.vertices[i].firstarc, 1, e);
		if(G.kind > 1)
		{
			e.adjvex = i;
			ListInsert(G.vertices[j].firstarc, 1, e);
		}
	}
}

void DestroyGraph(ALGraph & G)
{
	int i;
	ElemType e;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.kind%2)
		{
			while(G.vertices[i].firstarc)
			{
				ListDelete(G.vertices[i].firstarc, 1, e);
				if(G.kind < 2)
				{
					free(e.info);
				}
				else
				{
					if(e.adjvex > i)
					{
						free(e.info);
					}
				}
			}
		}
		else
		{
			DestroyList(G.vertices[i].firstarc);
		}
	}
	
	G.vexnum = 0;
	G.arcnum = 0;
}

void Display(ALGraph G)
{
	int i;
	ArcNode * p;
	
	switch(G.kind)
	{
		case DG:
			printf("有向图\n");
			break;
		case DN:
			printf("有向网\n");
			break;
		case UDG:
			printf("无向图\n");
			break;
		case UDN:
			printf("无向网\n");
			break;
	}
	
	printf("%d个顶点：\n", G.vexnum);
	for(i = 0; i < G.vexnum; ++i)
	{
		printf("%s ", G.vertices[i].data);
	}
	
	printf("\n%d条弧(边)：\n", G.arcnum);
	for(i = 0; i < G.vexnum; ++i)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			if(G.kind < 2 || p->e.adjvex > i)
			{
				printf("%s->%s ", G.vertices[i].data, G.vertices[p->e.adjvex].data);
				if(G.kind%2)
				{
					printf(":%d ", *(p->e.info));
				}
			}
			
			p = p->nextarc;
		}
		printf("\n");
	}
}

