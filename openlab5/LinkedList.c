#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// ���� ����Ʈ�� ���� ��� ����
typedef struct {
	int data;
	struct NODE *next;
}NODE;
// ���� ����Ʈ�� ��� ������� �����ϱ� ���� index, ���� ��带 ���ϱ� ���� tail ����
typedef struct list {
	int countIndex;
	NODE* tail;
}LIST;




LIST* createList() {
	LIST* list = (LIST*)malloc(sizeof(LIST));

	if (list == NULL)
	{
		printf("error\n");
	}
	else
	{
		list->tail = NULL;
		list->countIndex = 0;
	}

	return list;
}

void addNode(LIST* list, NODE element) {
	NODE *preNode = list->tail;
	NODE *newNode = (NODE*)malloc(sizeof(NODE));

	//������ ����
	newNode->data = element.data;

	if (list->countIndex == 0)
	{
		newNode->next = newNode;
		list->tail = newNode;
	}
	else
	{
		newNode->next = preNode->next;
		preNode->next = newNode;

		list->tail = newNode;
	}

	list->countIndex++;
}

void delNode(LIST* list, int position) {
	NODE *preNode = list->tail;
	NODE *delNode = list->tail;
	position = position - 1;
	if (list->countIndex == 0)
	{
		printf("��尡 �����ϴ�.");
	}
	else
	{

		for (int i = 0; i < position; i++)
		{
			preNode = preNode->next;
		}

		delNode = preNode->next;

		preNode->next = delNode->next;
		free(delNode);

		if (position == list->countIndex - 1)
		{
			list->tail = preNode;
		}

		list->countIndex--;
	}
}

void display(LIST* list) {
	int i;
	NODE* node;

	for (node = list->tail->next, i = 0; i < list->countIndex; i++, node = node->next) {
		printf("%d ", node->data);
	}
}

void merge(LIST*A, LIST*B) {	//merge �Ŀ��� B�� ������ A�� ��ħ
	NODE *prenode = A->tail->next;
	NODE *pronode = B->tail->next;
	A->countIndex += B->countIndex;
	A->tail->next = pronode;
	B->tail->next = prenode;
	A->tail = B->tail;
	prenode = A->tail->next;
	free(B);

}


void findDel(LIST *list, int n)//���񱳷� ����(��λ���)
{
	NODE *delNode = list->tail;
	NODE *preNode = list->tail;
	int i = 0;
	while (i != list->countIndex)
	{
		delNode = preNode->next;
		if (delNode->data == n)
		{
			preNode->next = delNode->next;
			if (i == list->countIndex - 1)
			{
				list->tail = preNode; // ���������ΰ�� ���� ����
			}
			free(delNode);
			list->countIndex--;
			return findDel(list, n);			// �����Ұ� �ִ°�� ���ֳ� �ٽ� Ȯ��.
		}	
		preNode = preNode->next;
		i++;
	}
}




int main() {
	LIST* A;
	LIST* B;
	LIST* C;
	NODE node;
	A = createList();
	B = createList();

	int f;
	// ���� A,B �ҷ��� ����Ʈ �����
	FILE* fp1 = fopen("./A.txt", "r");	//----------------------------------------���� ���!--------------------
	FILE* fp2 = fopen("./B.txt", "r");
	if (fp1 == NULL) {	//���� ������ �ٷ� ����.
		printf("Can't find file1");
		return 0;
	}
	if (fp2 == NULL) {	//���� ������ �ٷ� ����.
		printf("Can't find file2");
		return 0;
	}
	while (EOF != fscanf(fp1, "%d", &f)){
		node.data = f;
		addNode(A, node);
	}
	while (EOF != fscanf(fp2, "%d", &f)) {
		node.data = f;
		addNode(B, node);
	}
	fclose(fp1);
	fclose(fp2);

	merge(A, B); //��ġ��

	display(A); //�����ְ�
	printf("\n");

	FILE* fp3 = fopen("./C.txt", "r");
	while (EOF != fscanf(fp3, "%d", &f)) {
		int d = f;
		findDel(A, d); // C.txt�� ���ڸ� �񱳷� ã�°��

		//delNode(A, d); // C.txt�� �������ΰ��
	}
	fclose(fp3);

	display(A);

	return 0;
}

