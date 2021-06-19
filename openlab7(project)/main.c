#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct _student {
	char id[10];
	char name[40];
	char course[40];
	int score;
} STUDENT;

typedef struct _treenode {
	STUDENT key;
	struct _treenode *left, *right;
} TreeNode;

int InsertNode(TreeNode* root, STUDENT key);
TreeNode* NewNode(STUDENT key);
int DeleteNode(TreeNode* root, char *id);
void SearchCourse(TreeNode* node, char *course);
void SearchCourseRecursive(TreeNode* node, char *course, int *cnt, int *sum);
void SearchName(TreeNode* node, char *name);
int SearchNameRecursive(TreeNode *node, char *name);
int SearchID(TreeNode* node, char *id);
int SearchIDRecursive(TreeNode* node, char *id);
void printStudent(STUDENT key);
void PrintNode(TreeNode* root);
void PrintNodeRecursive(TreeNode* node);
void SaveNode(TreeNode* root, char* filename);
void SaveNodeRecursive(TreeNode* node, FILE *fp);

int main() {
	TreeNode *root = NULL;
	STUDENT tmp;
	int i, n;

	FILE *fp = NULL;
	fp = fopen("input.txt", "r");

	if (fp == NULL) {
		printf("���� �� ����.");
	}
	else {
		while (EOF != fscanf(fp, "%s %s %s %d", tmp.id, tmp.name, tmp.course, &tmp.score)) {
			if (root == NULL) {
				root = NewNode(tmp);
			}
			else {
				InsertNode(root, tmp);
			}
		}
	}
	fclose(fp);
	int menu = 0, x;
	char value[128];

	while (menu != -1) {
		printf("-- �޴� --\n");
		printf("-1. ����\n");
		printf("1. �л� ����\n");
		printf("2. �л� ����\n");
		printf("3. Course �˻�\n");
		printf("4. Name �˻�\n");
		printf("5. id �˻�\n");
		printf("�Է� : ");
		scanf("%d", &menu);


		if (menu == 1) {
			printf("������ �л� �Է� (id name course score: ");
			scanf("%s %s %s %d", tmp.id, tmp.name, tmp.course, &tmp.score);
			x = InsertNode(root, tmp);
			if (x == 1) {
				printf("�����Դϴ�.\n");
			}
		}

		else if (menu == 2) {
			printf("������ �л� id �Է� : ");
			scanf("%s", value);
			DeleteNode(root, value);
		}

		else if (menu == 3) {
			printf("Course �Է� : ");
			scanf("%s", value);
			SearchCourse(root, value);
		}
		else if (menu == 4) {
			printf("Name �Է� : ");
			scanf("%s", value);
			SearchName(root, value);
		}
		else if (menu == 5) {
			printf("ID �Է� : ");
			scanf("%s", value);
			SearchID(root, value);
		}

	}
	PrintNode(root);
	SaveNode(root, "output.txt");

	return 0;
}

int InsertNode(TreeNode* root, STUDENT key) {
	// a = �θ� ���, n = ���� ���
	TreeNode *a, *n;

	a = NULL;

	//Ž���ؼ� ���� �������� �˾ƺ���
	n = root;
	while (1) {
		if (strcmp(n->key.id, key.id) > 0) {
			if (n->left == NULL) {
				n->left = NewNode(key);
				return 1;
			}
			else {
				n = n->left;
			}
		}
		else if (strcmp(n->key.id, key.id) < 0) {
			if (n->right == NULL) {
				n->right = NewNode(key);
				return 1;
			}
			else {
				n = n->right;
			}
		}
		else {
			printf("id �ߺ��Դϴ�.(���� �Ұ����մϴ�.)\n");
			return 0;
		}
		if (strcmp(n->key.id, key.id) == 0) {
			printf("id �ߺ��Դϴ�.(���� �Ұ����մϴ�.)\n");
			return 0;
		}
	}
}


TreeNode* NewNode(STUDENT key) {
	TreeNode *b = (TreeNode *)malloc(sizeof(TreeNode));
	if (b == NULL) return 0;

	//����
	memcpy(&(b->key), &key, sizeof(STUDENT));
	b->left = b->right = NULL;
	return b;
}



int DeleteNode(TreeNode* root, char* id) {

	TreeNode* a, *c, *n, *s, *s_;

	a = NULL;
	n = root;

	while (n != NULL && strcmp(n->key.id, id) != 0) {
		a = n;
		if (strcmp(id, n->key.id) < 0) {
			n = n->left;
		}
		else {
			n = n->right;
		}
	}



	if (n == NULL) {
		printf("��� ������ �Ұ����մϴ�.");
		return 0;
	}

	//���ϳ��
	if (n->left == NULL && n->right == NULL) {

		if (a != NULL) {
			if (a->left == n) {
				a->left = NULL;
			}
			else {
				a->right = NULL;
			}
		}

		else {
			root->left = NULL;
			root->right = NULL;
		}
	}
	//�ڽ� �ϳ�
	else if ((n->left == NULL) || (n->right == NULL)) {

		if (n->left != NULL) {
			c = n->left;
		}

		else {
			c = n->right;
		}


		if (a != NULL) {
			if (a->left == n) {
				a->left = c;
			}
			else {
				a->right = c;
			}
		}

		else {
			root->key = c->key;
			root->left = c->left;
			root->right = c->right;
		}
	}
	//�ڽ� ��
	else {
		s_ = n;
		s = n->right;

		while (s->left != NULL) {
			s_ = s;
			s = s->left;
		}

		if (s_->left == s) {
			s_->left = s->right;
		}

		else {
			s_->right = s->right;
		}

		n->key = s->key;
		n = s;
	}
	printf("�����Դϴ�.");
	return 1;
}


void SearchCourse(TreeNode* node, char *course) {
	printf("%s ������ ã���ϴ�.\n", course);
	int cnt = 0;
	int sum = 0;

	SearchCourseRecursive(node, course, &cnt, &sum);
	if (cnt == 0) {
		printf("�ش� ������ ��� �л��� �����ϴ�.\n");
	}
	else {
		printf("���� �ο� : %d��\n", cnt);
		printf("��� ���� : %.2f��\n", (float)sum / cnt);
	}
}

void SearchCourseRecursive(TreeNode* node, char *course, int *cnt, int *sum) {
	if (node == NULL) {
		return;
	}
	if (strcmp(node->key.course, course) == 0) {
		printStudent(node->key);
		*cnt += 1;
		*sum += node->key.score;
	}
	SearchCourseRecursive(node->left, course, cnt, sum);
	SearchCourseRecursive(node->right, course, cnt, sum);
}


void SearchName(TreeNode* node, char *name) {
	SearchNameRecursive(node, name);
}

int SearchNameRecursive(TreeNode *node, char *name) {
	if (node == NULL) {
		return;
	}
	if (strcmp(node->key.name, name) == 0) {
		printStudent(node->key);
	}

	SearchNameRecursive(node->left, name);
	SearchNameRecursive(node->right, name);
}


int SearchID(TreeNode* node, char *id) {
	if (SearchIDRecursive(node, id)) {
		printf("�л��� ã�ҽ��ϴ�.\n");
		return 1;
	}
	else {
		printf("�л��� ã�� ���߽��ϴ�.\n");
		return 0;
	}
}
int SearchIDRecursive(TreeNode* node, char *id) {
	if (node == NULL) {
		return 0;
	}
	if (strcmp(node->key.id, id) == 0) {
		printStudent(node->key);
		return 1;
	}
	else if (SearchIDRecursive(node->left, id) == 1) {
		return 1;
	}
	else if (SearchIDRecursive(node->right, id) == 1) {
		return 1;
	}
	return 0;
}


void printStudent(STUDENT key) {
	printf("ID: %s, Name: %s, Course: %s, score: %d\n", key.id, key.name, key.course, key.score);
}

void PrintNode(TreeNode* root) {
	PrintNodeRecursive(root);
}
void PrintNodeRecursive(TreeNode* node) {
	if (node == NULL) {
		return;
	}
	printStudent(node->key);
	PrintNodeRecursive(node->left);
	PrintNodeRecursive(node->right);
}

void SaveNode(TreeNode* root, char* filename) {
	FILE *fp = fopen(filename, "w");
	SaveNodeRecursive(root, fp);
	fclose(fp);
}
void SaveNodeRecursive(TreeNode* node, FILE *fp) {
	if (node == NULL) {
		return;
	}
	fprintf(fp, "%s %s %d\n", node->key.id, node->key.name, node->key.score);
	SaveNodeRecursive(node->left, fp);
	SaveNodeRecursive(node->right, fp);
}