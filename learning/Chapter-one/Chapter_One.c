#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAXN 10
#define MAXK 1e7

double f1(double num[], double power, int n);
double f2(double num[], double power, int n);
void run(double (*ptr_f)(double*, double, int), double num[], int case_n);

clock_t start, stop;
double duration;

int main(void)
{
	double num[MAXN];
	for (int i = 0; i < MAXN; i++)
		num[i] = i ;
	
	run(f1, num, 1);
	run(f2, num, 1);

	return 0;
}

double f1(double num[], double power, int n)
{
	double sum = num[0];
	for (int i = 1; i <= n; i++)
		sum += num[i] * pow(power, i);
	return sum;
}

double f2(double num[], double power, int n)
{
	double sum = num[n];
	for (int i = n; i >0 ; i--)
		sum += num[i-1] + sum*power;
	return sum;
}

void run(double (*ptr_f)(double*, double, int), double num[], int case_n)
{
	start = clock();
	for (int i = 0; i < MAXK; i++)
		(*ptr_f)(num, 1.1, MAXN);
	stop = clock();

	duration = ((double)(stop)- (double)(start)) / CLK_TCK;
	printf("duration%d=%6.2e\n", case_n, duration);
}