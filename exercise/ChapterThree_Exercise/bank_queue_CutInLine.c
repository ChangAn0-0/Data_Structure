#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum{ false, true }bool;

//--------定义队列-------------

//顾客信息
typedef struct {
	char name[4];
	int appointment;
	int time_cost;
	bool mark;         //标记其是否插队
	int notwork;       // 人脉圈子
}Item;

//队列节点
typedef struct {
	Item item;
	Item* next;
}Customer;

static Customer* front;
static Customer* rear;
static int CustomerCount = 0;

Customer* InitializationQueue(void)
{
	Customer* head = (Customer*)malloc(sizeof(Customer));
	head->next = NULL;
	rear = head;
	front = head;
	return head;
}

Customer* AddCustomer(Customer* rear,Item item)
{
	Customer* NewCustomer = (Customer*)malloc(sizeof(Customer));
	(* NewCustomer).item = item;
	NewCustomer->next = NULL;
	rear->next = NewCustomer;
	CustomerCount++;

	return rear;
}

Customer* DeleteCustomer(Customer* head)
{
	if (CustomerCount) {
		printf("queue is empty\n");
		return head;
	}
	Customer* temp;
	temp = head->next;
	head->next = temp->next;
	free(temp);

	return head;
}
//--------定义队列结束-------------

//--------定义圈子-----------------
struct Notwork {
	char name[4];
	int notwork;
};

struct Notwork People[10000];
static int PeopleCount=0;

int GetNotwork(struct Notwork* People,int PeopleCount,int num)
{
	int notwork_num = 1; int n;
	for (int j = 0; j < num;j++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", &People[PeopleCount].name);
			People[PeopleCount].notwork = notwork_num;
			PeopleCount++;
		}
		notwork_num++;
	}
	return PeopleCount;
}





int main(void)
{
	int num, count;
	printf(":");
	scanf("%d %d", &count, & num);
	PeopleCount = GetNotwork(People, PeopleCount,num);
//	for (int i = 0; i < PeopleCount; i++) {
//		printf("%s %d\n", People[i].name, People[i].notwork);
//	}

	return 0;
}
