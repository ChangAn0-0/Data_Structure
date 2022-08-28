#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int coef;
	int index;
}Item;

typedef struct node{
	Item item;
	struct node* next;
}Node;

Node* AddItem(int coef,int index, Node* rear)
{   //申请节点并赋值
	Node* new;
	new = (Node*)malloc(sizeof(Node));
	(new->item).coef = coef;
	(new->item).index = index;
	new->next = NULL;

	rear->next = new;
	rear = new;
	return rear;
}

Node* SetPolynomial(void)
{
	int coef, index, count;
	Node* front, * rear, * temp;

	scanf("%d", &count);
	temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;

	rear = temp;

	while (count--) 
	{
		scanf("%d %d", &coef, &index);
		rear=AddItem(coef, index, rear);
	}

	front = temp->next;
	free(temp);
	
	return front;
}

Node* Mult(Node* front1, Node* front2) 
{
	if (!front1 || !front2) {
		return NULL;
	}

	Node* result, * rear, * delete_or_new;
	//int coef, index;

	result = (Node*)malloc(sizeof(Node));
	result->next = NULL;
	rear = result;

	Node* temp1 = front1;
	Node* temp2 = front2;

	while (temp2) {
		int temp_coef = (temp1->item.coef) * (temp2->item.coef);
		int temp_index = (temp1->item.index) + (temp2->item.index);

		AddItem(temp_coef, temp_index, rear);
		temp2 = temp2->next;
	}
	temp1 = temp1->next;

	while (temp1) {
		temp2 = front2; rear = result;
		while (temp2) {
			int temp_coef = (temp1->item.coef) * (temp2->item.coef);
			int temp_index = (temp1->item.index) + (temp2->item.index);

			while (rear->next && (rear->next->item).index > temp_index) {
				rear = rear->next;
			}

			if (rear->next &&( (rear->next->item).index = temp_index)) {
				if ((rear->next->item).index + temp_index)
					(rear->next->item).index += temp_index;
				else
				{
					delete_or_new = rear->next;
					rear->next = delete_or_new->next;
					free(delete_or_new);
				}
			}
			else {
				delete_or_new = (Node*)malloc(sizeof(Node));
				delete_or_new->item.coef = temp_coef;
				delete_or_new->item.index = temp_index;

				delete_or_new->next = rear->next;
				rear->next = delete_or_new;
				rear = rear->next;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}

	delete_or_new = result;
	result = result->next;
	free(delete_or_new);

	return result;
}

void PrintResult(Node* result) {
	if (!result)
		printf("0 0\n");
	else {
		//printf("%d %d ", result->item.coef, result->item.index);
		//result = result->next;
		while (result) {
			printf("%d %d ", result->item.coef, result->item.index);
			result = result->next;
		}
		putchar('\n');
	}
}

int main(void)
{
	printf("enter polynomial one\n");
	Node* Polynomial_one = SetPolynomial();
	PrintResult(Polynomial_one);
	printf("enter polynomial two\n");
	Node* Polynomial_two = SetPolynomial();
	PrintResult(Polynomial_two);
	Node* result = Mult(Polynomial_one, Polynomial_two);

	PrintResult(result);
}