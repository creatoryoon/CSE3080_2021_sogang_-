#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int Swap(int* a, int* b) {	//�� ������ �ٲ��ִ� �Լ�
	int c = *a;	//������ �ٲٱ� ��, a�� ����Ǿ� �ִ� ���� �ӽ� ���� c�� ����
	*a = *b;	//a�� ���� b�� ������ ����
	*b = c;		//b�� ���� c�� �����ص� ������ ����
}
	/*
	�������� �Լ�
	*/
void InsertionSort(int* arr, int size) {
	for (int i = 1; i < size; ++i) {	//0�� �ε����� ��ġ�� ���Ҵ� �̹� ���ĵ� ���¶�� �����ϰ� 1�� �ε������� ����
		int cur = i;	//���� �ڸ��� ã���� �ϴ� ������ ��ġ
		for (int j = i - 1; j >= 0; --j) {	//�̹� ���ĵ� �κ�, ��. ���� �����ϰ��� �ϴ� ������ ��ġ �ٷ� ���� ��ġ���ʹ� ��� ���ĵǾ� �ִ� �����̹Ƿ� 
											//�ش� ��ġ���� ó�� ��ġ���� �ݺ��ϸ� ���� ������ ��ġ�� Ž��
			if (arr[cur] < arr[j]) {	//���� ���� ���ں��� ���� ��ġ�� ���ڰ� ũ�ٸ� Swap �Լ��� ���� ��ġ ����
				Swap(&arr[cur], &arr[j]);
				--cur;	//���� ���� ������ ��ġ�� ����Ű�� ������ 1 ���ҽ��������ν� ���� ������ ��ġ�� ����
			}
			else {	//���� ���� ���ں��� �۰ų� ���� ���ڰ� ���� ��ġ�� �ִٸ� �ùٸ� ��ġ�̹Ƿ� �ݺ����� ����
				break;
			}
		}
	}
}
	/*
	Simulation�� ���� �Լ��� size�� �Է����� ������ �ش� ���ں��� 1���� �������� ���ĵ� �迭��
	�������� �����Ͽ� �ش� �ּҰ���ȯ

	Insertion sort�� �־��� ���� �迭�� ������������ ���ĵǾ� �ִ� ���
	*/
int* ArraySetting(int size) {
	int* temp = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i)
		temp[i] = size - i;
	return temp;
}
int main() {
	/*File I/O ����*/
	FILE* fp = fopen("lab1.data", "r");	//lab1.data�� ��θ� �ٲ��ּ���.
	if (fp == NULL) {
		printf("������ ã�� �� �����ϴ�.");
		return 0;
	}
	/*File I/O ����*/

	int num;		//File�κ��� ���ڸ� �Է����� �޾ƿ� ����
	int idx = 0;	//�Է����� ���� ������ ������ ���Ƹ��� ���ÿ� �迭�� �� �κ��� ������� Ȯ���� �� �ִ� ����
	int size = 10;	//�迭�� ���� ������ ������ ũ�⸦ �����ϴ� ����

	int* arr = (int*)malloc(sizeof(int) * size);	//arr�� size ũ��� �迭 ����

	printf("Input: ");
	/*
	scanf �Լ� �Ǵ� fscanf �Լ��� ��ȯ������ �ش� �Լ��� ���� �� ���� �Է��� �޾ƿԴ����� ��ȯ
	�̶� -1�� ��ȯ�Ǵ� ��� EOF�� �������� �ǹ�
	*/
	while (fscanf(fp, "%d", &num) != -1) {
		printf("%d ", num);
		if (idx >= size) {	//���� �迭�� ���� size���� ũ�ų� �������ٸ� �迭�� �÷���� ��
			size *= 2;	//�迭�� ũ�⸦ 2��� �÷��ְ�
			int* temp = (int*)malloc(sizeof(int) * size);	//�ش� ũ�⸸ŭ ���ο� �迭�� �����
			for (int i = 0; i < idx; ++i)	//���� �迭�� �ִ� ������ ���� ���� �迭�� �������� ��
				temp[i] = arr[i];
			free(arr);	//���� �迭�� ������ ����
			arr = temp;	//arr�� ���Ӱ� ���� �迭�� ���� �κ��� ����ų �� �ֵ��� �Ҵ�
		}
		arr[idx++] = num;	//�Է¹��� ���� �迭�� ����
	}
	puts("");

	InsertionSort(arr, idx);
	
	printf("Sorted: ");
	for (int i = 0; i < idx; ++i)
		printf("%d ", arr[i]);
	puts("\n");

	free(arr);

	//Simulation�� ���� ����
	printf("%4s %11s %-8s\n", "n", "repetitions", "time");
	for (int i = 0; i <= 100; i += 10){	//�迭�� ���� 0���� 100���� 10������ simulation
		//n, repetitions ���
		printf("%4d %11d ", i, 1000 - (i * 5));

		long sum = 0;	//Sinmulation ��ü �ð��� ���� ���� �� ����

		for (int j = 0; j < 1000 - (i * 5); ++j) {
			arr = ArraySetting(i);		//arr�� ũ�� i�� ���ο� �迭�� �Ҵ�
			clock_t start = clock();	//���� �ð� Ȯ��
			InsertionSort(arr, i);		//���� ����
			clock_t end = clock();		//�� �ð� Ȯ��
			sum += (end - start);		//sum ������ �� �ð� - ���� �ð��� ������,
		}
		printf("%-8lf\n", sum / (1000.0 - (i * 5)));	//time ���
	}
	return 0;
}