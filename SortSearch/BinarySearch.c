#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//0~99���� ���� ������ ������ �Է��� �޾Ƽ� sort���Ŀ� binarysearch ���� 

int binarySearch(int list[], int n, int target, int* locn){
	int begin = 0;
	int mid = 0;
	int end = n - 1;
	while (begin <= end) {
		mid = (begin + end) / 2;
		if (target > list[mid]) begin = mid + 1;
		else if (target < list[mid]) end = mid - 1;
		else begin = end + 1;
	}
	*locn = mid;
	if (target == list[mid]) return 1;
	else return 0;
}

int main() {
	int list[100];
	int temp=0;
	int find=0;
	int* loc;
	int swit;
	loc = (int*)malloc(sizeof(int*));

	FILE* f1 = fopen("input.txt", "r");
	if (f1 == NULL) return 0;
	
	printf("input :\n");
	for (int i = 0; i < 100; i++) {
		fscanf(f1, "%d\n", &list[i]);
		printf("%d, ", list[i]);
		if (i % 10 == 9) printf("\n");
	}
	for (int i = 0; i < 99; i++) {
		for (int j = i; j < 100; j++) {
			if (list[i] > list[j]) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}	
		}
	}

	printf("\nBinary Search �迭 ���ĿϷ�!\n\n");

	while (1) {
		printf("0)BinarySearch 1)exit : ");
		scanf("%d", &swit);
		switch (swit) {
		case 0:
			printf("ã������ ���� �Է��Ͻÿ� : ");
			scanf("%d", &find);
			if (binarySearch(list, 100, find, loc)) {
				printf("ã������ %d�� list�� �ε��� %d�� �����մϴ�.\n\n", find, *loc);
			}
			else printf("ã���ô� %d�� �������� �ʽ��ϴ�.\n\n", find);
			continue;
		case 1:
			free(loc);
			fclose(f1);
			printf("exit!");
			return 0;
		default :
			printf("0,1�� �Է��ϼ���\n");
			continue;
		}
	}
	return 0;

}