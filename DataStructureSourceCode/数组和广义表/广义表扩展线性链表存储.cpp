# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef char AtomType;

typedef enum ElemTag
{
	ATOM, LIST
} ElemTag;

typedef struct GLNode
{
	ElemTag tag;
	union
	{
		AtomType atom;
		struct GLNode * hp;
	};
	struct GLNode * tp;
} GLNode, * GList;

int main(void)
{
	//广义表的扩展线性链表存储的数据结构代码编写这里不再进行（因为懒） 
	
	return 0;
}

