#include <stdio.h>

typedef int Data;

typedef struct AVLNode* TreeNode;

typedef struct AVLNode {
	Data data;
	TreeNode left;
	TreeNode right;
	int height;
};

//�Ƚϴ�С-------
int Max(int a, int b)
{
	return a > b ? a : b;
}

//��ȡ����
int GetHeight(TreeNode root)
{
	int lh, rh, maxh;
	if (root) {
		lh = GetHeight(root->left);
		rh = GetHeight(root->right);
		maxh = lh > rh ? lh : rh;
		return maxh + 1;
	}
	else return 0;
}

//�����㷨
TreeNode SingleLeftRotation(TreeNode A)
{
	TreeNode B = A->left;
	A->left = B->right;
	B->right = A;

	A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
	B->height = Max(GetHeight(B->left), A->height) + 1;

	return B;
}

//�ҵ����㷨
TreeNode SingleRightRotation(TreeNode A)
{
	TreeNode B = A->right;
	A->right = B->left;
	B->left = A;

	A->height = Max(GetHeight(A->left), GetHeight(A->right)) + 1;
	B->height = Max(GetHeight(B->right), A->height) + 1;

	return B;
}

//����˫���㷨
TreeNode DoubleLeftRightRotation(TreeNode A)
{
	A->left = SingleRightRotation(A->left);
	return SingleLeftRotation(A);
}

//����˫���㷨
TreeNode DoubleRightLeftRotation(TreeNode A)
{
	A->right = SingleLeftRotation(A->right);
	return SingleLeftRotation(A);
}

//ƽ�����������
TreeNode Insert(TreeNode root, Data data)
{
	if (!root) {
		root = (TreeNode)malloc(sizeof(struct AVLNode));
		root->data = data;
		root->right = root->left = NULL;
		root->height = 1;
	}
	else if (data < root->data) {
		root->left = Insert(root->left, data);
		if (GetHeight(root->left) - GetHeight(root->right) == 2) {
			if (data < root->left->data)
				root = SingleLeftRotation(root);
			else
				root = DoubleLeftRightRotation(root);
		}
	}
	else if (data > root->data) {
		root->right = Insert(root->right, data);
		if (GetHeight(root->left) - GetHeight(root->right) == 2) {
			if (data > root->right->data)
				root = SingleRightRotation(root);
			else
				root = DoubleRightLeftRotation(root);
		}
	}
	root->height = Max(GetHeight(root->left), GetHeight(root->right))+1;

	return root;
}