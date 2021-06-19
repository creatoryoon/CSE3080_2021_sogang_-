#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int* Pre(char * str) {
	int m = strlen(str);
	int* pi = (int*)malloc(sizeof(int) * m);
	pi[0] = 0;
	int j = 0;	//현재 관리하고 있는 구간의 접두사와 접미사가 같은 최대 길이
	for (int i = 1; i < m; i++) {
		while (j > 0 && str[i] != str[j])	//만약 현재 관리한 구간의 양 끝문자가 서로 다른 경우 이전에 저장되어 있는 값들과 비교하여
											//가장 긴 공통 접두사/접미사의 길이를 찾음
			j = pi[j - 1];

		if (str[i] == str[j]) {	//만약 양 끝문자가 같다면 접두사/접미사의 길이를 1 증가시켜주며, 해당 값을 저장
			pi[i] = j + 1;
			++j;
		}
		else
			pi[i] = 0;	//그 외의 경우에는 공통 접두사/접미사가 없으므로 0을 저장
	}
	return pi;
}

int KMP(char * s, char * p, int * cnt) {
	int n = strlen(s);	//문자열 s의 길이
	int m = strlen(p);	//패턴 p의 길이
	int * pi = Pre(p);	//실패 함수를 통해 구한 값을 pi에 저장
	int j = 0;	//패턴 p의 위치
	for (int i = 0; i < n; i++) {
		++(*cnt);
		while (j > 0 && s[i] != p[j]) {	//문자열 s와 패턴 p를 비교하는 도중 다른 부분
			j = pi[j - 1];	
			++(*cnt);
		}
		if (s[i] == p[j]) {	//만약 두 위치의 문자가 같은 경우
			if (j == m - 1)	//패턴의 끝 문자와 비교한 경우 패턴을 찾은 것이므로 1을 반환
				return 1;

			else	//아니라면 다음 문자를 비교하기 위해 인덱스를 1 증가시킴
				++j;
		}
	}
	return 0;	//찾지 못한 경우 0 반환
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
		if (chk == 1)	//만약 chk가 1인 경우 해당 패턴을 찾은 것이므로 1 반환
			return 1;
	}
	return 0;	//찾지 못한 경우 0 반환
}
int main() {

//-------------파일 읽어서 할때-----------
//	FILE* fp = fopen("./input.txt", "r");
//	if (fp == NULL) {
//		printf("파일없음");
//		return 0;
//	}
//	char s[1000], p[1000];
//	fscanf(fp, "%s %s", s, p);
//
//	fclose(fp);
//-------------입력받아서 할 때--------
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