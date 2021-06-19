#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int Swap(int* a, int* b) {	//두 변수를 바꿔주는 함수
	int c = *a;	//변수를 바꾸기 전, a에 저장되어 있는 값을 임시 변수 c에 저장
	*a = *b;	//a의 값을 b의 값으로 변경
	*b = c;		//b의 값을 c에 저장해둔 값으로 변경
}
	/*
	삽입정렬 함수
	*/
void InsertionSort(int* arr, int size) {
	for (int i = 1; i < size; ++i) {	//0번 인덱스에 위치한 원소는 이미 정렬된 상태라고 가정하고 1번 인덱스부터 시작
		int cur = i;	//현재 자리를 찾고자 하는 숫자의 위치
		for (int j = i - 1; j >= 0; --j) {	//이미 정렬된 부분, 즉. 현재 정렬하고자 하는 숫자의 위치 바로 이전 위치부터는 모두 정렬되어 있는 상태이므로 
											//해당 위치부터 처음 위치까지 반복하며 현재 숫자의 위치를 탐색
			if (arr[cur] < arr[j]) {	//만약 현재 숫자보다 이전 위치의 숫자가 크다면 Swap 함수를 통해 위치 변경
				Swap(&arr[cur], &arr[j]);
				--cur;	//이후 현재 숫자의 위치를 가리키는 변수를 1 감소시켜줌으로써 현재 숫자의 위치를 갱신
			}
			else {	//만약 현재 숫자보다 작거나 같은 숫자가 이전 위치에 있다면 올바른 위치이므로 반복문을 종료
				break;
			}
		}
	}
}
	/*
	Simulation을 위한 함수로 size를 입력으로 받으면 해당 숫자부터 1까지 역순으로 정렬된 배열을
	동적으로 생성하여 해당 주소값반환

	Insertion sort의 최악의 경우는 배열이 내림차순으로 정렬되어 있는 경우
	*/
int* ArraySetting(int size) {
	int* temp = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i)
		temp[i] = size - i;
	return temp;
}
int main() {
	/*File I/O 시작*/
	FILE* fp = fopen("lab1.data", "r");	//lab1.data의 경로를 바꿔주세요.
	if (fp == NULL) {
		printf("파일을 찾을 수 없습니다.");
		return 0;
	}
	/*File I/O 종료*/

	int num;		//File로부터 숫자를 입력으로 받아올 변수
	int idx = 0;	//입력으로 받은 숫자의 개수를 세아림과 동시에 배열의 끝 부분이 어디인지 확인할 수 있는 변수
	int size = 10;	//배열의 저장 가능한 공간의 크기를 저장하는 변수

	int* arr = (int*)malloc(sizeof(int) * size);	//arr에 size 크기로 배열 설정

	printf("Input: ");
	/*
	scanf 함수 또는 fscanf 함수는 반환값으로 해당 함수를 통해 몇 개의 입력을 받아왔는지를 반환
	이때 -1이 반환되는 경우 EOF를 만났음을 의미
	*/
	while (fscanf(fp, "%d", &num) != -1) {
		printf("%d ", num);
		if (idx >= size) {	//만약 배열의 끝이 size보다 크거나 같아졌다면 배열을 늘려줘야 함
			size *= 2;	//배열의 크기를 2배로 늘려주고
			int* temp = (int*)malloc(sizeof(int) * size);	//해당 크기만큼 새로운 배열을 만들어
			for (int i = 0; i < idx; ++i)	//이전 배열에 있던 정보를 새로 만든 배열에 복사해준 뒤
				temp[i] = arr[i];
			free(arr);	//이전 배열의 정보를 삭제
			arr = temp;	//arr이 새롭게 만든 배열의 시작 부분을 가리킬 수 있도록 할당
		}
		arr[idx++] = num;	//입력받은 값을 배열에 저장
	}
	puts("");

	InsertionSort(arr, idx);
	
	printf("Sorted: ");
	for (int i = 0; i < idx; ++i)
		printf("%d ", arr[i]);
	puts("\n");

	free(arr);

	//Simulation을 위한 세팅
	printf("%4s %11s %-8s\n", "n", "repetitions", "time");
	for (int i = 0; i <= 100; i += 10){	//배열의 길이 0부터 100까지 10단위로 simulation
		//n, repetitions 출력
		printf("%4d %11d ", i, 1000 - (i * 5));

		long sum = 0;	//Sinmulation 전체 시간의 합을 저장 할 변수

		for (int j = 0; j < 1000 - (i * 5); ++j) {
			arr = ArraySetting(i);		//arr에 크기 i의 새로운 배열을 할당
			clock_t start = clock();	//시작 시간 확인
			InsertionSort(arr, i);		//삽입 정렬
			clock_t end = clock();		//끝 시간 확인
			sum += (end - start);		//sum 변수에 끝 시간 - 시작 시간을 더해줌,
		}
		printf("%-8lf\n", sum / (1000.0 - (i * 5)));	//time 출력
	}
	return 0;
}