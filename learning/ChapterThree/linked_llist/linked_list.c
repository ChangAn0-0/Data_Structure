#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLIST 10

typedef struct {
	char fname[10];
	char lname[10];
}Item;

typedef struct {
	Item item;
	struct Node* next;
}Node;

typedef struct {
	Node* head;
	int count;
}Entrance;

//初始化链表
void InitializationList(Entrance* ptr) {
	(*ptr).head = NULL;
	(*ptr).count = 0;
}

//检查链表是否为空
bool ListIsEmpty(Entrance* ptr) {
	if (ptr->head == NULL)
		return true;
	else
		return false;
}

//检查链表是否为满
bool ListIsFull(Entrance* ptr) {
	if (ptr->count == MAXLIST)
		return true;
	else
		return false;
}

//返回链表数量
int ListCount(Entrance* ptr) {
	return ptr->count;
}

//添加第K节点
void AddList(Entrance* ptr, int k,Item item) {
	if (ptr->count == MAXLIST) {
		printf("error:List is full\n");
			return;
	}

	Node* temp;
	Node* new = (Node*)malloc(sizeof(Node));
	new->item = item;

	/*if (k == 1)
	{
		new->next = ptr->head;
		ptr->head = new;
		ptr->count++;
		return;
	}*/

	//else
	{
		
		int i = 0;
		temp = ptr->head;
		while (temp && i < k - 1) {
			temp = temp->next;
			i++;
		}
		if (temp == NULL || i != k - 1) {
			printf("error:Unable to insert %dth linked list", k);
			free(new);
			return NULL;
		}
		else {
			new->next = temp->next;
			temp->next = new;
			ptr->count++;
		}
		return;
	}
}

//删除第K节点
void DeleteList(Entrance* ptr,int k) {
	int i = 0; Node* delete;
	Node* temp = ptr->head;
	if (temp == NULL)
	{
		printf("erroe:List is empty\n");
		return;
	}

	while (temp && i < k - 1) {
		temp = temp->next;
		i++;
	}

	if (i != k - 1 || temp == NULL || temp->next == NULL)
	{
		printf("error:delete failed");
		return;
	}
	else {
		delete = temp->next;
		temp->next = delete->next;
		free(delete);
		ptr->count--;
		return;
	}
}