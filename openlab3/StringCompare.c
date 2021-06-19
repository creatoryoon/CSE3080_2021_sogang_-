#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
* ���� �Լ��� �˻� �ϰ��� �ϴ� ����(str)�� ��ó��
* pi[i]���� 0~i��°���� ���ڸ� ������� ��, ���λ�� ���̻簡 �������� �ִ� ����
*/
int* Preprocessing(char * str) {
	int m = strlen(str);
	int* pi = (int*)malloc(sizeof(int) * m);
	pi[0] = 0;
	int j = 0;	//���� �����ϰ� �ִ� ������ ���λ�� ���̻簡 ���� �ִ� ����
	for (int i = 1; i < m; i++) {
		while (j > 0 && str[i] != str[j])	//���� ���� ������ ������ �� �����ڰ� ���� �ٸ� ��� ������ ����Ǿ� �ִ� ����� ���Ͽ�
											//���� �� ���� ���λ�/���̻��� ���̸� ã��
			j = pi[j - 1];

		if (str[i] == str[j]) {	//���� �� �����ڰ� ���ٸ� ���λ�/���̻��� ���̸� 1 ���������ָ�, �ش� ���� ����
			pi[i] = j + 1;
			++j;
		}
		else 
			pi[i] = 0;	//�� ���� ��쿡�� ���� ���λ�/���̻簡 �����Ƿ� 0�� ����
	}
	return pi;
}
/*
*	KMP �Լ��� ���ڿ� s�� ���� p�� �Ű������� �޾�, ���ڿ� s���� ���� p�� ã�� ����� ��ȯ
*	�̶� cnt�� �������� ������ �ݺ����� ����Ǵ� Ƚ��
*/
int KMP(char * s, char * p, int * cnt) {
	int n = strlen(s);	//n�� ���ڿ� s�� ����
	int m = strlen(p);	//p�� ���� p�� ����
	int * pi = Preprocessing(p);	//���� p�� ���� �Լ��� ���� ���� ���� pi�� ����
	int j = 0;	//���� p�� ��ġ�� ������ ����
	for (int i = 0; i < n; i++) {
		++(*cnt);
		while (j > 0 && s[i] != p[j]) {	//���ڿ� s�� ���� p�� ���ϴ� ���� �ٸ� �κ��� ã�Ҵٸ�
			j = pi[j - 1];	//���� �Լ��� �̿��� ���� ���� �������� j�� �̵�
			++(*cnt);
		}
		if (s[i] == p[j]) {	//���� �� ��ġ�� ���ڰ� ���� ���
			if (j == m - 1)	//������ �� ���ڿ� ���� ��� ������ ã�� ���̹Ƿ� 1�� ��ȯ
				return 1;

			else	//�ƴ϶�� ���� ���ڸ� ���ϱ� ���� �ε����� 1 ������Ŵ
				++j;
		}
	}
	return 0;	//ã�� ���� ��� 0 ��ȯ
}
/*
*	Naive �Լ��� ���ڿ� s�� ���� p�� �Ű������� �޾�, ���ڿ� s���� ���� p�� ã�� ����� ��ȯ(O(NM)) N: ���ڿ��� ����, M: ������ ����
*	�̶� cnt�� �������� ������ �ݺ����� ����Ǵ� Ƚ��
*/
int Naive(char* s, char* p, int* cnt) {
	int n = strlen(s);	//n���� str�� ���̸� ����
	int m = strlen(p);	//m���� pat�� ���̸� ����
	for (int i = 0; i + m <= n; ++i) {	//���� �񱳸� �����ϴ� ������ ��ġ�� ���Ϻ��� �۴ٸ� �� �̻� ������ ã�� �� �����Ƿ� �ݺ��� ����
		int chk = 1;	//������ ã�Ҵ��� Ȯ���� ����
		for (int j = 0; j < m; ++j) {	//������ ���̸�ŭ �ݺ�
			++(*cnt);
			if (s[i + j] != p[j]) {	//���� ���ϴ� �� ���ڰ� ���� �ٸ��ٸ�
				chk = 0;	//chk�� 0���� ���� Ž���� ���������� Ȯ��
			}
		}
		if (chk == 1)	//���� chk�� 1�� ��� �ش� ������ ã�� ���̹Ƿ� 1 ��ȯ
			return 1;
	}
	return 0;	//ã�� ���� ��� 0 ��ȯ
}
int main() {
	const char fileName = "input.txt";
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Can't open file");
		return 0;
	}
	char s[1000], p[1000];
	fscanf(fp, "%s %s", s, p);

	fclose(fp);

	int cnt1 = 0, cnt2 = 0;
	int res1 = Naive(s, p, &cnt1);
	int res2 = KMP(s, p, &cnt2);

	if (res1 == 1)
		printf("YES ");
	else
		printf("NO ");
	printf("%d\n", cnt1);

	if (res2 == 1)
		printf("YES ");
	else
		printf("NO ");
	printf("%d", cnt2);
	
}