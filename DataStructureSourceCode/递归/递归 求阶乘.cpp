# include <stdio.h>

long f(long i)
{
	if(1 == i)
	{
		return 1;
	}
	else
	{
		return f(i-1)*i;
	}
}

int main(void)
{
	printf("%ld\n", f(5));
	
	return 0;
} 
