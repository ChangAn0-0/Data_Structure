/*最大子列和问题：给定一列数组{a1,a2.....an},求出该数组中和最大的一段连续序列
并输出，如果和为负数，输出0。如{-1，3，-2，4，-8}，最大子列为{3，-2，4}，和为5*/
#include <stdio.h>
#include <time.h>

#define MAXN 1000

void transfer(int (*ptr)(int num[]), int num[], int n);
int Maxsubsum1(int num[]);
int Maxsubsum2(int num[]);

int main(void)
{
	//初始化数组
	int num[MAXN] = { 0 };
	for (int i = 0; i < MAXN; i++)
	{
		if (i % 2==0)
			num[i] = -i;
		else
			num[i] = i;
	}

	transfer(Maxsubsum1, num, 1);
	transfer(Maxsubsum2, num, 2);


	return 0;
}

//调用算法函数并输出该算法用时
void transfer(int (*ptr)(int num[]), int num[],int n)
{
	int max; double duration;
	clock_t start, stop;
	
	start = clock();
	max = ptr(num);
	stop = clock();
	duration = (double)stop - start;
	
	printf("Maxsum%d:%d duration:%2.6e\n",n,max, duration);
}

//算法一：穷举法
int Maxsubsum1(int num[])
{
	int Maxsum = 0, ThisSum;
	
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = i; j < MAXN; j++)
		{
			ThisSum = 0;
			for (int k = i; k <= j; k++)
				ThisSum += num[k];
			if (ThisSum > Maxsum)
				Maxsum = ThisSum;
		}
	}

	return Maxsum;
}

//算法二：在算法一的基础上进行改进，去除一层循环
int Maxsubsum2(int num[])
{
	int Maxsum = 0, ThisSum;

	for (int i = 0; i < MAXN; i++)
	{
		ThisSum = 0;
		for (int j = i; j < MAXN; j++)
		{
			ThisSum += num[j];
			if (ThisSum > Maxsum)
				Maxsum = ThisSum;
		}
	}

	return Maxsum;
}

//算法三：分治法，
int Maxsubsum3(int num[])
{

}