#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 20

int sorted[MAX_SIZE];

// Ƚ�� ���� �ʿ�
void merge(int list[], int left, int mid, int right, int* move_count, int* compare_count, int print) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i<=mid && j<=right) {
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
			(*compare_count)++;
		}
		else {
			sorted[k++] = list[j++];
			(*compare_count)++;
			(*move_count)++;
		}
	}

	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			(*compare_count)++;
		}
	}

	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			(*move_count)++;
		}
	}

	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
		(*move_count)++;
	}

	// ���
	if (print == 1) {
		for (int n = 0; n < MAX_SIZE; n++) {
			printf("%d ", list[n]);
		}
		printf("\n");
	}

}

void merge_sort(int list[], int left, int right,int* move_count, int* compare_count,int print) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid, move_count, compare_count, print);
		merge_sort(list, mid + 1, right, move_count, compare_count, print);
		merge(list, left, mid, right, move_count, compare_count, print);
	}
}

int main()
{
	int list[MAX_SIZE];
	int move[MAX_SIZE]; // �̵� Ƚ�� ���� ����Ʈ
	int compare[MAX_SIZE]; // �� Ƚ�� ���� ����Ʈ
	 
	int move_count = 0; // �̵� Ƚ�� ����
	int compare_count = 0; // �� Ƚ�� ����

	int move_average = 0; // ��� �̵� Ƚ��
	int compare_avetage = 0; // ��� �� Ƚ��

	// ���� ����Ʈ ����
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE; i++) {
		list[i] = rand() % 100;
	}

	// �������� ����Ʈ ���
	printf("Original List\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", list[i]);
	}
	printf("\n\n");

	printf("Merge Sort\n");
	merge_sort(list, 0, MAX_SIZE - 1, &move_count, &compare_count, 1);
	move[0] = move_count;
	compare[0] = compare_count;

	// �ݺ�
	for (int k = 1; k < MAX_SIZE; k++) {
		// �̵� ���� �ʱ�ȭ
		move_count = 0;
		compare_count = 0;

		// ���� ����Ʈ ����
		for (int i = 0; i < MAX_SIZE; i++) {
			list[i] = rand() % 100;
		}

		// merge ���� ����
		merge_sort(list, 0, MAX_SIZE - 1, &move_count, &compare_count, 0);

		// �̵�, �� Ƚ�� ����
		move[k] = move_count;
		compare[k] = compare_count;
	}

	// ��� �Ի��� ���� sum ����
	int sum = 0;

	// ��� �̵� Ƚ�� ���ϱ�
	for (int i = 0; i < MAX_SIZE; i++) {
		sum += move[i];
	}
	move_average = sum / 20;

	// sum �ʱ�ȭ
	sum = 0;

	// ��� �� Ƚ�� ���ϱ�
	for (int i = 0; i < MAX_SIZE; i++) {
		sum += compare[i];
	}
	compare_avetage = sum / 20;

	// ��� �� ���
	printf("Move average : %d\n", move_average);
	printf("Compare average : %d\n", compare_avetage);
}
