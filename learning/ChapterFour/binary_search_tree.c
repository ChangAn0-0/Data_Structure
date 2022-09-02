#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

typedef int Data;

typedef  struct Tree* TreeNode;

struct Tree{
	Data data;
	TreeNode left;
	TreeNode right;
};

//层序生成二叉树算法
/*
TreeNode* CreatTree(void)
{
	Data data;
	TreeNode* root;
	TreeNode* temp;
	Queue Q = CreatQueue();


	scanf("%d", &data);
	if (data != 0) {
		root = (TreeNode*)malloc(sizeof(TreeNode));
		root->data = data;
		root->left = root->right = NULL;
		AddQ(Q, root);
	}
	else return NULL;

	while (!IsEmpty(Q)) {
		temp = Delete(Q);
		scanf("%d", &data);
		if (data == 0)temp->left = NULL;
		else {
			temp->left = (TreeNode*)malloc(sizeof(TreeNode));
			temp->left->data = data;
			(*temp->left).left = (*temp->left).right = NULL;
			AddQ(Q, temp->left);
		}
		scanf("%d", &data);
		if (data == 0)temp->right = NULL;
		else {
			temp->right = (TreeNode*)malloc(sizeof(TreeNode));
			temp->right->data = data;
			(*temp->right).left = (*temp->right).right = NULL;
			AddQ(Q, temp->right);
		}
	}
	return root;
}
*/


//二叉搜索树插入算法
TreeNode Insert(TreeNode root, Data data)
{
	if (!root) {
		root = (TreeNode)malloc(sizeof(struct Tree));
		if (root == NULL) {
			printf("error:line 63");
			exit(1);
		}
		else {
			root->data = data;
			root->left = root->right = NULL;
		}
	}
	else {
		if (data < root->data) {
			root->left = Insert(root->left, data);
		}
		else if (data > root->data){
			root->right = Insert(root->right, data);
		}
	}
	return root;
}

//二叉树历遍-中序
void InorderTravelsal(TreeNode root)
{
	if (root) {
		InorderTravelsal(root->left);
		printf("%d", root->data);
		InorderTravelsal(root->right);
	}
}

//二叉树历遍-先序
void PreorderTravelsal(TreeNode root)
{
	if (root) {
		printf("%d", root->data);
		PreorderTravelsal(root->left);
		PreorderTravelsal(root->right);
	}
}

//二叉树历遍-后序
void PostorderTravelsal(TreeNode root)
{
	if (root) {
		PostorderTravelsal(root->left);
		PostorderTravelsal(root->right);
		printf("%d", root->data);
	}
}

//二叉搜索树查找-递归
TreeNode Recursive_Find(TreeNode root, Data data)
{
	if (!root) {
		printf("tree is empty");
		return NULL;
}
	if (data < root->data) {
		return Recursive_Find(root->left, data);
	}
	else if (data > root->data) {
		return Recursive_Find(root->right, data);
	}
	else
		return root;
}

//二叉搜索树-迭代
TreeNode Iterate_Find(TreeNode root, Data data)
{
	while (root) {
		if (data < root->data) {
			root = root->left;
		}
		else if (data > root->data) {
			root = root->right;
		}
		else
			break;
}
	return root;
}

//二叉搜索树最小值-递归
TreeNode FindMin(TreeNode root)
{
	if (!root) return NULL;
	else if (!root->left)return root;
	else return FindMin(root->left);
}

//二叉搜索树最大值-迭代
TreeNode FindMax(TreeNode root)
{
	if (root) {
		while (root->right) {
			root = root->right;
		}
	}
	return root;
}

//二叉树输出叶子节点
void PreorderPrintLeaves(TreeNode root)
{
	if (root) {
		if (!root->left && !root->right)
			printf("%d", root->data);
		PreorderTravelsal(root->left);
		PreorderTravelsal(root->right);
	}
}

//二叉树高度
int GetHight(TreeNode root)
{
	int lh, rh, maxh;
	if (root) {
		lh = GeiHight(root->left);
		rh = GetHight(root->right);
		maxh = lh > rh ? lh : rh;
		return (maxh + 1);
	}
	else return 0;
}

//二叉搜索树删除节点
TreeNode Delete(TreeNode root, Data data)
{
	TreeNode temp;
	if (!root) {
		printf("no find data");
		return root;
	}
	else {
		if (data < root->data)
			root->left = Delete(root->left, data);
		else if (data > root->right)
			root->right = Delete(root->right, data);
		else {
			if (root->left && root->right) {
				temp = FindMin(root->right);
				root->data = temp->data;

				root->right = Delete(root->right, root->data);
			}
			else {
				temp = root;
				if (!root->left)
					root = root->right;
				else
					root = root->left;
				free(temp);
			}
		}
	}
	return root;
}


int main(void)
{
	TreeNode root=NULL, result;
	Data data,find_data;
	printf("enter data:\n");
	while (scanf("%d", &data) == 1) {
		root = Insert(root, data);
	}
	while (getchar() != '\n')
		continue;

	InorderTravelsal(root);

	printf("\nenter find data:\n");
	scanf("%d", &find_data);

	result = Recursive_Find(root, find_data);
	printf("%p %d\n", result, result->data);

	result = Iterate_Find(root, find_data);
	printf("%p %d\n", result, result->data);

	return 0;
}
