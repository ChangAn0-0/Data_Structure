/*������к����⣺����һ������{a1,a2.....an},����������к�����һ����������
������������Ϊ���������0����{-1��3��-2��4��-8}���������Ϊ{3��-2��4}����Ϊ5*/
#include <stdio.h>
#include <time.h>

#define MAXN 1000

void transfer(int (*ptr)(int num[]), int num[], int n);
int Maxsubsum1(int num[]);
int Maxsubsum2(int num[]);
int Maxsubsum3(int num[]);
int Maxsubsum4(int num[]);

int divide(int num[], int left, int right);
int Max3(int a, int b, int c);

int main(void)
{
	//��ʼ������
	int num[MAXN] = { 0 };
	for (int i = 0; i < MAXN; i++)
	{
		if (i % 2==0)
			num[i] = -i;
		else
			num[i] = i;
	}

	//transfer(Maxsubsum1, num, 1);
	//transfer(Maxsubsum2, num, 2);
	transfer(Maxsubsum3, num, 3);
	transfer(Maxsubsum4, num, 4);

	return 0;
}

//�����㷨������������㷨��ʱ
void transfer(int (*ptr)(int num[]), int num[],int n)
{
	int max=0; double duration;
	clock_t start, stop;
	
	start = clock();
	max = ptr(num);
	stop = clock();
	duration = ((double)stop - start);
	
	printf("Maxsum%d:%d duration:%2.9e\n",n,max, duration);
}

//�㷨һ����ٷ�
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

//�㷨�������㷨һ�Ļ����Ͻ��иĽ���ȥ��һ��ѭ��
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

//�㷨�������η���
int Maxsubsum3(int num[])
{
	return divide(num, 0, MAXN - 1);
}

int divide(int num[], int left, int right)
{
	int Maxleftsum, Maxrightsum;
	int Maxleftbordesum, Maxrightbordesum;

	int Leftbordesum, Rightbordesum;
	int center, i;

	if (left = right){
		if (num[left] > 0)
			return num[left];
		else
			return 0;
	}

	center = (left + right) / 2;

	Maxleftsum = divide(num, left, center);
	Maxrightsum = divide(num, center + 1, right);

	Maxleftbordesum = 0; Maxrightbordesum = 0;
	Leftbordesum = 0; Rightbordesum = 0;
	for (i = center; i >= left; i--)
	{
		Leftbordesum += num[i];
		if (Leftbordesum > Maxleftbordesum)
			Maxleftbordesum = Leftbordesum;
	}

	for (i = center; i <= right; i++)
	{
		Rightbordesum += num[i];
		if (Rightbordesum > Maxrightbordesum)
			Maxrightbordesum = Rightbordesum;
	}

	return Max3(Maxleftsum, Maxrightsum, Maxleftbordesum + Maxrightbordesum);
}

int Max3(int a, int b, int c)
{
	return a > b ? a > c ? a : c : b > c ? b : c;
}

//�㷨�ģ������㷨
int Maxsubsum4(int num[])
{
	int i;
	int ThisSum=0, Maxsum=0;

	for (i = 0; i < MAXN; i++)
	{
		ThisSum += num[i];
		if (ThisSum < 0)
			ThisSum = 0;
		if (ThisSum > Maxsum)
			Maxsum = ThisSum;
	}
	return Maxsum;
}