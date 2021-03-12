# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

# define MAX_NAME 3
# define MAX_VERTEX_NUM 20

typedef int InfoType;
typedef char VertexType[MAX_NAME];

typedef struct ArcBox1
{
	int tailvex, headvex;
	InfoType * info;
	struct ArcBox1 * hlink, * tlink;
} ArcBox1;

typedef struct ElemType
{
	int tailvex, headvex;
	InfoType * info;
	ArcBox1 * hlink;
} ElemType;

typedef struct ArcBox
{
	ElemType e;
	struct ArcBox * tlink;
} ArcBox;

typedef struct VexNode
{
	VertexType data;
	ArcBox1 * firstin;
	ArcBox * firstout;
} VexNode, OList[MAX_VERTEX_NUM];

typedef struct OLGraph
{
	OList xlist;
	int vexnum, arcnum;
} OLGraph;

# define LNode ArcBox
# define next tlink
typedef ArcBox * LinkList;

int LocateVex(OLGraph, VertexType);
void CreateDG(OLGraph &);
void DestroyDG(OLGraph &);
VertexType& GetVex(OLGraph, int);
bool PutVex(OLGraph &, VertexType, VertexType);
int FirstAdjVex(OLGraph, VertexType);
int NextAdjVex(OLGraph, VertexType, VertexType);
void InsertVex(OLGraph &, VertexType);
bool equal(ElemType, ElemType);
bool DeleteVex(OLGraph &, VertexType);
bool InsertArc(OLGraph &, VertexType, VertexType);
bool DeleteArc(OLGraph &, VertexType, VertexType);
void DFS(OLGraph, int);
void DFSTraverse(OLGraph, void(*Visit)(VertexType));
void BFSTraverse(OLGraph, void(*Visit)(VertexType));
void Display(OLGraph);

void visit(VertexType s)
{
	printf("%s ", s);
}

int main(void)
{
	OLGraph G;
	VertexType v = {'A'};
	VertexType w = {'C'};
	VertexType u = {'Z'};
	VertexType x = {'H'};
	char * p;
	int i;
	
	CreateDG(G);
	
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
	
	DestroyDG(G);
	
	return 0;
}

# include "OLGraphLinkList.cpp"

int LocateVex(OLGraph G, VertexType u)
{
	int i;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(strcmp(u, G.xlist[i].data) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

void CreateDG(OLGraph & G)
{
	int i, j, k;
	int IncInfo;
	ArcBox * p;
	VertexType va, vb;
	
	printf("请输入有向图的顶点数，弧数，是否为带权图(是:1, 否:0)：");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符)：\n", G.vexnum, MAX_NAME);
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%s", G.xlist[i].data);
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
	}
	
	printf("请输入%d条弧的弧尾和弧头：\n", G.arcnum);
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%s%s", va, vb);
		
		i = LocateVex(G, va);
		j = LocateVex(G, vb);
		
		p = (ArcBox *)malloc(sizeof(ArcBox));
		p->e.tailvex = i;
		p->e.headvex = j;
		p->e.hlink = G.xlist[j].firstin;
		p->tlink = G.xlist[i].firstout;
		G.xlist[j].firstin = (ArcBox1 *)p;
		G.xlist[i].firstout = p;
		
		if(IncInfo)
		{
			p->e.info = (InfoType *)malloc(sizeof(InfoType));
			printf("请输入该弧的权值：");
			scanf("%d", p->e.info);
		}
		else
		{
			p->e.info = NULL;
		}
	}
}

void DestroyDG(OLGraph & G)
{
	int i;
	ElemType e;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		while(G.xlist[i].firstout)
		{
			ListDelete(G.xlist[i].firstout, 1, e);
			if(e.info)
			{
				free(e.info);
			}
		}
	}
	
	G.vexnum = 0;
	G.arcnum = 0;
}

VertexType& GetVex(OLGraph G, int v)
{
	if(v < 0 || v >= G.vexnum)
	{
		exit(-1);
	}
	
	return G.xlist[v].data;
}

bool PutVex(OLGraph & G, VertexType v, VertexType value)
{
	int i;
	
	i = LocateVex(G, v);
	if(i < 0)
	{
		return false;
	}
	
	strcpy(G.xlist[i].data, value);
	
	return true;
}

int FirstAdjVex(OLGraph G, VertexType v)
{
	int i;
	ArcBox * p;
	
	i = LocateVex(G, v);
	
	p = G.xlist[i].firstout;
	
	if(p)
	{
		return p->e.headvex;
	}
	else
	{
		return -1;
	}
}

int NextAdjVex(OLGraph G, VertexType v, VertexType w)
{
	int i, j;
	ArcBox * p;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	
	p = G.xlist[i].firstout;
	
	while(p && p->e.headvex != j)
	{
		p = p->tlink;
	}
	
	if(p)
	{
		p = p->tlink;
	}
	if(p)
	{
		return p->e.headvex;
	}
	else
	{
		return -1;
	}
}

void InsertVex(OLGraph & G, VertexType v)
{
	strcpy(G.xlist[G.vexnum].data, v);
	G.xlist[G.vexnum].firstin = NULL;
	G.xlist[G.vexnum].firstout = NULL;
	G.vexnum++;
}

bool equal(ElemType a, ElemType b)
{
	if(a.headvex == b.headvex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DeleteVex(OLGraph & G, VertexType v)
{
	int i, j, k;
	ElemType e1, e2;
	ArcBox * p;
	ArcBox1 * p1, * p2;
	
	k = LocateVex(G, v);
	if(k < 0)
	{
		return false;
	}
	
	e1.headvex = k;
	
	for(j = 0; j < G.vexnum; ++j)
	{
		i = LocateElem(G.xlist[j].firstout, e1, equal);
		
		if(i)
		{
			ListDelete(G.xlist[j].firstout, i, e2);
			G.arcnum--;
			if(e2.info)
			{
				free(e2.info);
			}
		}
	}
	
	for(j = 0; j < G.vexnum; ++j)
	{
		p1 = G.xlist[j].firstin;
		
		while(p1 && p1->tailvex != k)
		{
			p2 = p1;
			p1 = p1->hlink;
		}
		
		if(p1)
		{
			if(p1 == G.xlist[j].firstin)
			{
				G.xlist[j].firstin = p1->hlink;
			}
			else
			{
				p2->hlink = p1->hlink;
			}
			
			if(p1->info)
			{
				free(p1->info);
			}
			
			free(p1);
			
			G.arcnum--;
		}
	}
	
	for(j = k + 1; j < G.vexnum; ++j)
	{
		G.xlist[j - 1] = G.xlist[j];
	}
	
	G.vexnum--;
	
	for(j = 0; j < G.vexnum; ++j)
	{
		p = G.xlist[j].firstout;
		
		while(p)
		{
			if(p->e.tailvex > k)
			{
				p->e.tailvex--;
			}
			if(p->e.headvex > k)
			{
				p->e.headvex--;
			}
			p = p->tlink;
		}
	}
	
	return true;
}

bool InsertArc(OLGraph & G, VertexType v, VertexType w)
{
	int i, j;
	int IncInfo;
	ArcBox * p;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	{
		return false;
	}
	
	p = (ArcBox *)malloc(sizeof(ArcBox));
	p->e.tailvex = i;
	p->e.headvex = j;
	p->e.hlink = G.xlist[j].firstin;
	p->tlink = G.xlist[i].firstout;
	G.xlist[j].firstin = (ArcBox1 *)p;
	G.xlist[i].firstout = p;
	
	G.arcnum++;
	
	printf("要插入的弧是否带权(是:1, 否:0)：");
	scanf("%d", &IncInfo);
	if(IncInfo)
	{
		p->e.info = (InfoType *)malloc(sizeof(InfoType));
		printf("请输入该弧的权值：");
		scanf("%d", p->e.info);
	}
	else
	{
		p->e.info = NULL;
	}
	
	return true;
}

bool DeleteArc(OLGraph & G, VertexType v, VertexType w)
{
	int i, j, k;
	ElemType e;
	ArcBox1 * p1, * p2;
	
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if(i < 0 || j < 0)
	{
		return false;
	}
	
	p1 = G.xlist[j].firstin;
	
	while(p1 && p1->tailvex != i)
	{
		p2 = p1;
		p1 = p1->hlink;
	}
	
	if(p1 == G.xlist[j].firstin)
	{
		G.xlist[j].firstin = p1->hlink;
	}
	else
	{
		p2->hlink = p1->hlink;
	}
	
	e.headvex = j;
	
	k = LocateElem(G.xlist[i].firstout, e, equal);
	
	ListDelete(G.xlist[i].firstout, k, e);
	if(e.info)
	{
		free(e.info);
	}
	
	G.arcnum--;
	
	return true;
}

bool visited[MAX_VERTEX_NUM];
void(*VisitFunc)(VertexType);

void DFS(OLGraph G, int v)
{
	ArcBox * p;
	
	visited[v] = true;
	VisitFunc(G.xlist[v].data);
	
	p = G.xlist[v].firstout;
	while(p && visited[p->e.headvex])
	{
		p = p->tlink;
	}
	if(p && !visited[p->e.headvex])
	{
		DFS(G, p->e.headvex);
	}
}

void DFSTraverse(OLGraph G, void(*Visit)(VertexType))
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

# include "OLGraphQueue.cpp"

void BFSTraverse(OLGraph G, void(*Visit)(VertexType))
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
			Visit(G.xlist[v].data);
			
			enqueue(&q, v);
			while(!emptyQueue(&q))
			{
				dequeue(&q, &u);
				
				for(w = FirstAdjVex(G, G.xlist[u].data); w >= 0; w = NextAdjVex(G, G.xlist[u].data, G.xlist[w].data))
				{
					if(!visited[w])
					{
						visited[w] = true;
						Visit(G.xlist[w].data);
						enqueue(&q, w);
					}
				}
			}
		}
	}
	
	printf("\n");
	
	destroyQueue(&q);
}

void Display(OLGraph G)
{
	int i;
	ArcBox * p;
	
	printf("共%d个顶点：", G.vexnum);
	for(i = 0; i < G.vexnum; ++i)
	{
		printf("%s ", G.xlist[i].data);
	}
	
	printf("\n%d条弧：\n", G.arcnum);
	for(i = 0; i < G.vexnum; ++i)
	{
		p = G.xlist[i].firstout;
		while(p)
		{
			printf("%s->%s ", G.xlist[i].data, G.xlist[p->e.headvex].data);
			if(p->e.info)
			{
				printf("权值：%d ", *(p->e.info));
			}
			p = p->tlink;
		}
		printf("\n");
	}
}

