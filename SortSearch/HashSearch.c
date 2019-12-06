#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
Hash function = item^2+(item/2)+(17*item)
Collision : Bucket hashing�� �̿�
*/

typedef struct {
	int list[3];
	int cnt;
}Bucket;

int main() {
	Bucket bucket[200];
	int idx=0;
	int tmp=0;
	int find=0;
	int found = 0;
	int swit = 0;
	FILE* f1 = fopen("input.txt", "r");
	if (f1 == NULL) return 0;

	for (int i = 0; i < 200; i++) {
		bucket[i].cnt = 0;
		for (int j = 0; j < 3; j++) {
			bucket[i].list[j] = 0;
		}
	}
	printf("Hash Search\n");
	printf("");
	printf("input :\n");

	for (int i = 0; i < 100; i++) {
		fscanf(f1, "%d\n", &tmp);
		printf("%d, ", tmp);
		if (i % 10 == 9) printf("\n");
		idx = pow(tmp,2)+(tmp/2)+(17*tmp);
		idx = idx % 201;
		bucket[idx].list[(bucket[idx].cnt++)] = tmp;
	}

	printf("�ؽ� ���� �Ϸ�\n\n");
	
	while (1) {
		printf("0)Hash Search 1)Exit :");
		scanf("%d", &swit);
		switch (swit) {
		case 0:
			printf("ã�� ���� : ");
			scanf("%d", &find);
			idx = pow(find, 2) + (find / 2) + (17 * find);
			idx = idx % 201;
			found = 0;
			for (int i = 0; i < 3; i++) {
				if (bucket[idx].list[i] == find) {
					found = 1;
					break;
				}
			}
			if (found == 1) printf("ã���ô� %d�� bucket�� %d �ε����� �����մϴ�.\n\n", find, idx);
			else printf("ã���ô� %d�� �������� �ʽ��ϴ�.\n\n", find);
			continue;
		case 1:
			printf("Exit!");
			fclose(f1);
			return 0;
		default:
			printf("0,1�� �Է��ϼ���!");
			continue;
		}
	}
	return 0;
}