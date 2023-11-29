#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 20

int sorted[MAX_SIZE];

// 횟수 수정 필요
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

	// 출력
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
	int move[MAX_SIZE]; // 이동 횟수 저장 리스트
	int compare[MAX_SIZE]; // 비교 횟수 저장 리스트
	 
	int move_count = 0; // 이동 횟수 변수
	int compare_count = 0; // 비교 횟수 변수

	int move_average = 0; // 평균 이동 횟수
	int compare_avetage = 0; // 평균 비교 횟수

	// 난수 리스트 생성
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE; i++) {
		list[i] = rand() % 100;
	}

	// 오리지널 리스트 출력
	printf("Original List\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", list[i]);
	}
	printf("\n\n");

	printf("Merge Sort\n");
	merge_sort(list, 0, MAX_SIZE - 1, &move_count, &compare_count, 1);
	move[0] = move_count;
	compare[0] = compare_count;

	// 반복
	for (int k = 1; k < MAX_SIZE; k++) {
		// 이동 변수 초기화
		move_count = 0;
		compare_count = 0;

		// 난수 리스트 생성
		for (int i = 0; i < MAX_SIZE; i++) {
			list[i] = rand() % 100;
		}

		// merge 정렬 시행
		merge_sort(list, 0, MAX_SIZE - 1, &move_count, &compare_count, 0);

		// 이동, 비교 횟수 저장
		move[k] = move_count;
		compare[k] = compare_count;
	}

	// 평균 게산을 위한 sum 변수
	int sum = 0;

	// 평균 이동 횟수 구하기
	for (int i = 0; i < MAX_SIZE; i++) {
		sum += move[i];
	}
	move_average = sum / 20;

	// sum 초기화
	sum = 0;

	// 평균 비교 횟수 구하기
	for (int i = 0; i < MAX_SIZE; i++) {
		sum += compare[i];
	}
	compare_avetage = sum / 20;

	// 평균 값 출력
	printf("Move average : %d\n", move_average);
	printf("Compare average : %d\n", compare_avetage);
}
