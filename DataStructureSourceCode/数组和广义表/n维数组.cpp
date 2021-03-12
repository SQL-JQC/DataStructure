# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <stdarg.h>

# define MAX_ARRAY_DIM 8
# define ElementType int

typedef struct Array
{
	ElementType * base;
	int dim;
	int * bounds;
	int * constants;
} Array;

void InitArray(Array *, int, ...);
void DestroyArray(Array *);
void Value(Array *, int *, ...);
void Assign(Array *, int, ...);
bool Locate(Array *, va_list, int *);

int main(void)
{
	Array array;
	InitArray(&array, 3, 3, 4, 5);
	
	int i, j, k;
	for(i = 0; i < 3; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			for(k = 0; k < 5; ++k)
			{
				Assign(&array, i + j + k, i, j, k);
			}
		}
	}
	
	int l, m, n;
	for(l = 0; l < 3; ++l)
	{
		for(m = 0; m < 4; ++m)
		{
			for(n = 0; n < 5; ++n)
			{
				int tmp = 1;
				Value(&array, &tmp, l, m, n);
				printf("%5d", tmp);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
	
	DestroyArray(&array);
	
	return 0;
}

void InitArray(Array * array, int dim, ...)
{
	int i, j;
	
	if(dim < 1 || dim > MAX_ARRAY_DIM)
	{
		return;
	}
	
	array->dim = dim;
	array->bounds = (int *)malloc(sizeof(int) * dim);
	
	int elemtotal = 1;
	va_list ap;
	va_start(ap, dim);
	for(i = 0; i < dim; ++i)
	{
		array->bounds[i] = va_arg(ap, int);
		elemtotal *= array->bounds[i];
	}
	va_end(ap);
	
	array->base = (int *)malloc(sizeof(int) * elemtotal);
	array->constants = (int *)malloc(sizeof(int) * dim);
	
	array->constants[dim - 1] = 1;
	for(j = dim - 2; j >= 0; --j)
	{
		array->constants[j] = array->bounds[j + 1] * array->constants[j + 1];
	}
	
	return;
}

void DestroyArray(Array * array)
{
	if(array->base == NULL)
	{
		return;
	}
	free(array->base);
	array->base = NULL;
	
	if(array->bounds == NULL)
	{
		return;
	}
	free(array->bounds);
	array->bounds = NULL;
	
	if(array->constants == NULL)
	{
		return;
	}
	free(array->constants);
	array->constants = NULL;
	
	return;
}

bool Locate(Array * array, va_list ap, int * off)
{
	int i;
	
	*off = 0;
	for(i = 0; i < array->dim; ++i)
	{
		int index = va_arg(ap, int);
		if(index < 0 || index > (array->bounds[i] - 1))
		{
			return false;
		}
		(*off) += array->constants[i] * index;
	}
	
	return true;
}

void Value(Array * array, int * e, ...)
{
	va_list ap;
	va_start(ap, e);
	
	int off;
	if(!Locate(array, ap, &off))
	{
		return;
	}
	*e = *(array->base + off);
	va_end(ap);
	
	return;
}

void Assign(Array * array, int e, ...)
{
	va_list ap;
	va_start(ap, e);
	
	int off;
	if(!Locate(array, ap, &off))
	{
		return;
	}
	*(array->base + off) = e;
	va_end(ap);
	
	return;
}

