#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int* Pre(char * str) {
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

int KMP(char * s, char * p, int * cnt) {
	int n = strlen(s);	//���ڿ� s�� ����
	int m = strlen(p);	//���� p�� ����
	int * pi = Pre(p);	//���� �Լ��� ���� ���� ���� pi�� ����
	int j = 0;	//���� p�� ��ġ
	for (int i = 0; i < n; i++) {
		++(*cnt);
		while (j > 0 && s[i] != p[j]) {	//���ڿ� s�� ���� p�� ���ϴ� ���� �ٸ� �κ�
			j = pi[j - 1];	
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



int Bo(char* s, char* p, int* cnt) {
	int n = strlen(s);
	int m = strlen(p);
	for (int i = 0; i + m <= n; ++i) {	
		int chk = 1;
		for (int j = 0; j < m; ++j) {	
			++(*cnt);
			if (s[i + j] != p[j]) {	
				chk = 0;	
			}
		}
		if (chk == 1)	//���� chk�� 1�� ��� �ش� ������ ã�� ���̹Ƿ� 1 ��ȯ
			return 1;
	}
	return 0;	//ã�� ���� ��� 0 ��ȯ
}
int main() {

//-------------���� �о �Ҷ�-----------
//	FILE* fp = fopen("./input.txt", "r");
//	if (fp == NULL) {
//		printf("���Ͼ���");
//		return 0;
//	}
//	char s[1000], p[1000];
//	fscanf(fp, "%s %s", s, p);
//
//	fclose(fp);
//-------------�Է¹޾Ƽ� �� ��--------
	 char s[1000], p[1000];  
	 scanf("%s %s", s, p);
//-----------------------------------------------


	int cnt1 = 0, cnt2 = 0;
	int res1 = Bo(s, p, &cnt1);
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