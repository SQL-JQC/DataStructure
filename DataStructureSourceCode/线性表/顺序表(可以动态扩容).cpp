# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

# define length 10  //初始化数组元素的个数为10个 

typedef struct ArrayList
{
	int * pBase;  //数组本身，保存数组第一个元素的地址 
	int len;  //数组所允许存放的最大数量的元素的个数 
	int cnt;  //数组中存放的有效元素的个数 
	const int increment = 5;  //每次增长的数组元素的个数设为5个 
} array, * pArray;

void init_array(pArray);
bool append_array(pArray, int);
bool insert_array(pArray, int, int);
bool delete_array(pArray, int, int *);
bool get(pArray, int, int *);
int find(pArray, int);
bool is_empty(pArray);
bool is_full(pArray);
void sort_array(pArray);
void show_array(pArray);
void inversion_array(pArray);
void destroy_array(pArray);

int main(void)
{
	array arr;
	int delete_value;
	int get_value;
	
	init_array(&arr);  //初始化数组 
	show_array(&arr);
	
	append_array(&arr, 1);  //追加 
	append_array(&arr, 2);
	append_array(&arr, 3);
	append_array(&arr, 4);
	append_array(&arr, 5);
	append_array(&arr, 6);
	append_array(&arr, 7);
	append_array(&arr, 8);
	append_array(&arr, 9);
	append_array(&arr, 10);  //此时数组长度还为初始化时的10，(# define length 10) 
	append_array(&arr, 11);  //此时数组的长度由于已满，所以需要扩充长度5(increment = 5)，从而数组总长度变为15  
	append_array(&arr, 12);
	append_array(&arr, 13);
	show_array(&arr);
	
	insert_array(&arr, 2, 100);  //插入 
	show_array(&arr);
	
	if( delete_array(&arr, 5, &delete_value) )  //删除 
	{
		printf("\n删除成功，删除的值为：%d\n", delete_value);
	}
	else
	{
		printf("\n删除失败！\n");
	}
	show_array(&arr);
	
	get(&arr, 2, &get_value); 
	printf("\n得到数组索引为2的元素的值为：%d\n", get_value);
	
	int index = find(&arr, 3);
	printf("\n查找出3这个值在数组中的索引为：%d\n", index); 
	
	printf("\n对数组升序排序之后的结果是：");
	sort_array(&arr);
	show_array(&arr);
	
	printf("\n对数组倒置之后的结果是：");
	inversion_array(&arr);
	show_array(&arr);
	
	destroy_array(&arr);  //在测试所有的操作完成后 释放掉 结构体中的pBase所指向的动态分配的内存单元 
	
	return 0;
}

void init_array(pArray pArr)
{
	pArr->pBase = (int *)malloc(sizeof(int)*length);
	if(NULL == pArr->pBase)
	{
		printf("动态内存分配失败！");
		exit(-1);
	}
	else
	{
		pArr->len = length;
		pArr->cnt = 0;
	}
	
	return;
}

bool is_empty(pArray pArr)
{
	if(0 == pArr->cnt)
		return true;
	else
		return false;
}

bool is_full(pArray pArr)
{
	if(pArr->len == pArr->cnt)
	{
		int * pNewBase = (int *)realloc(pArr->pBase, sizeof(int)*(pArr->len + pArr->increment));
		if(NULL == pNewBase)
		{
			printf("重新分配动态内存失败！");
			exit(-1);	
		}
		
		pArr->pBase = pNewBase;
		pArr->len += pArr->increment;
		
		return false;
	}
	else
	{
		return false;
	}
}

void show_array(pArray pArr)
{
	if( is_empty(pArr) )
	{
		printf("数组为空，无法显示！\n");
	}
	else
	{
		printf("\n");
		for(int i=0; i<pArr->cnt; ++i)
		{
			printf("%d ", pArr->pBase[i]);
		}
		printf("\n");
	}
	
	return;
}

bool append_array(pArray pArr, int val)
{
	if( is_full(pArr) )
		return false;
	
	pArr->pBase[pArr->cnt] = val;
	pArr->cnt++;
	
	return true;
}

bool insert_array(pArray pArr, int pos, int val)
{
	int i;
	
	if( is_full(pArr) )
		return false;
	
	if(pos<1 || pos>pArr->cnt+1)
		return false;
	
	for(i=pArr->cnt-1; i>=pos-1; --i)
	{
		pArr->pBase[i+1] = pArr->pBase[i];
	}
	pArr->pBase[pos-1] = val;
	
	pArr->cnt++;
	
	return true;
}

bool delete_array(pArray pArr, int pos, int * pVal)
{
	int i;
	
	if( is_empty(pArr) )
		return false;
		
	if(pos<1 || pos>pArr->cnt)
		return false;
		
	*pVal = pArr->pBase[pos-1];
	
	for(i=pos; i<pArr->cnt; ++i)
	{
		pArr->pBase[i-1] = pArr->pBase[i];
	}
	
	pArr->cnt--;
	
	return true;
}

bool get(pArray pArr, int index, int * pVal)
{
	if(index<0 || index>pArr->cnt-1)
		return false;
		
	*pVal = pArr->pBase[index];
	
	return true;
}

int find(pArray pArr, int val)
{
	int i;
	int index;
	
	for(i=0; i<pArr->cnt; ++i)
	{
		if(val == pArr->pBase[i])
		{
			index = i;
			break;
		}
		if(i == pArr->cnt-1)
		{
			return -1;
		}
	}
	
	return index;
}

void sort_array(pArray pArr)
{
	int t;
	int i;
	int j;
	
	for(i=0; i<pArr->cnt-1; ++i)
	{
		for(j=0; j<pArr->cnt-1-i; ++j)
		{
			if(pArr->pBase[j] > pArr->pBase[j+1])
			{
				t = pArr->pBase[j];
				pArr->pBase[j] = pArr->pBase[j+1];
				pArr->pBase[j+1] = t;
			}
		}
	}
	
	return;
}

void inversion_array(pArray pArr)
{
	int i = 0;
	int j = pArr->cnt-1;
	int t;
	
	while(i < j)
	{
		t = pArr->pBase[i];
		pArr->pBase[i] = pArr->pBase[j];
		pArr->pBase[j] = t;
		
		i++;
		j--;
	}
	
	return;
}

void destroy_array(pArray pArr)
{
	free(pArr->pBase);
	printf("ArrayList动态数组释放成功！\n");
	
	return;
}
