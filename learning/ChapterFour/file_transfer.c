#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX 10000

//定义集合及操作
typedef int Link[MAX];
typedef int Root;
typedef int Data;

void Initialization(Link link, int count)
{
	for (int i = 0; i < count; i++) {
		link[i] = -1;
	}
}

Root Find(Link link, Data data)
{
	if (link[data] < 0)
		return data;
	else
	{
		return link[data] = Find(link, link[data]);
	}
}

void Union(Link link, Root root1, Root root2)
{
	if (link[root1] < link[root2]) {
		link[root1] += link[root2];
		link[root2] = root1;
	}
	else {
		link[root2] += link[root1];
		link[root1] = root2;
	}
}
//-----------------------------结束定义

void Check(Link link);
void Link_Computer(Link link);
void Check_Notwork(Link link, int count);

int main(void)
{
	int count;static Link link; char ch;

	printf("enter count:\n");
	scanf("%d", &count);
	Initialization(link, count);

	do {
		scanf("%c", &ch);
		switch (ch) {
		case 'C':Check(link);
			break;
		case 'I':Link_Computer(link);
			break;
		case 'S':Check_Notwork(link, count);
			break;
		default:break;
		}
	} while (ch != 'S');
}

void Check(Link link)
{
	Data data1, data2;
	Root root1, root2;

	scanf("%d %d", &data1, &data2);
	root1 = Find(link, data1-1);
	root2 = Find(link, data2-1);

	if (root1 == root2) {
		printf("yes\n");
	}
	else
		printf("no\n");

	return;
}

void Link_Computer(Link link)
{
	Data data1, data2;
	Root root1, root2;

	scanf("%d %d", &data1, &data2);
	root1 = Find(link, data1-1);
	root2 = Find(link, data2-1);

	if (root1 != root2) {
		Union(link, root1, root2);
	}

	return;
}

void Check_Notwork(Link link,int count)
{
	int counter = 0;
	for(int i=0; i < count; i++) {
		if (link[i] < 0)
			counter++;
	}

	if (counter == 1) {
		printf("The network is connected\n");
	}
	else {
		printf("There are %d components.\n",counter);
	}

	return;
}


