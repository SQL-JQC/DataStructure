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
VertexType& GetVex(ALGraph, int);
bool PutVex(ALGraph &, VertexType, VertexType);
int FirstAdjVex(ALGraph, VertexType);
bool equalvex(ElemType, ElemType);
int NextAdjVex(ALGraph, VertexType, VertexType);
void InsertVex(ALGraph &, VertexType);
bool DeleteVex(ALGraph &, VertexType);
bool InsertArc(ALGraph &, VertexType, VertexType);
bool DeleteArc(ALGraph &, VertexType, VertexType);
void DFS(ALGraph, int);
void DFSTraverse(ALGraph, void(*Visit)(VertexType));
void BFSTraverse(ALGraph, void(*Visit)(VertexType));
void DFS1(ALGraph, int, void(*Visit)(VertexType));
void DFSTraverse1(ALGraph, void(*Visit)(VertexType));
void BFSTraverse1(ALGraph, void(*Visit)(VertexType));
void Display(ALGraph);

void visit(VertexType s)
{
	printf("%s ", s);
}

int main(void)
{
	ALGraph G;
	VertexType v = {'A'};
	VertexType w = {'C'};
	VertexType u = {'Z'};
	VertexType x = {'H'};
	char * p;
	int i;
	
	CreateGraph(G);
	
//	PutVex(G, v, x);
//	p = GetVex(G, 0);
//	printf("%s\n", p);
	
//	i = FirstAdjVex(G, v);
//	printf("%d\n", i);
//	i = NextAdjVex(G, v, x);
//	printf("%d\n", i);
	
//	Display(G);
//	InsertVex(G, u);
//	Display(G);
	
//	Display(G);
//	DeleteVex(G, w);
//	Display(G);
	
//	Display(G);
//	InsertArc(G, x, w);
//	Display(G);
	
//	Display(G);
//	DeleteArc(G, x, w);
//	Display(G);
	
//	DFSTraverse(G, visit);
//	BFSTraverse(G, visit);
	
//	DFSTraverse1(G, visit);
//	BFSTraverse1(G, visit);
	
//	Display(G);
	
	DestroyGraph(G);
	
	return 0;
}

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

VertexType& GetVex(ALGraph G, int v)
{
	if(v < 0 || v >= G.vexnum)
	{
		exit(-1);
	}
	
	return G.vertices[v].data;
}

bool PutVex(ALGraph & G, VertexType v, VertexType value)
{
	int i;
	
	i = LocateVex(G, v);
	
	if(i < 0)
	{
		return false;
	}
	
	strcpy(G.vertices[i].data, value);
	
	return true;
}

int FirstAdjVex(ALGraph G, VertexType v)
{
	int v1;
	ArcNode * p;
	
	v1 = LocateVex(G, v);
	p = G.vertices[v1].firstarc;
	
	if(p)
	{
		return p->e.adjvex;
	}
	else
	{
		return -1;
	}
}

bool equalvex(ElemType a, ElemType b)
{
	if(a.adjvex == b.adjvex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int NextAdjVex(ALGraph G, VertexType v, VertexType w)
{
	LinkList p, p1;
	ElemType e;
	int v1;
	
	v1 = LocateVex(G, v);
	e.adjvex = LocateVex(G, w);
	p = Point(G.vertices[v1].firstarc, e, equalvex, p1);
	
	if(!p || !p->next)
	{
		return -1;
	}
	else
	{
		return p->next->e.adjvex;
	}
}

void InsertVex(ALGraph & G, VertexType v)
{
	strcpy(G.vertices[G.vexnum].data, v);
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
}

bool DeleteVex(ALGraph & G, VertexType v)
{
	int i, j, k;
	ElemType e;
	LinkList p, p1;
	
	j = LocateVex(G, v);
	if(j < 0)
	{
		return false;
	}
	
	i = ListLength(G.vertices[j].firstarc);
	G.arcnum -= i;
	
	if(G.kind%2)
	{
		while(G.vertices[j].firstarc)
		{
			ListDelete(G.vertices[j].firstarc, 1, e);
			free(e.info);
		}
	}
	else
	{
		DestroyList(G.vertices[j].firstarc);
	}
	G.vexnum--;
	
	for(i = j; i < G.vexnum; ++i)
	{
		G.vertices[i] = G.vertices[i + 1];
	}
	
	for(i = 0; i < G.vexnum; ++i)
	{
		e.adjvex = j;
		p = Point(G.vertices[i].firstarc, e, equalvex, p1);
		
		if(p)
		{
			if(p1)
			{
				p1->next = p->next;
			}
			else
			{
				G.vertices[i].firstarc = p->next;
			}
			
			if(G.kind < 2)
			{
				G.arcnum--;
				
				if(G.kind == 1)
				{
					free(p->e.info);
				}
			}
			
			free(p);
		}
		
		for(k = j + 1; k <= G.vexnum; ++k)
		{
			e.adjvex = k;
			p = Point(G.vertices[i].firstarc, e, equalvex, p1);
			
			if(p)
			{
				p->e.adjvex--;
			}
		}
	}
	
	return true;
}

bool InsertArc(ALGraph & G, VertexType v, VertexType w)
{
	int i, j;
	ElemType e;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	{
		return false;
	}
	
	G.arcnum++;
	
	e.adjvex = j;
	e.info = NULL;
	
	if(G.kind%2)
	{
		e.info = (int *)malloc(sizeof(int));
		printf("请输入弧(边)%s->%s的权值：", v, w);
		scanf("%d", e.info);
	}
	
	ListInsert(G.vertices[i].firstarc, 1, e);
	if(G.kind > 1)
	{
		e.adjvex = i;
		ListInsert(G.vertices[j].firstarc, 1, e);
	}
	
	return true;
}

bool DeleteArc(ALGraph & G, VertexType v, VertexType w)
{
	int i, j;
	bool k;
	ElemType e;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	{
		return false;
	}
	
	e.adjvex = j;
	
	k = DeleteElem(G.vertices[i].firstarc, e, equalvex);
	
	if(k)
	{
		G.arcnum--;
		
		if(G.kind%2)
		{
			free(e.info);
		}
		
		if(G.kind > 1)
		{
			e.adjvex = i;
			DeleteElem(G.vertices[j].firstarc, e, equalvex);
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

bool visited[MAX_VERTEX_NUM];
void(*VisitFunc)(VertexType);

void DFS(ALGraph G, int v)
{
	int w;
	
	visited[v] = true;
	VisitFunc(G.vertices[v].data);
	
	for(w = FirstAdjVex(G, G.vertices[v].data); w >= 0; w = NextAdjVex(G, G.vertices[v].data, G.vertices[w].data))
	{
		if(!visited[w])
		{
			DFS(G, w);
		}
	}
}

void DFSTraverse(ALGraph G, void(*Visit)(VertexType))
{
	int v;
	
	VisitFunc = Visit;
	
	for(v = 0; v < G.vexnum; ++v)
	{
		visited[v] = false;
	}
	
	for(v = 0; v < G.vexnum; ++v)
	{
		if(!visited[v])
		{
			DFS(G, v);
		}
	}
	
	printf("\n");
}

# include "ALGraphQueue.cpp"

void BFSTraverse(ALGraph G, void(*Visit)(VertexType))
{
	int v, u, w;
	Queue q;
	
	for(v = 0; v < G.vexnum; ++v)
	{
		visited[v] = false;
	}
	
	initQueue(&q);
	
	for(v = 0; v < G.vexnum; ++v)
	{
		if(!visited[v])
		{
			visited[v] = true;
			Visit(G.vertices[v].data);
			
			enqueue(&q, v);
			while(!emptyQueue(&q))
			{
				dequeue(&q, &u);
				
				for(w = FirstAdjVex(G, G.vertices[u].data); w >= 0; w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data))
				{
					if(!visited[w])
					{
						visited[w] = true;
						Visit(G.vertices[w].data);
						enqueue(&q, w);
					}
				}
			}
		}
	}
	
	printf("\n");
	
	destroyQueue(&q);
}

void DFS1(ALGraph G, int v, void(*Visit)(VertexType))
{
	ArcNode * p;
	
	visited[v] = true;
	Visit(G.vertices[v].data);
	
	for(p = G.vertices[v].firstarc; p; p = p->nextarc)
	{
		if(!visited[p->e.adjvex])
		{
			DFS1(G, p->e.adjvex, Visit);
		}
	}
}

void DFSTraverse1(ALGraph G, void(*Visit)(VertexType))
{
	int v;
	
	for(v = 0; v < G.vexnum; ++v)
	{
		visited[v] = false;
	}
	
	for(v = 0; v < G.vexnum; ++v)
	{
		if(!visited[v])
		{
			DFS1(G, v, Visit);
		}
	}
	
	printf("\n");
}

void BFSTraverse1(ALGraph G, void(*Visit)(VertexType))
{
	int v, u;
	ArcNode * p;
	Queue q;
	
	for(v = 0; v < G.vexnum; ++v)
	{
		visited[v] = false;
	}
	
	initQueue(&q);
	
	for(v = 0; v < G.vexnum; ++v)
	{
		if(!visited[v])
		{
			visited[v] = true;
			Visit(G.vertices[v].data);
			
			enqueue(&q, v);
			while(!emptyQueue(&q))
			{
				dequeue(&q, &u);
				
				for(p = G.vertices[u].firstarc; p; p = p->nextarc)
				{
					if(!visited[p->e.adjvex])
					{
						visited[p->e.adjvex] = true;
						Visit(G.vertices[p->e.adjvex].data);
						enqueue(&q, p->e.adjvex);
					}
				}
			}
		}
	}
	
	printf("\n");
	
	destroyQueue(&q);
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

