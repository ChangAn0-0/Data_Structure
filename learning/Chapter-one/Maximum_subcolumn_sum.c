/*������к����⣺����һ������{a1,a2.....an},����������к�����һ����������
������������Ϊ���������0����{-1��3��-2��4��-8}���������Ϊ{3��-2��4}����Ϊ5*/
#include <stdio.h>
#include <time.h>

#define MAXN 1000

void transfer(int (*ptr)(int num[]), int num[], int n);
int Maxsubsum1(int num[]);
int Maxsubsum2(int num[]);

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

	transfer(Maxsubsum1, num, 1);
	transfer(Maxsubsum2, num, 2);


	return 0;
}

//�����㷨������������㷨��ʱ
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

}