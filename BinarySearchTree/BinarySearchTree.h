#define _CRT_SECURE_NO_WARNINGS
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

typedef struct {
	int count;
	TreeNode* root;
	int (*compare)(Element data1, Element data2);
}hTree;

//헤드 생성
hTree* BstCreate(int (*compare) (void* argu1, void* argu2)) {
	hTree* tree = NULL;
	tree = (hTree*)malloc(sizeof(hTree));
	if (tree) {
		tree->root = NULL;
		tree->count = 0;
		tree->compare = compare;
	}
	return tree;
}

//pre
void Preorder(TreeNode* root, void (*process)(Element data)) {
	if (root == NULL) return;
	process(root->data);
	Preorder(root->left, process);
	Preorder(root->right, process);
}

//in
void Inorder(TreeNode* root, void (*process)(Element data)) {
	if (root == NULL) return;
	Inorder(root->left, process);
	process(root->data);
	Inorder(root->right, process);
}

// post
void Postorder(TreeNode* root, void (*process)(Element data)) {
	if (root == NULL) return;
	Postorder(root->left, process);
	Postorder(root->right, process);
	process(root->data);
}

//bft 
void LevelOrder(TreeNode* root, void (*process)(Element data)) {
	Queue* q = NULL;
	if (root == NULL) return;
	q = CreateQueue();
	while (root) {
		process(root->data);
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
	if ((root->left) != NULL) DestroyTree(root->left);
	if ((root->right) != NULL) DestroyTree(root->right);
	free(root);
}

//insert
TreeNode* insert(hTree* tree, TreeNode* root, TreeNode* newnode) {
	if (root == NULL) return newnode;
	if (tree->compare(newnode->data, root->data) < 0) {
		root->left = insert(tree, root->left, newnode);
		return root;
	}
	else {
		root->right = insert(tree, root->right, newnode);
		return root;
	}
	return root;
}

//front
int BstInsert(hTree* tree, Element data) {
	TreeNode* newnode = NULL;
	newnode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newnode == NULL) return 0;
	newnode->right = NULL;
	newnode->left = NULL;
	newnode->data = data;
	if (tree->count == 0) tree->root = newnode;
	else insert(tree, tree->root, newnode);
	tree->count++;
	return 1;
}

//retrieve
void* retrieve(hTree* tree, Element data, TreeNode* root) {
	if (root != NULL) {
		if (tree->compare(data, root->data) < 0) return retrieve(tree, data, root->left);
		else if (tree->compare(data, root->data) > 0) return retrieve(tree, data, root->right);
		else return root->data;
	}
	else
		return NULL;
}

//outfront
void* Bstretrieve(hTree* tree, Element data) {
	if (tree->root) return retrieve(tree, data, tree->root);
	else return NULL;
}

//delete
TreeNode* deleteBST(hTree* tree, TreeNode* root, Element data, int* success) {
	if (root == NULL) {
		*success = 0;
		return root;
	}
	if ((tree->compare)(data, root->data) < 0) root->left = deleteBST(tree, root->left, data, success);
	else if ((tree->compare)(data, root->data) > 0) root->right = deleteBST(tree, root->right, data, success);
	else {
		TreeNode* delnode = NULL;
		*success = 1;
		if (!root->right) {
			delnode = root;
			root = delnode->left;
			free(delnode);
			return root;
		}
		else if (!root->left) {
			delnode = root;
			root = root->right;
			free(delnode);
			return root;
		}
		else {
			for (delnode = root->left; delnode->right != NULL; delnode = delnode->right);
			root->data = delnode->data;
			root->left = deleteBST(tree, root->left, delnode->data, success);
		}
	}
	return root;
}