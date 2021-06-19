#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define null NULL
// ���� ����Ʈ�� ���� ��� ����
typedef struct {
	int data;
	struct Node *next;
}Node;
// ���� ����Ʈ�� ��� ������� ���� ���� index, ���� ��带 ���� tail ����
typedef struct list {
	int countIndex;
	Node* tail;
}List;




List* CreateList() {
	List* list = (List*)malloc(sizeof(List));

	if (list == null)
	{
		printf("error\n");
	}
	else
	{
		list->tail = null;
		list->countIndex = 0;
	}

	return list;
}

void AddNode(List* list, Node element) {
	Node *preNode = list->tail;
	Node *newNode = (Node*)malloc(sizeof(Node));

	//������ ����
	newNode->data = element.data;

	if (list->countIndex == 0)
	{
		newNode->next = newNode;
		list->tail = newNode;
	}
	else
	{
		//for (int i = 0; i < list->countIndex; i++)
		//{
		//	preNode = preNode->next;
		//}

		newNode->next = preNode->next;
		preNode->next = newNode;

		list->tail = newNode;
	}

	list->countIndex++;
}

void DelNode(List* list, int position) {
	Node *preNode = list->tail;
	Node *delNode = list->tail;
	position = position - 1;
	//printf("%d", preNode->data);

	//position = position - 1;
	//printf("%d", delNode->data);
	if (list->countIndex == 0)
	{
		printf("��尡 �����ϴ�.");
	}
	else
	{
		//int count = 0;
		for (int i = 0; i < position; i++)
		{
			//printf("%d", preNode->data);
			//count += 1;
			preNode = preNode->next;
			//printf("\n\n%d %d",count, preNode->data);
			
		}

		delNode = preNode->next;
		//printf("\n %d %d", position, delNode->data);
		preNode->next = delNode->next;
		free(delNode);

		if (position == list->countIndex - 1)
		{
			list->tail = preNode;
		}

		list->countIndex--;
	}
}

void display(List* list) {
	int i;
	Node* node;

	for (node = list->tail->next, i = 0; i < list->countIndex; i++, node = node->next) {
		printf("%d ", node->data);
	}
}

void merge(List*A, List*B) {	//merge �Ŀ��� B�� ������ A�� ��ħ
	Node *prenode = A->tail->next;
	Node *pronode = B->tail->next;
	A->countIndex += B->countIndex;
	A->tail->next = pronode;
	B->tail->next = prenode;
	A->tail = B->tail;
	prenode = A->tail->next;
	free(B);
	//printf("\n\n%d", prenode->data);
	//
	//int count = 0;
	//for (int i = 0; i < 100; i++) {
	//	count++;
	//	printf("%d ", count);
	//	printf("%d\n\n", prenode->data);
	//	prenode = prenode->next;
	//}








	//printf("\n%d", pronode->data);
	//pronode = pronode->next;
	//printf("\n%d", pronode->data);
	//if (A == NULL) return B;
	//else if (B == NULL) return A;
	//int c = A->countIndex;
	//for (int i = 0; i < c; i++)
	//{
	//	prenode = prenode->next;
	//	printf("%d", pronode->data);
	//}
	//prenode->next = B->tail;
	//c = B->countIndex;
	//for (int i = 0; i < c; i++)
	//{
	//	prenode = prenode->next;
	//	A->countIndex++;
	//}
	//pronode->next = prenode->next;
	//printf("\n%d", prenode->next);
	//printf("\n%d", A->tail);
	//printf("\n%d", A->countIndex);


}

//void Finddel(List *Target_List, int item)//���񱳷� ����(��λ���)
//{
//	int c = 0;
//	Node *Cur = Target_List->tail->next;
//	int i = 1;
//	while (i != Target_List->countIndex+1)
//	{
//		if (Cur->data == item)
//		{
//			c = 1;
//			DelNode(Target_List, i);
//			return Finddel(Target_List, item);			// �����Ұ� �ִ°�� ���ֳ� �ٽ��ѹ� Ȯ��.
//		}		
//		i++;
//		Cur = Cur->next;
//	}
//}

void Finddel(List *list, int item)//���񱳷� ����(��λ���)
{
	Node *delNode = list->tail;
	Node *preNode = list->tail;
	int i = 0;
	while (i != list->countIndex + 3)
	{
		delNode = preNode->next;
		if (delNode->data == item)
		{
			preNode->next = delNode->next;
			if (i == list->countIndex - 1)
			{
				list->tail = preNode; // ���������ΰ�� ���� ����
			}
			free(delNode);
			list->countIndex--;
			return Finddel(list, item);			// �����Ұ� �ִ°�� ���ֳ� �ٽ��ѹ� Ȯ��.
		}
		preNode = preNode->next;
		i++;
	}
}


int main() {
	List* A;
	List* B;
	List* C;
	Node node;
	A = CreateList();
	B = CreateList();

	int f;
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
		AddNode(A, node);
	}
	while (EOF != fscanf(fp2, "%d", &f)) {
		node.data = f;
		AddNode(B, node);
	}
	fclose(fp1);
	fclose(fp2);
	//display(A);
	//printf("\n");
	//display(B);
	merge(A, B);
	//printf("\n");
	//printf("\n");
	display(A);
	printf("\n");
	//printf("\n");



	FILE* fp3 = fopen("./C.txt", "r");
	while (EOF != fscanf(fp3, "%d", &f)) {
		int d = f;
		//DelNode(A, d);
		Finddel(A, d); // C.txt�� ���ڸ� �񱳷� ã�°��
		//printf("\n");
		//display(A);
	}
	fclose(fp3);


	//printf("\n");
	//printf("\n");
	//printf("\n");
	display(A);

	// ����Ʈ A, B ���ļ� ����ϱ�












	// C.txt �Է¹ް� �ش��ϴ� ������ ������� ����

	return 0;
}

