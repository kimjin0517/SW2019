#pragma once
#include"Queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef void* Element;

//구조체
typedef struct tTreeNode {
	Element data;
	struct tTreeNode* left, * right;
} TreeNode;

//트리 생성 재귀함수이용
TreeNode* CreateTree(char* item, int count) {
	if (count > strlen(item)) return NULL;
	if (count > strlen(item) / 2) {
		TreeNode* pNewNode = (TreeNode*)malloc(sizeof(TreeNode));
		pNewNode->data = &item[count - 1];
		pNewNode->left = NULL;
		pNewNode->right = NULL;
		return pNewNode;
	}

	TreeNode* pNewNode = (TreeNode*)malloc(sizeof(TreeNode));
	pNewNode->data = &item[count - 1];
	pNewNode->left = CreateTree(item, count * 2);
	pNewNode->right = CreateTree(item, (count * 2) + 1);

	return pNewNode;
}

//pre
void Preorder(TreeNode* root)
{
	if (root == NULL)
		return;
	printf("%c", *(char*)root->data);
	Preorder(root->left);
	Preorder(root->right);
}

//in
void Inorder(TreeNode* root)
{
	if (root == NULL) return;
	Inorder(root->left);
	printf("%c", *(char*)root->data);
	Inorder(root->right);
}

// post
void Postorder(TreeNode* root)
{
	if (root == NULL) return;
	Postorder(root->left);
	Postorder(root->right);
	printf("%c", *(char*)root->data);
}

//bft 
void LevelOrder(TreeNode* root) {
	Queue* q = NULL;
	if (root == NULL)
		return;
	q = CreateQueue();
	while (root) {
		printf("%c", *(char*)root->data);
		if (root->left) Enqueue(q, root->left);
		if (root->right) Enqueue(q, root->right);
		if (!IsEmptyQueue(q)) root = Dequeue(q);
		else root = NULL;
	}
	DestroyQueue(q);
}

//트리메모리 해제
void DestroyTree(TreeNode* root)
{
	if (root == NULL) return;
	if (root->left) DestroyTree(root->left);
	if (root->right) DestroyTree(root->right);
	free(root);
}