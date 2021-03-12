# include <stdio.h>

long sum(long i)
{
	if(1 == i)
	{
		return 1;
	}
	else
	{
		return sum(i-1)+i;
	}
}

int main(void)
{
	printf("%ld\n", sum(100));
	
	return 0;
}
