# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

# define MAX_NAME 3
# define MAX_VERTEX_NUM 20

typedef int InfoType;
typedef char VertexType[MAX_NAME];

typedef enum VisitIf
{
	unvisited, visited
} VisitIf;

typedef struct EBox
{
	VisitIf mark;
	int ivex, jvex;
	struct EBox * ilink, * jlink;
	InfoType * info;
} EBox;

typedef struct VexBox
{
	VertexType data;
	EBox * firstedge;
} VexBox, AMList[MAX_VERTEX_NUM];

typedef struct AMLGraph
{
	AMList adjmulist;
	int vexnum, edgenum;
} AMLGraph;

int LocateVex(AMLGraph, VertexType);
void CreateUDG(AMLGraph &);
void DestroyUDG(AMLGraph &);
VertexType& GetVex(AMLGraph, int);
bool PutVex(AMLGraph &, VertexType, VertexType);
int FirstAdjVex(AMLGraph, VertexType);
int NextAdjVex(AMLGraph, VertexType, VertexType);
bool InsertVex(AMLGraph &, VertexType);
bool DeleteVex(AMLGraph &, VertexType);
bool InsertArc(AMLGraph &, VertexType, VertexType);
bool DeleteArc(AMLGraph &, VertexType, VertexType);
void DFS(AMLGraph, int);
void DFSTraverse(AMLGraph, void(*Visit)(VertexType));
void BFSTraverse(AMLGraph, void(*Visit)(VertexType));
void MarkUnvizited(AMLGraph);
void Display(AMLGraph);

void visit(VertexType s)
{
	printf("%s ", s);
}

int main(void)
{
	AMLGraph G;
	VertexType v = {'A'};
	VertexType w = {'C'};
	VertexType u = {'Z'};
	VertexType x = {'H'};
	char * p;
	int i;
	
	CreateUDG(G);
	
//	p = GetVex(G, 3);
//	printf("%s\n", p);

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
//	Display(G);
	
//	DestroyUDG(G);
	
	return 0;
}

int LocateVex(AMLGraph G, VertexType u)
{
	int i;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(strcmp(u, G.adjmulist[i].data) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

void CreateUDG(AMLGraph & G)
{
	int i, j, k;
	int IncInfo;
	VertexType va, vb;
	EBox * p;
	
	printf("请输入无向图的顶点数，边数，是否为带权图(是:1, 否:0)：");
	scanf("%d,%d,%d", &G.vexnum, &G.edgenum, &IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符)：\n", G.vexnum, MAX_NAME);
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%s", G.adjmulist[i].data);
		G.adjmulist[i].firstedge = NULL;
	}
	
	printf("请输入%d条边的两个顶点：\n", G.edgenum);
	for(k = 0; k < G.edgenum; ++k)
	{
		scanf("%s%s%*c", va, vb);
		
		i = LocateVex(G, va);
		j = LocateVex(G, vb);
		
		p = (EBox *)malloc(sizeof(EBox));
		p->mark = unvisited;
		p->ivex = i;
		p->ilink = G.adjmulist[i].firstedge;
		G.adjmulist[i].firstedge = p;
		p->jvex = j;
		p->jlink = G.adjmulist[j].firstedge;
		G.adjmulist[j].firstedge = p;
		
		if(IncInfo)
		{
			p->info = (InfoType *)malloc(sizeof(InfoType));
			printf("请输入该边的权值：");
			scanf("%d", p->info);
		}
		else
		{
			p->info = NULL;
		}
	}
}

void DestroyUDG(AMLGraph & G)
{
	int i;
	
	for(i = G.vexnum - 1; i >= 0; --i)
	{
		DeleteVex(G, G.adjmulist[i].data);
	}
}

VertexType& GetVex(AMLGraph G, int v)
{
	if(v < 0 || v >= G.vexnum)
	{
		exit(-1);
	}
	
	return G.adjmulist[v].data;
}

bool PutVex(AMLGraph & G, VertexType v, VertexType value)
{
	int i;
	
	i = LocateVex(G, v);
	if(i < 0)
	{
		return false;
	}
	
	strcpy(G.adjmulist[i].data, value);
	
	return true;
}

int FirstAdjVex(AMLGraph G, VertexType v)
{
	int i;
	
	i = LocateVex(G, v);
	if(i < 0)
	{
		return -1;
	}
	
	if(G.adjmulist[i].firstedge)
	{
		if(G.adjmulist[i].firstedge->ivex == i)
		{
			return G.adjmulist[i].firstedge->jvex;
		}
		else
		{
			return G.adjmulist[i].firstedge->ivex;
		}
	}
	else
	{
		return -1;
	}
}

int NextAdjVex(AMLGraph G, VertexType v, VertexType w)
{
	int i, j;
	EBox * p;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	{
		return -1;
	}
	
	p = G.adjmulist[i].firstedge;
	while(p)
	{
		if(p->ivex == i && p->jvex != j)
		{
			p = p->ilink;
		}
		else if(p->jvex == i && p->ivex != j)
		{
			p = p->jlink;
		}
		else
		{
			break;
		}
	}
	
	if(p && p->ivex == i && p->jvex == j)
	{
		p = p->ilink;
		if(p && p->ivex == i)
		{
			return p->jvex;
		}
		else if(p && p->jvex == i)
		{
			return p->ivex;
		}
	}
	if(p && p->jvex == i && p->ivex == j)
	{
		p = p->jlink;
		if(p && p->ivex == i)
		{
			return p->jvex;
		}
		else if(p && p->jvex == i)
		{
			return p->ivex;
		}
	}
	
	return -1;
}

bool InsertVex(AMLGraph & G, VertexType v)
{
	if(G.vexnum == MAX_VERTEX_NUM)
	{
		return false;
	}
	if(LocateVex(G, v) >= 0)
	{
		return false;
	}
	
	strcpy(G.adjmulist[G.vexnum].data, v);
	G.adjmulist[G.vexnum].firstedge = NULL;
	G.vexnum++;
	
	return true;
}

//邻接多重表的删除顶点函数功能有误 
bool DeleteVex(AMLGraph & G, VertexType v)
{
	int i, j;
	EBox * p;
	
	i = LocateVex(G, v);
	if(i < 0)
	{
		return false;
	}
	
	for(j = 0; j < G.vexnum; ++j)
	{
		DeleteArc(G, v, G.adjmulist[j].data);
	}
	
	for(j = i + 1; j < G.vexnum; ++j)
	{
		G.adjmulist[j - 1] = G.adjmulist[j];
	}
	
	G.vexnum--;
	
	for(j = i; j < G.vexnum; ++j)
	{
		p = G.adjmulist[j].firstedge;
		while(p)
		{
			if(p->ivex == j + 1)
			{
				p->ivex--;
				p = p->ilink;
			}
			else
			{
				p->jvex--;
				p = p->jlink;
			}
		}
	}
	
	return true;
}

bool InsertArc(AMLGraph & G, VertexType v, VertexType w)
{
	int i, j;
	int IncInfo;
	EBox * p;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	{
		return false;
	}
	
	p = (EBox *)malloc(sizeof(EBox));
	p->mark = unvisited;
	p->ivex = i;
	p->ilink = G.adjmulist[i].firstedge;
	G.adjmulist[i].firstedge = p;
	p->jvex = j;
	p->jlink = G.adjmulist[j].firstedge;
	G.adjmulist[j].firstedge = p;
	
	printf("该边是否有权值(是:1, 否:0)：");
	scanf("%d", &IncInfo);
	
	if(IncInfo)
	{
		p->info = (InfoType *)malloc(sizeof(InfoType));
		printf("请输入该边的权值：");
		scanf("%d", p->info);
	}
	else
	{
		p->info = NULL;
	}
	
	G.edgenum++;
	
	return true;
}

bool DeleteArc(AMLGraph & G, VertexType v, VertexType w)
{
	int i, j;
	EBox * p, * q;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	{
		return false;
	}
	
	p = G.adjmulist[i].firstedge;
	if(p && p->jvex == j)
	{
		G.adjmulist[i].firstedge = p->ilink;
	}
	else if(p && p->ivex == j)
	{
		G.adjmulist[i].firstedge = p->jlink;
	}
	else
	{
		while(p)
		{
			if(p->ivex == i && p->jvex != j)
			{
				q = p;
				p = p->ilink;
			}
			else if(p->jvex == i && p->ivex != j)
			{
				q = p;
				p = p->jlink;
			}
			else
			{
				break;
			}
		}
		
		if(!p)
		{
			return false;
		}
		
		if(p->ivex == i && p->jvex == j)
		{
			if(q->ivex == i)
			{
				q->ilink = p->ilink;
			}
			else
			{
				q->jlink = p->ilink;
			}
		}
		else if(p->jvex == i && p->ivex == j)
		{
			if(q->ivex == i)
			{
				q->ilink = p->jlink;
			}
			else
			{
				q->jlink = p->jlink;
			}
		}
	}
	
	p = G.adjmulist[j].firstedge;
	if(p && p->jvex == i)
	{
		G.adjmulist[j].firstedge = p->ilink;
	}
	else if(p && p->ivex == i)
	{
		G.adjmulist[j].firstedge = p->jlink;
	}
	else
	{
		while(p)
		{
			if(p->ivex == j && p->jvex != i)
			{
				q = p;
				p = p->ilink;
			}
			else if(p->jvex == j && p->ivex != i)
			{
				q = p;
				p = p->jlink;
			}
			else
			{
				break;
			}
		}
		
		if(!p)
		{
			return false;
		}
		
		if(p->ivex == j && p->jvex == i)
		{
			if(q->ivex == j)
			{
				q->ilink = p->ilink;
			}
			else
			{
				q->jlink = p->ilink;
			}
		}
		else if(p->jvex == j && p->ivex == i)
		{
			if(q->ivex == j)
			{
				q->ilink = p->jlink;
			}
			else
			{
				q->jlink = p->jlink;
			}
		}
	}
	
	if(p->info)
	{
		free(p->info);
	}
	free(p);
	
	G.edgenum--;
	
	return true;
}

bool visite[MAX_VERTEX_NUM];
void(*VisitFunc)(VertexType);

void DFS(AMLGraph G, int v)
{
	int j;
	EBox * p;
	
	visite[v] = true;
	VisitFunc(G.adjmulist[v].data);
	
	p = G.adjmulist[v].firstedge;
	while(p)
	{
		j = p->ivex == v ? p->jvex : p->ivex;
		if(!visite[j])
		{
			DFS(G, j);
		}
		p = p->ivex == v ? p->ilink : p->jlink;
	}
}

void DFSTraverse(AMLGraph G, void(*Visit)(VertexType))
{
	int v;
	
	VisitFunc = Visit;
	
	for(v = 0; v < G.vexnum; ++v)
	{
		visite[v] = false;
	}
	
	for(v = 0; v < G.vexnum; ++v)
	{
		if(!visite[v])
		{
			DFS(G, v);
		}
	}
	
	printf("\n");
}

# include "AMLGraphQueue.cpp"

void BFSTraverse(AMLGraph G, void(*Visit)(VertexType))
{
	int v, u, w;
	Queue q;
	
	for(v = 0; v < G.vexnum; ++v)
	{
		visite[v] = false;
	}
	
	initQueue(&q);
	
	for(v = 0; v < G.vexnum; ++v)
	{
		if(!visite[v])
		{
			visite[v] = true;
			Visit(G.adjmulist[v].data);
			
			enqueue(&q, v);
			while(!emptyQueue(&q))
			{
				dequeue(&q, &u);
				
				for(w = FirstAdjVex(G, G.adjmulist[u].data); w >= 0; w = NextAdjVex(G, G.adjmulist[u].data, G.adjmulist[w].data))
				{
					if(!visite[w])
					{
						visite[w] = true;
						Visit(G.adjmulist[w].data);
						enqueue(&q, w);
					}
				}
			}
		}
	}
	
	printf("\n");
	
	destroyQueue(&q);
}

void MarkUnvizited(AMLGraph G)
{
	int i;
	EBox * p;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		p = G.adjmulist[i].firstedge;
		while(p)
		{
			p->mark = unvisited;
			if(p->ivex == i)
			{
				p = p->ilink;
			}
			else
			{
				p = p->jlink;
			}
		}
	}
}

void Display(AMLGraph G)
{
	int i;
	EBox * p;
	
	MarkUnvizited(G);
	
	printf("%d个顶点：\n", G.vexnum);
	for(i = 0; i < G.vexnum; ++i)
	{
		printf("%s ", G.adjmulist[i].data);
	}
	
	printf("\n%d条边：\n", G.edgenum);
	for(i = 0; i < G.vexnum; ++i)
	{
		p = G.adjmulist[i].firstedge;
		while(p)
		{
			if(p->ivex == i)
			{
				if(!p->mark)
				{
					printf("%s-%s ", G.adjmulist[i].data, G.adjmulist[p->jvex].data);
					p->mark = visited;
					if(p->info)
					{
						printf("权值：%d ", *(p->info));
					}
				}
				
				p = p->ilink;
			}
			else
			{
				if(!p->mark)
				{
					printf("%s-%s ", G.adjmulist[p->ivex].data, G.adjmulist[i].data);
					p->mark = visited;
					if(p->info)
					{
						printf("权值：%d ", *(p->info));
					}
				}
				
				p = p->jlink;
			}
		}
		printf("\n");
	}
}

