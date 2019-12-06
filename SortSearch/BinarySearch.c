#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//0~99까지 수의 무작위 순서의 입력을 받아서 sort이후에 binarysearch 실행 

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

	printf("\nBinary Search 배열 정렬완료!\n\n");

	while (1) {
		printf("0)BinarySearch 1)exit : ");
		scanf("%d", &swit);
		switch (swit) {
		case 0:
			printf("찾으려는 수를 입력하시오 : ");
			scanf("%d", &find);
			if (binarySearch(list, 100, find, loc)) {
				printf("찾으려는 %d는 list의 인덱스 %d에 존재합니다.\n\n", find, *loc);
			}
			else printf("찾으시는 %d는 존재하지 않습니다.\n\n", find);
			continue;
		case 1:
			free(loc);
			fclose(f1);
			printf("exit!");
			return 0;
		default :
			printf("0,1만 입력하세요\n");
			continue;
		}
	}
	return 0;

}