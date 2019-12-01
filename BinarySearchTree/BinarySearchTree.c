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
	//변수 선언
	char** s;
	char ss[1000];
	int i = 0;
	int swit = 0;
	hTree* tree = BstCreate(compareStr);
	int* success = (int *)malloc(sizeof(int*));
	s = (char**)malloc(sizeof(char**)*100);
	*success = 0;
	printf("사전식 순서 정렬 Binary Search tree...\n");

	//main
	while (1) {
		printf("\n0)Insert  1)Delete  2)Search  3)Print(DFT&BFT)  4)Exit : ");
		scanf("%d",&swit);

		if (swit == 0) {
			printf("문자열을 입력하시오 : ");
			scanf("%s", ss);
			*(s + i) = malloc(strlen(ss));
			strcpy(*(s + i), ss);
			if (Bstretrieve(tree, ss) != NULL) printf("%s가 존재합니다.\n", ss);
			else BstInsert(tree, *(s + i));
			i++;
		}
		else if (swit == 1) {
			printf("삭제할 문자열 입력 : ");
			scanf("%s",ss);
			tree->root=deleteBST(tree, tree->root, ss, success);
			if (*success == 0) printf("입력하신 문자열이 존재하지 않습니다.\n");
			else printf("문자열을 삭제하였습니다\n");
		}
		else if (swit == 2) {
			printf("찾을 문자열 입력 : ");
			scanf("%s",ss);
			if (Bstretrieve(tree, ss) != NULL) printf("%s가 존재합니다.\n", ss);
			else printf("%s는 존재하지 않습니다.\n",ss);
		}
		else if (swit == 3) {
			if (tree->count == 0) printf("입력이 없습니다.\n");
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
			printf("0~3사이의 정수만 입력!");
		}
	}
	return 0;
}