#include<stdio.h>
#include<stdlib.h>

/*
*	Sparse matrix�� ������ ������ ����ü�Դϴ�.
*/
struct MATRIX {
	int r, c, dat;
};
/*
*	Push �Լ��� �Ű������� �޴� MATRIX �迭��, r, c, dat �����͸� �߰��մϴ�.
*	idx�� MATRIX �迭�� ���� ��ġ, �����Ͱ� ����ִ� �� ���� ��ġ�� ��Ÿ����
*	capacity�� ���� ���� ������ ������
*	r, c, dat�� ������ �������Դϴ�.
*/
void Push(struct MATRIX** mat, int* idx, int* capacity, int r, int c, int dat) {
	if (*idx >= *capacity) {	//���� ���� �����ϰ��� �ϴ� ��ġ�� ���� ������ �������� ũ�ٸ�
		(*capacity) *= 2;	//���� ������ ������ 2��� �ø���
		struct MATRIX* tmp = (struct MATRIX*)malloc(sizeof(struct MATRIX) * (*capacity));	//�ش� �����͸� �����ϱ� ���� ���ο� ������ �Ҵ��� ��
		for (int k = 0; k < *idx; ++k)	//���� �迭�� �����͸� ���ο� �迭�� �������� ��
			tmp[k] = (*mat)[k];
		free((*mat));	//������ �迭 �޸𸮸� �����ϰ�
		(*mat) = tmp;	//���� ���� �迭�� ����Ű���� �ٲ�
	}
	(*mat)[(*idx)].r = r;	//�迭�� �� �ڿ� �����͸� �߰�
	(*mat)[(*idx)].c = c;
	(*mat)[(*idx)++].dat = dat;
}
/*
*	LoadMatrix�� fileName���κ��� ��� �����͸� �ҷ��ɴϴ�.
*	idx�� ���� ������ �������� ������ ��Ÿ���ϴ�.
*	capacity�� �ش� �迭�� ���� ���� ������ ������ ũ�⸦ ��Ÿ���ϴ�.
*	n�� m�� ����� ũ�⸦ ��Ÿ���ϴ�.
*/
struct MATRIX* LoadMatrix(const char* fileName, int * idx, int * capacity, int * n, int * m) {
	FILE* fp = fopen(fileName, "r");	//FILE �����͸� �̿��Ͽ� fileName�� read only�� �н��ϴ�.
	if (fp == NULL) {	//���� �ش� ������ ����ִٸ� �Լ��� ��� �����մϴ�.
		printf("Can't find file");
		return 0;
	}
	*idx = 0;	//idx�� 0����
	*capacity = 20;	//���� ������ ������ 20���� �ʱ�ȭ�մϴ�.
	struct MATRIX* res = (struct MATRIX*)malloc(sizeof(struct MATRIX) * (*capacity));	//�о�� ����� ������ �迭�� ������ݴϴ�.
	fscanf(fp, "%d %d", n, m);	//���Ϸκ��� ����� ũ�⸦ �о�ɴϴ�.
	for (int i = 0; i < *n; ++i) {
		for (int j = 0; j <* m; ++j) {
			int num; fscanf(fp, "%d", &num);	//���Ϸκ��� ����� ���Ҹ� �о�ɴϴ�.
			if (num != 0)	//���� ���Ұ� 0�� �ƴ϶��
				Push(&res, idx, capacity, i, j, num);	//Sparse matrix�� �ش� ���Ҹ� �����մϴ�.
		}
	}
	return res;
}
/*
*	Sum �Լ��� �� sparse matrix(A, B)�� �Ű������� �޾� A+B�� ����� sparse matrix�� ����� ��ȯ�մϴ�.
*	idx�� capacity�� ��� ������ ����� �Ͱ� ���� �ǹ̸� �����ϴ�.
*/
struct MATRIX* Sum(struct MATRIX* A, struct MATRIX* B, int idx1, int idx2, int * idx, int * capacity) {
	int i1 = 0, i2 = 0;	//i2, i2�� ���� A, B �迭�� �ε����� ������ �����Դϴ�.

	*idx = 0;	//idx�� capacity�� A+B�� ����� ������ �迭�� �ε����� ��������� ������ �����Դϴ�.
	*capacity = 20;
	struct MATRIX* res = (struct MATRIX*)malloc(sizeof(struct MATRIX) * (*capacity));	//A+B�� ����� ������ �迭�� ������ ���Ӱ� �Ҵ��մϴ�.

	while (i1 < idx1 && i2 < idx2) {	//�� �迭�� �ε��� ���� �������� �ݺ��� �� �ֵ��� ���ǽ��� ������ݴϴ�.
		if (A[i1].r == B[i2].r && A[i1].c == B[i2].c) {	//���� �� ������ ��/�� ���� ���ٸ� ���� �� �ִٴ� ���̹Ƿ�,
			Push(&res, idx, capacity, A[i1].r, A[i1].c, A[i1].dat + B[i2].dat);	//���� ����� ���� ���� �迭�� �־��ְ�
			++i1;	//�� �ε����� �ϳ��� ���������ݴϴ�.
			++i2;
		}
		else {
			int pos1 = A[i1].r * 10000 + A[i1].c;	//��� ���� ���� �����ϰ� ���� �� �ֵ��� 0000011111(0: r, 1 : c)�� �ǵ��� �ϳ��� ������ ������ݴϴ�)
			int pos2 = B[i2].r * 10000 + B[i2].c;
			if (pos1 > pos2) {	//pos1 > pos2���, B�迭�� ���� ��ġ�� �ִ� ���Ұ� �� �տ� �ִٴ� �ǹ��̹Ƿ�
				Push(&res, idx, capacity, B[i2].r, B[i2].c, B[i2].dat);	//B�迭�� ���� ���Ҹ� �����ϰ�
				++i2;
			}
			else {	//�ƴ϶��
				Push(&res, idx, capacity, A[i1].r, A[i1].c, A[i1].dat);	//A�迭�� ���� ���Ҹ� �����մϴ�.
				++i1;
			}

		}
	}
	/*
	*	���� �� �ݺ����� �׻� �� �� �ϳ��� ����˴ϴ�.
	*	���� while������ Ż�� ������ (i1 >= idx1 || i2 >= idx2)�̱� �����Դϴ�.
	*	���� ���� �����ִ� ���Ұ� �ִ� ��� ���� ������� �迭�� ����� �� �ֵ��� �߰��մϴ�.
	*/
	for (; i1 < idx1; ++i1)
		Push(&res, idx, capacity, A[i1].r, A[i1].c, A[i1].dat);
	for (; i2 < idx2; ++i2)
		Push(&res, idx, capacity, B[i2].r, B[i2].c, B[i2].dat);
	return res;
}
/*
*	FastTranspose �Լ��� sparse matrix �迭�� �Ű������� �޾� transpose�� ����� ��ȯ�մϴ�.
*	�̶� n�� m�� swap���ݴϴ�.
*/
struct MATRIX* FastTranspose(struct MATRIX* A, int idx, int * n, int * m) {
	struct MATRIX* res = (struct MATRIX*)malloc(sizeof(struct MATRIX) * idx);	//���ο� ����� ������ �迭�� ������ݴϴ�.
	int cols = (*m) + 1;	//rowTerms�� ������ֱ� ���� ����
	int* rowTerms = (int*)malloc(sizeof(int) * cols);	//rowTerms�� ���ο� �޸� ������ �Ҵ����ݴϴ�.
	int tmp = *n;	//n�� m�� ��ü�ϱ� ���� �ӽ� ����
	*n = *m;
	*m = tmp;

	for (int i = 0; i < cols; ++i)	//rowTerms�� 0���� �ʱ�ȭ���ݴϴ�.
		rowTerms[i] = 0;

	for (int i = 0; i < idx; ++i)	//�� column�� ������ ����� �����ݴϴ�.
		++rowTerms[A[i].c + 1];

	for (int i = 1; i < cols; ++i)	//start_pos�� ����� ������ �� �� �ֵ��� rowTerms�� �������� ����մϴ�.
		rowTerms[i] += rowTerms[i - 1];

	for (int i = 0; i < idx; ++i) {
		int pos = rowTerms[A[i].c];	//�ش� �迭�� ���� ���Ҹ� ��ġ��Ű�� ���� ����Ǿ� �� ��ġ�� ã���ϴ�.
									//�̶� rowTerms�� ����Ǿ� �ִ� ���� ������ ������ ������ start_pos�� ���� ���Դϴ�.
		res[pos].c = A[i].r;	//���ο� �����͸� �߰��մϴ�.
		res[pos].r = A[i].c;
		res[pos].dat = A[i].dat;
		++rowTerms[A[i].c];	//start_pos�� �ϳ� ������Ű�� �Ͱ� ���� ȿ���� ���ϴ�.
	}
	return res;
}

/* Test�� �ڵ� ���� */
int AA[10][10];
int BB[10][10];
void test(const char * file1, const char * file2) {
	freopen(file1, "r", stdin);
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			scanf("%d", &AA[i][j]);
	freopen(file2, "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf("%d", &BB[i][j]);
			AA[i][j] += BB[i][j];
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (AA[j][i])
				printf("%d %d %d\n", i, j, AA[j][i]);
		}
	}
	puts("\n\n");
}
/* Test�� �ڵ� �� */
int main() {
	/*
	*	test �Լ��� TEST�� �ڵ� �Դϴ�.
	*	�� �Լ��� �־��� �Է� ����(A.txt, B.txt)�� 2���� �迭�� �Է¹޾� ���� ��, transpose�� ����� sparse matrix �������� ����մϴ�
	*	���� FastTranspose �Լ��� ����� �����ϴ��� Ȯ���ϱ� ���� ����� �Լ��̹Ƿ� ���� ����ÿ��� �����ϼŵ� �����մϴ�.
	*/
	const char* file1 = "./Crebugs/SparseMatrix/A.txt";
	const char* file2 = "./Crebugs/SparseMatrix/B.txt";
	test(file1, file2);	//���� ����

	int idx1, cap1, idx2, cap2;	//Sparse matrix�� ���õ� ������ �����ϴ� �������Դϴ�. idx�� �迭�� ũ��, cap�� ���� ���尡���� ������ �����մϴ�.
	int n1, n2, m1, m2;	//Sparse matrix�� ���õ� ������ �����ϴ� �����Դϴ�. n�� m�� ����� ũ�⸦ ���մϴ�.

	struct MATRIX* A = LoadMatrix(file1, &idx1, &cap1, &n1, &m1);	//A.txt ������ �о�� A�� �����մϴ�.
	struct MATRIX* B = LoadMatrix(file2, &idx2, &cap2, &n2, &m2);	//B.txt ������ �о�� B�� �����մϴ�.
	
	int idx3, cap3;	//A+B�� ����� ������ ����� �����ϴ� sparse matrix�� ������ �����ϴ� �����Դϴ�.
	struct MATRIX* sum = Sum(A, B, idx1, idx2, &idx3, &cap3);	//sum�� A+B�� �����մϴ�.
	
	/*��� ���*/
	printf("%d %d %d\n", n1, m1, idx3);
	for (int i = 0; i < idx3; ++i)
		printf("%d %d %d\n", sum[i].r, sum[i].c, sum[i].dat);
	puts("\n\n");

	struct MATRIX* transpose = FastTranspose(sum, idx3, &n1, &m1);	//sum�� transpose ����� �����մϴ�.

	/*��� ���*/
	printf("%d %d %d\n", n1, m1, idx3);
	for (int i = 0; i < idx3; ++i)
		printf("%d %d %d\n", transpose[i].r, transpose[i].c, transpose[i].dat);

}