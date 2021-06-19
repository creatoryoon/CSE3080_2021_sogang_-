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

int main() {
    TreeNode *root = NULL;
    STUDENT tmp;
    int i, n;

    FILE *fp = NULL;
    fp = fopen("input.txt", "r");

    if(fp == NULL) {
        printf("���� �� ����.");
    }
    else {
        for (i=0;i<15;i++) {
            fscanf(fp,"%s %s %s %d", tmp.id, tmp.name, tmp.course, &tmp.score);
            if (root == NULL) {
                root = NewNode(tmp);
            } else {
                InsertNode(root, tmp);
            }
        }
    }

    int menu = 0;
    char value[128];

    while (menu != -1) {
        printf("-1. ����\n");
        printf("1. Course �˻�\n");
        printf("2. ID �˻�\n");
        printf("3. Name �˻�\n");
        printf("�Է� : ");
        scanf("%d", &menu);

        if(menu == 1) {
            printf("Course �Է� : ");
            scanf("%s", value);
            SearchCourse(root, value);
        } else if(menu == 2) {
            printf("ID �Է� : ");
            scanf("%s", value);
            SearchID(root, value);
        } else if (menu == 3) {
            printf("Name �Է� : ");
            scanf("%s", value);
            SearchName(root, value);
        }
    }

    return 0;
}

int InsertNode(TreeNode* root, STUDENT key) {
    // a = �θ� ���, b = ���ο� ���, n = ���� ���
    TreeNode *a, *n;

    a = NULL;

    //Ž���ؼ� ���� �������� �˾ƺ���
    n = root;
    while(n != NULL) {
        if (strcmp(n->key.id, key.id) == 0) {
            printf("�ߺ� id\n");
            return 0;
        }

        a = n;
        if (strcmp(key.id, n->key.id) > 0) {
            n = n->left;
        }
        else {
            n = n->right;
        }
    }

    //item�� Ʈ���ȿ� �����Ƿ� ���� ����
    TreeNode *b = NewNode(key);

    //�θ���� ��ũ ����
    if(strcmp(key.id, a->key.id) > 0) {
        a->left = b;
    }

    else {
        a->right = b;
    }
    return 1;
}

TreeNode* NewNode(STUDENT key) {
    TreeNode *b = (TreeNode *)malloc(sizeof(TreeNode));
    if(b == NULL) return 0;

    //������ ����
    memcpy(&(b->key), &key, sizeof(STUDENT));
    b->left = b->right = NULL;
    return b;
}
int DeleteNode(TreeNode* root, char *id) {
    TreeNode *a, *n;

    a = NULL;
    n = root;
    //key�� ���� ��� n�� Ž���Ѵ�.
    while(n != NULL && n->key.id != *id) {
        a = n;
        n = (strcmp(id, n->key.id) > 0)? n->left:n->right;
    }

    //Ž���� ����� �������� t�� NULL�̸� Ʈ���ȿ� key�� ����

    if(n == NULL){
        printf("�Ұ����մϴ�.");
        return 0;
    }

    //ù��° ���:�ܸ������ ���
    if(n->left == NULL && n->right == NULL){
        // TODO
        if(a != NULL){
            //�θ����� �ڽ� �ʵ带 NULL�� �����.
            if(a->left==n) {
                a->left=NULL;
            }
            else {
                a->right=NULL;
            }
        }

        //���� �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
        else{
            root = NULL;
        }
    }
    return 1;
}


void SearchCourse(TreeNode* node, char *course) {
    printf("%s ������ ã���ϴ�.\n", course);
    int cnt = 0;
    int sum = 0;

    SearchCourseRecursive(node, course, &cnt, &sum);
    if(cnt == 0) {
        printf("�ش� ������ ��� �л��� �����ϴ�.\n");
    }
    else {
        printf("���� �ο� : %d��\n", cnt);
        printf("��� ���� : %.2f��\n", (float)sum / cnt);
    }
}

void SearchCourseRecursive(TreeNode* node, char *course, int *cnt, int *sum) {
    if(node == NULL) {
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
    if(node == NULL) {
        return 0;
    }
    if (strcmp(node->key.name, name) == 0) {
        printStudent(node->key);
        return 1;
    }
    else if(SearchNameRecursive(node->left, name) == 1) {
        return 1;
    }
    else if(SearchNameRecursive(node->right, name) == 1) {
        return 1;
    }
}


int SearchID(TreeNode* node, char *id) {
    if(SearchIDRecursive(node, id)) {
        printf("�л��� ã�ҽ��ϴ�.\n");
        return 1;
    } else {
        printf("�л��� ã�� ���߽��ϴ�.\n");
        return 0;
    }
}
int SearchIDRecursive(TreeNode* node, char *id) {
    if(node == NULL) {
        return 0;
    }
    if (strcmp(node->key.id, id) == 0) {
        printStudent(node->key);
        return 1;
    }
    else if(SearchIDRecursive(node->left, id) == 1) {
        return 1;
    }
    else if(SearchIDRecursive(node->right, id) == 1) {
        return 1;
    }
    return 0;
}


void printStudent(STUDENT key) {
    printf("ID: %s, Name: %s, score: %d\n", key.id, key.name, key.score);
}
