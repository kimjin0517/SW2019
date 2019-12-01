#define _CRT_SECURE_NO_WARNINGS
#include"BinaryTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	//변수 선언
	char s[1000];
	TreeNode* root = NULL;

	//문자열 입력받기, 공백 없애기
	printf("Enter string(공백제외) : ");
	gets(s);
	for (int i = 0; i < strlen(s);i++) {
		if (s[i] == ' ') {
			for (int j = i;j < strlen(s);j++) {
				s[j] = s[j + 1];
			}
			i--;
		}
	}

	//이진트리 구성
	root = CreateTree(s, 1);

	//이진트리 출력
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