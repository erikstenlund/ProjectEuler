#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int next_triangle_nbr(void)
{
	static int sum = 0;
	static int n = 1;
	sum += n++;
	return sum;
}

int divisors_in_nbr(int n)
{
	int divisors = 0;
	for (int i = 2; i < (int) sqrt(n); i++) {
		if (n % i == 0)
			divisors += 2;
	}

	// Do not count the square root twice
	if (sqrt(n) * sqrt(n) == n)
		divisors--;

	return divisors;
}


int main(int argc, const char *argv[])
{
	int nbr = next_triangle_nbr();

	while (divisors_in_nbr(nbr) <= 500)
		nbr = next_triangle_nbr();

	printf("%d, has %d divisors\n", nbr, divisors_in_nbr(nbr));
	return 0;
}

