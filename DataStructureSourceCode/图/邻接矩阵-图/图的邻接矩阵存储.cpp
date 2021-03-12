# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

# define MAX_NAME 5
# define MAX_INFO 20
# define INFINITY INT_MAX
# define MAX_VERTEX_NUM 26

typedef int VRType;
typedef char InfoType;
typedef char VertexType[MAX_NAME];

typedef enum GraphKind
{
	DG, DN, UDG, UDN
} GraphKind;

typedef struct ArcCell
{
	VRType adj;
	InfoType * info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph
{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;
	GraphKind kind;
} MGraph;

int LocateVex(MGraph, VertexType);
void CreateDG(MGraph &);
void CreateDN(MGraph &);
void CreateUDG(MGraph &);
void CreateUDN(MGraph &);
void CreateGraph(MGraph &);
void DestroyGraph(MGraph &);
VertexType& GetVex(MGraph, int);
bool PutVex(MGraph &, VertexType, VertexType);
int FirstAdjVex(MGraph, VertexType);
int NextAdjVex(MGraph, VertexType, VertexType);
void InsertVex(MGraph &, VertexType);
bool DeleteVex(MGraph &, VertexType);
bool InsertArc(MGraph &, VertexType, VertexType);
bool DeleteArc(MGraph &, VertexType, VertexType);
void DFS(MGraph, int);
void DFSTraverse(MGraph, void(*Visit)(VertexType));
void BFSTraverse(MGraph, void(*Visit)(VertexType));
void Display(MGraph);

void visit(VertexType s)
{
	printf("%s ", s);
}

int main(void)
{
	MGraph G;
	VertexType v = {'A'};
	VertexType w = {'C'};
	VertexType u = {'Z'};
	VertexType x = {'H'};
	char * p;
	int i;
	
	CreateGraph(G);
	
//	PutVex(G, v, w);
//	p = GetVex(G, 0);
//	printf("%s\n", p);
	
//	i = FirstAdjVex(G, v);
//	printf("%d\n", i);
//	i = NextAdjVex(G, v, w);
//	printf("%d\n", i);
	
//	Display(G);
//	InsertVex(G, u);
//	Display(G);

//	Display(G);
//	DeleteVex(G, v);
//	Display(G);

//	Display(G);
//	InsertArc(G, w, x);
//	Display(G);
	
//	Display(G);
//	DeleteArc(G, w, x);
//	Display(G);
	
//	DFSTraverse(G, visit);
//	BFSTraverse(G, visit);
//	Display(G);
	
	DestroyGraph(G);
	
	return 0;
}

int LocateVex(MGraph G, VertexType u)
{
	int i;
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(strcmp(u, G.vexs[i]) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

void CreateDG(MGraph & G)
{
	int i, j, k, l, IncInfo;
	char s[MAX_INFO];
	VertexType va, vb;
	
	printf("请输入有向图G的顶点数、弧数、弧是否含其他信息(是:1, 否:0)：");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符)：\n", G.vexnum, MAX_NAME);
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%s", G.vexs[i]);
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}
	
	printf("请输入%d条弧的弧尾 弧头(以空格作为间隔)：\n", G.arcnum);
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%s%s%*c", va, vb);
		
		i = LocateVex(G, va);
		j = LocateVex(G, vb);
		G.arcs[i][j].adj = 1;
		
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(<%d个字符)：", MAX_INFO);
			gets(s);
			
			l = strlen(s);
			if(l)
			{
				G.arcs[i][j].info = (char *)malloc(sizeof(char) * (l + 1));
				strcpy(G.arcs[i][j].info, s);
			}
		}
	}
	
	G.kind = DG;
}

void CreateDN(MGraph & G)
{
	int i, j, k, w, IncInfo;
	char s[MAX_INFO];
	VertexType va, vb;
	
	printf("请输入有向网G的顶点数、弧数、弧是否含其他信息(是:1, 否:0)：");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符)：\n", G.vexnum, MAX_NAME);
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%s", G.vexs[i]);
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	
	printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔)：\n", G.arcnum);
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%s%s%d%*c", va, vb, &w);
		
		i = LocateVex(G, va);
		j = LocateVex(G, vb);
		G.arcs[i][j].adj = w;
		
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(<%d个字符)：", MAX_INFO);
			gets(s);
			
			w = strlen(s);
			if(w)
			{
				G.arcs[i][j].info = (char *)malloc(sizeof(char) * (w + 1));
				strcpy(G.arcs[i][j].info, s);
			}
		}
	}
	
	G.kind = DN;
}

void CreateUDG(MGraph & G)
{
	int i, j, k, l, IncInfo;
	char s[MAX_INFO];
	VertexType va, vb;
	
	printf("请输入无向图G的顶点数、边数、边是否含其他信息(是:1, 否:0)：");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符)：\n", G.vexnum, MAX_NAME);
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%s", G.vexs[i]);
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}
	
	printf("请输入%d条边的顶点1 顶点2(以空格作为间隔)：\n", G.arcnum);
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%s%s%*c", va, vb);
		
		i = LocateVex(G, va);
		j = LocateVex(G, vb);
		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;
		
		if(IncInfo)
		{
			printf("请输入该边的相关信息(<%d个字符)：", MAX_INFO);
			gets(s);
			
			l = strlen(s);
			if(l)
			{
				G.arcs[i][j].info = G.arcs[j][i].info = (char *)malloc(sizeof(char) * (l + 1));
				strcpy(G.arcs[i][j].info, s);
			}
		}
	}
	
	G.kind = UDG;
}

void CreateUDN(MGraph & G)
{
	int i, j, k, w, IncInfo;
	char s[MAX_INFO];
	VertexType va, vb;
	
	printf("请输入无向网G的顶点数、边数、边是否含其他信息(是:1, 否:0)：");
	scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符)：\n", G.vexnum, MAX_NAME);
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%s", G.vexs[i]);
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	
	printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔)：\n", G.arcnum);
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%s%s%d%*c", va, vb, &w);
		
		i = LocateVex(G, va);
		j = LocateVex(G, vb);
		G.arcs[i][j].adj = G.arcs[j][i].adj = w;
		
		if(IncInfo)
		{
			printf("请输入该边的相关信息(<%d个字符)：", MAX_INFO);
			gets(s);
			
			w = strlen(s);
			if(w)
			{
				G.arcs[i][j].info = G.arcs[j][i].info = (char *)malloc(sizeof(char) * (w + 1));
				strcpy(G.arcs[i][j].info, s);
			}
		}
	}
	
	G.kind = UDN;
}

void CreateGraph(MGraph & G)
{
	printf("请输入图G的类型(有向图:0, 有向网:1, 无向图:2, 无向网:3)：");
	scanf("%d", &G.kind);
	
	switch(G.kind)
	{
		case DG:
			CreateDG(G);
			break;
		case DN:
			CreateDN(G);
			break;
		case UDG:
			CreateUDG(G);
			break;
		case UDN:
			CreateUDN(G);
			break;
	}
}

void DestroyGraph(MGraph & G)
{
	int i, j;
	int k = 0;
	
	if(G.kind%2)
	{
		k = INFINITY;
	}
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.kind < 2)
		{
			for(j = 0; j < G.vexnum; ++j)
			{
				if(G.arcs[i][j].adj != k)
				{
					if(G.arcs[i][j].info)
					{
						free(G.arcs[i][j].info);
						G.arcs[i][j].info = NULL;
					}
				}
			}
		}
		else
		{
			for(j = i+1; j < G.vexnum; ++j)
			{
				if(G.arcs[i][j].adj != k)
				{
					if(G.arcs[i][j].info)
					{
						free(G.arcs[i][j].info);
						G.arcs[i][j].info = G.arcs[j][i].info = NULL;
					}
				}
			}
		}
	}
	
	G.vexnum = 0;
	G.arcnum = 0;
}

VertexType& GetVex(MGraph G, int v)
{
	if(v >= G.vexnum || v < 0)
	{
		exit(-1);
	}
	
	return G.vexs[v];
}

bool PutVex(MGraph & G, VertexType v, VertexType value)
{
	int k;
	
	k = LocateVex(G, v);
	if(k < 0)
	{
		return false;
	}
	
	strcpy(G.vexs[k], value);
	
	return true;
}

int FirstAdjVex(MGraph G, VertexType v)
{
	int i, j = 0;
	int k;
	
	k = LocateVex(G, v);
	
	if(G.kind%2)
	{
		j = INFINITY;
	}
	
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.arcs[k][i].adj != j)
		{
			return i;
		}
	}
	
	return -1;
}

int NextAdjVex(MGraph G, VertexType v, VertexType w)
{
	int i, j = 0;
	int k1, k2;
	
	k1 = LocateVex(G, v);
	k2 = LocateVex(G, w);
	
	if(G.kind%2)
	{
		j = INFINITY;
	}
	
	for(i = k2+1; i < G.vexnum; ++i)
	{
		if(G.arcs[k1][i].adj != j)
		{
			return i;
		}
	}
	
	return -1;
}

void InsertVex(MGraph & G, VertexType v)
{
	int i, j = 0;
	
	if(G.kind%2)
	{
		j = INFINITY;
	}
	
	strcpy(G.vexs[G.vexnum], v);
	
	for(i = 0; i <= G.vexnum; ++i)
	{
		G.arcs[G.vexnum][i].adj = G.arcs[i][G.vexnum].adj = j;
		G.arcs[G.vexnum][i].info = G.arcs[i][G.vexnum].info = NULL;
	}
	
	G.vexnum++;
}

bool DeleteVex(MGraph & G, VertexType v)
{
	int i, j, k;
	VRType m = 0;
	
	if(G.kind%2)
	{
		m = INFINITY;
	}
	
	k = LocateVex(G, v);
	if(k < 0)
	{
		return false;
	}
	
	for(j = 0; j < G.vexnum; ++j)
	{
		if(G.arcs[j][k].adj != m)
		{
			if(G.arcs[j][k].info)
			{
				free(G.arcs[j][k].info);
			}
			
			G.arcnum--;
		}
	}
	if(G.kind < 2)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			if(G.arcs[k][j].adj != m)
			{
				if(G.arcs[k][j].info)
				{
					free(G.arcs[k][j].info);
				}
				
				G.arcnum--;
			}
		}
	}
	
	for(j = k+1; j < G.vexnum; ++j)
	{
		strcpy(G.vexs[j-1], G.vexs[j]);
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = k+1; j < G.vexnum; ++j)
		{
			G.arcs[i][j-1] = G.arcs[i][j];
		}
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = k+1; j < G.vexnum; ++j)
		{
			G.arcs[j-1][i] = G.arcs[j][i];
		}
	}
	
	G.vexnum--;
	
	return true;
}

bool InsertArc(MGraph & G, VertexType v, VertexType w)
{
	int i, l;
	int v1, w1;
	char s[MAX_INFO];
	
	v1 = LocateVex(G, v);
	w1 = LocateVex(G, w);
	if(v1 < 0 || w1 < 0)
	{
		return false;
	}
	
	G.arcnum++;
	
	if(G.kind%2)
	{
		printf("请输入此弧或边的权值：");
		scanf("%d", &G.arcs[v1][w1].adj);
	}
	else
	{
		G.arcs[v1][w1].adj = 1;
	}
	
	printf("是否有该弧或边的相关信息(有:1, 无:0)：");
	scanf("%d%*c", &i);
	if(i)
	{
		printf("请输入该弧或边的相关信息(<%d个字符)：", MAX_INFO);
		gets(s);
		
		l = strlen(s);
		if(l)
		{
			G.arcs[v1][w1].info = (char *)malloc(sizeof(char) * (l + 1));
			strcpy(G.arcs[v1][w1].info, s);
		}
	}
	
	if(G.kind > 1)
	{
		G.arcs[w1][v1].adj = G.arcs[v1][w1].adj;
		G.arcs[w1][v1].info = G.arcs[v1][w1].info;
	}
	
	return true;
}

bool DeleteArc(MGraph & G, VertexType v, VertexType w)
{
	int j = 0;
	int v1, w1;
	
	if(G.kind%2)
	{
		j = INFINITY;
	}
	
	v1 = LocateVex(G, v);
	w1 = LocateVex(G, w);
	if(v1 < 0 || w1 < 0)
	{
		return false;
	}
	
	G.arcs[v1][w1].adj = j;
	if(G.arcs[v1][w1].info)
	{
		free(G.arcs[v1][w1].info);
		G.arcs[v1][w1].info = NULL;
	}
	
	if(G.kind > 1)
	{
		G.arcs[w1][v1].adj = j;
		G.arcs[w1][v1].info = NULL;
	}
	
	G.arcnum--;
	
	return true;
}

bool visited[MAX_VERTEX_NUM];
void(*VisitFunc)(VertexType);

void DFS(MGraph G, int v)
{
	int w;
	
	visited[v] = true;
	VisitFunc(G.vexs[v]);
	
	for(w = FirstAdjVex(G, G.vexs[v]); w >= 0; w = NextAdjVex(G, G.vexs[v], G.vexs[w]))
	{
		if(!visited[w])
		{
			DFS(G, w);
		}
	}
}

void DFSTraverse(MGraph G, void(*Visit)(VertexType))
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

# include "MGraphQueue.cpp"

void BFSTraverse(MGraph G, void(*Visit)(VertexType))
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
			Visit(G.vexs[v]);
			
			enqueue(&q, v);
			while(!emptyQueue(&q))
			{
				dequeue(&q, &u);
				for(w = FirstAdjVex(G, G.vexs[u]); w >= 0; w = NextAdjVex(G, G.vexs[u], G.vexs[w]))
				{
					if(!visited[w])
					{
						visited[w] = true;
						Visit(G.vexs[w]);
						enqueue(&q, w);
					}
				}
			}
		}
	}
	
	printf("\n");
	
	destroyQueue(&q);
}

void Display(MGraph G)
{
	int i, j;
	char s[7];
	
	switch(G.kind)
	{
		case DG:
			strcpy(s, "有向图");
			break;
		case DN:
			strcpy(s, "有向网");
			break;
		case UDG:
			strcpy(s, "无向图");
			break;
		case UDN:
			strcpy(s, "无向网");
			break;
	}
	
	printf("%d个顶点%d条弧或边的%s。顶点依次是：", G.vexnum, G.arcnum, s);
	for(i = 0; i < G.vexnum; ++i)
	{
		printf("%s ", G.vexs[i]);
	}
	
	printf("\nG.arcs.adj:\n");
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			printf("%11d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
	
	printf("\nG.arcs.info:\n");
	printf("顶点1(弧尾) 顶点2(弧头) 该弧或边的信息：\n");
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.kind < 2)
		{
			for(j = 0; j < G.vexnum; ++j)
			{
				if(G.arcs[i][j].info)
				{
					printf("%5s %11s     %s\n", G.vexs[i], G.vexs[j], G.arcs[i][j].info);
				}
			}
		}
		else
		{
			for(j = i+1; j < G.vexnum; ++j)
			{
				if(G.arcs[i][j].info)
				{
					printf("%5s %11s     %s\n", G.vexs[i], G.vexs[j], G.arcs[i][j].info);
				}
			}
		}
	}
}

