#define _CRT_SECURE_NO_WARNINGS
#include"BinaryTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	//���� ����
	char s[1000];
	TreeNode* root = NULL;

	//���ڿ� �Է¹ޱ�, ���� ���ֱ�
	printf("Enter string(��������) : ");
	gets(s);
	for (int i = 0; i < strlen(s);i++) {
		if (s[i] == ' ') {
			for (int j = i;j < strlen(s);j++) {
				s[j] = s[j + 1];
			}
			i--;
		}
	}

	//����Ʈ�� ����
	root = CreateTree(s, 1);

	//����Ʈ�� ���
	printf("\nPrint(PreOrder) : ");
	Preorder(root);
	printf("\n\nPrint(InOrder) : ");
	Inorder(root);
	printf("\n\nPrint(PostOrder) : ");
	Postorder(root);
	printf("\n\nPrint(breath-first traversal) : ");
	LevelOrder(root);
	
	DestroyTree(root);
	return 0;
}