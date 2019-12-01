#define _CRT_SECURE_NO_WARNINGS
#include"BinarySearchTree.h"

//compare
int compareStr(Element data1, Element data2) {
	return strcmp((char*)data1, (char*)data2);
}

//process print str
void process(Element data) {
	printf("%s  ", (char*)data);
}

int main() {
	//���� ����
	char** s;
	char ss[1000];
	int i = 0;
	int swit = 0;
	hTree* tree = BstCreate(compareStr);
	int* success = (int *)malloc(sizeof(int*));
	s = (char**)malloc(sizeof(char**)*100);
	*success = 0;
	printf("������ ���� ���� Binary Search tree...\n");

	//main
	while (1) {
		printf("\n0)Insert  1)Delete  2)Search  3)Print(DFT&BFT)  4)Exit : ");
		scanf("%d",&swit);

		if (swit == 0) {
			printf("���ڿ��� �Է��Ͻÿ� : ");
			scanf("%s", ss);
			*(s + i) = malloc(strlen(ss));
			strcpy(*(s + i), ss);
			if (Bstretrieve(tree, ss) != NULL) printf("%s�� �����մϴ�.\n", ss);
			else BstInsert(tree, *(s + i));
			i++;
		}
		else if (swit == 1) {
			printf("������ ���ڿ� �Է� : ");
			scanf("%s",ss);
			tree->root=deleteBST(tree, tree->root, ss, success);
			if (*success == 0) printf("�Է��Ͻ� ���ڿ��� �������� �ʽ��ϴ�.\n");
			else printf("���ڿ��� �����Ͽ����ϴ�\n");
		}
		else if (swit == 2) {
			printf("ã�� ���ڿ� �Է� : ");
			scanf("%s",ss);
			if (Bstretrieve(tree, ss) != NULL) printf("%s�� �����մϴ�.\n", ss);
			else printf("%s�� �������� �ʽ��ϴ�.\n",ss);
		}
		else if (swit == 3) {
			if (tree->count == 0) printf("�Է��� �����ϴ�.\n");
			else {
				printf("\nInorder : ");
				Inorder(tree->root, process);
				printf("\nPreorder : ");
				Preorder(tree->root, process);
				printf("\nPostorder : ");
				Postorder(tree->root, process);
				printf("\nLevelorder : ");
				LevelOrder(tree->root, process);
				printf("\n");
			}	
		}
		else if (swit == 4) {
			printf("Program Down...");
			if (tree->root == NULL) return 0;
			else DestroyTree(tree->root);
			free(tree);
			free(success);
			free(s);
			return 0;
		}
		else {
			printf("0~3������ ������ �Է�!");
		}
	}
	return 0;
}