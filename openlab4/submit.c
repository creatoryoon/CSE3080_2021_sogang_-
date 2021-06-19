#define _CRT_SECURE_NO_WARNINGS
#define INF 99999999 //����÷ο� ����
#include<stdio.h>
#include<stdlib.h>


//------------------------��� ����
typedef struct {
	int data;
	struct Node *next;
} Node;
//----------------------------- ť ����

typedef struct {
	Node *front;
	Node *rear;
	int count;
} Queue;

void Qpush(Queue *queue, int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	if (queue->count == 0) {
		queue->front = node;
	}
	else {
		queue->rear->next = node;
	}
	queue->rear = node;
	queue->count++;
}
int Qpop(Queue *queue) {
	if (queue->count == 0) {
		printf("Queue underflow");
		return -INF;
	}
	Node *node = queue->front;
	int data = node->data;
	queue->front = node->next;
	free(node);
	queue->count--;
	return data;


}

void Qshow(Queue *queue) {
	Node *cur = queue->front;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
}


// --------------------------------���� ����
typedef struct {
	Node *top;
} Stack;
// ���� ����
void Stackpush(Stack *stack, int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = stack->top;
	stack->top = node;
}
// ���� ��
int Stackpop(Stack *stack) {
	if (stack->top == NULL) {
		printf("Stack underflow");
		return -INF;
	}
	Node *node = stack->top;
	int data = node->data;
	stack->top = node->next;
	free(node);
	return data;
}
// ���� ���
void Stackshow(Stack *stack) {
	Node *cur = stack->top;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
}





int main() {
	Queue queue;
	queue.front = queue.rear = NULL;
	queue.count = 0;

	Stack stack;
	stack.top = NULL;




	int f;
	FILE* fp = fopen("./input.txt", "r");	//----------------------------------------���� ���!--------------------
	if (fp == NULL) {	//���� ������ �ٷ� ����.
		printf("Can't find file");
		return 0;
	}

	
	while (!feof(fp)) {
		fscanf(fp, "%d", &f);
		if (f == 0) {
			fscanf(fp, "%d", &f);
			Qpush(&queue, f);
			Stackpush(&stack, f);
		}
		else if (f == 1) {
			Qpop(&queue);
			Stackpop(&stack);

		}

	}
	fclose(fp);


	Stackshow(&stack);
	printf("\n");
	Qshow(&queue);
	return 0;
}