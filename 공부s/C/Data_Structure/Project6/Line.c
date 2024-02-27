#include<stdio.h>
#include<stdlib.h>

#define MAX_CHAR_PER_LINE 1000

typedef struct Line {
	char str[MAX_CHAR_PER_LINE];
} Line;

typedef Line Element;

typedef struct LinkedNode {
	Element data;
	struct LinkedNode* link;
}Node;

Node* head;
int is_empty() { return head == NULL; }		//�����?

Node* get_entry(int pos) {					//index peek
	Node* p = head;
	int i;
	for (i = 0; i < pos; i++, p = p->link)	//pos (=index) ��ŭ ���� ��� ��ȯ, �� ���� NULL ������ NULL ��ȯ
		if (p == NULL)
			return NULL;
	return p;
}
Node* remove_next(Node* prev) {				//index pop? find�� ��?
	Node* removed = prev->link;
	if (removed != NULL)
		prev->link = removed->link;
	return removed;
}
void delete(int pos) {
	Node* prev, * removed;
	if (pos == 0 && is_empty() == 0) {
		removed = head;
		head = head->link;
		free(removed);
	}
	else {
		prev = get_entry(pos - 1);
		if (prev != NULL) {
			removed = remove_next(prev);
			free(removed);
		}
	}
}
void insert_next(Node* before, Node* node) {		//before->link�� before �տ��� (before�� ù ���� before->link = NULL�̴ϱ�)
	if (node != NULL) {
		node->link = before->link;					//before�� ����Ű�� ���� �� ��尡 ������, �� ��带 before�� ������
		before->link = node;
	}
}
void insert(int pos, Element val) {					//pos �տ��� �ҷ��ٰ� �� ��带 ����Ű�� ����� ��
	Node* new_node, * prev;
	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = val;
	new_node->link = NULL;

	if (pos == 0) {				//ù ��Ҹ� �� ��尡 NULL ����Ű��, head�� �� �� ����Ű��
		new_node->link = head;
		head = new_node;
	}
	else {
		prev = get_entry(pos - 1);			//���ϴ� index �� ��� ������
		if (prev != NULL)
			insert_next(prev, new_node);	//prev�� new_node�� ����Ű�� ���ּ���
		else free(new_node);
	}
}
void replace(int pos, Element val) {		//���ϴ� index�� ���� �ٲٰ� �;��
	Node* node = get_entry(pos);
	if (node != NULL)
		node->data = val;
}
int size() {
	Node* p;
	int count = 0;
	for (p = head; p != NULL; p = p->link)
		count++;
	return count;
}
void init_list() { head = NULL; }			//�ʱ�ȭ


void display(FILE* fp)
{
	int i = 0;
	Node* p;
	for (p = head; p != NULL; p = p->link, i++) {
		fprintf(stderr, "%3d: ", i);
		fprintf(fp, "%s", p->data.str);
	}
}
void my_fflush() { while (getchar() != '\n'); }

void main() {
	char command;
	int pos;
	Line line;
	FILE* fp;
	init_list();
	do {
		printf("[�޴�����] i-�Է�, d-����, r-����, p-���, l-�����б�, s-����, q-����=>");
		command = getchar();
		switch (command) {
		case 'i':
			printf("  �Է��� ��ȣ:");
			scanf("%d", &pos);
			printf("  �Է��� ����:");
			my_fflush();
			fgets(line.str, MAX_CHAR_PER_LINE, stdin);
			insert(pos, line);
			break;
		case 'd':
			printf("  ������ ��ȣ:");
			scanf("%d", &pos);
			delete(pos);
			break;
		case 'r':
			printf("  ������ ��ȣ:");
			scanf("%d", &pos);
			printf("  ������ ����:");
			my_fflush();
			fgets(line.str, MAX_CHAR_PER_LINE, stdin);
			replace(pos, line);
			break;
		case 'l':
			fp = fopen("Test.txt", "r");
			if (fp != NULL) {
				while (fgets(line.str, MAX_CHAR_PER_LINE, fp))
					insert(size(), line);
				fclose(fp);
			}
			break;
		case 's':
			fp = fopen("Test.txt", "w");
			if (fp != NULL) {
				display(fp);
				fclose(fp);
			}
			break;
		case 'p': display(stdout);
		}
		my_fflush();
	} while (command != 'q');

	printf("20220848 ��ȣö");

	return 0;
}