#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

int is_empty() { return head == NULL; }		//비었니?
void init_list() { head = NULL; }			//초기화
void my_fflush() { while (getchar() != '\n'); }

Node* get_entry(int pos) {					//index peek
	Node* p = head;
	int i;
	for (i = 0; i < pos; i++, p = p->link)	//pos (=index) 만큼 들어가서 노드 반환, 그 전에 NULL 만나면 NULL 반환
		if (p == NULL)
			return NULL;
	return p;
}
Node* remove_next(Node* prev) {				//index pop? find랑 씀?
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
void insert_next(Node* before, Node* node) {		//before->link가 before 앞엣놈 (before가 첫 노드면 before->link = NULL이니까)
	if (node != NULL) {
		node->link = before->link;					//before가 가리키는 놈을 새 노드가 가리켜, 새 노드를 before가 가리켜
		before->link = node;
	}
}
void insert(int pos, Element val) {					//pos 앞에놈 불러다가 새 노드를 가리키게 만드는 것
	Node* new_node, * prev;
	new_node = (Node*)malloc(sizeof(Node));
	new_node->data = val;
	new_node->link = NULL;

	if (pos == 0) {				//첫 요소면 새 노드가 NULL 가리키고, head가 그 놈 가리키고
		new_node->link = head;
		head = new_node;
	}
	else {
		prev = get_entry(pos - 1);			//원하는 index 앞 노드 가져와
		if (prev != NULL)
			insert_next(prev, new_node);	//prev가 new_node를 가리키게 해주세요
		else free(new_node);
	}
}
void replace(int pos, Element val) {		//원하는 index의 값을 바꾸고 싶어요
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
void display(FILE* fp)
{
	int i = 0;
	Node* p;
	for (p = head; p != NULL; p = p->link, i++) {
		fprintf(stderr, "%3d: ", i);
		fprintf(fp, "%s", p->data.str);							//fprintf(파일, 자료형, 쓸 거) = 파일에 출력
	}
}

void main() {
	char command;
	int pos;
	char text[MAX_CHAR_PER_LINE];														//찾을 단어
	char ftext[2][MAX_CHAR_PER_LINE];
	Line line;
	FILE* fp;
	init_list();
	do {
		printf("[메뉴선택] i-입력, d-삭제, r-변경, p-출력, l-파일읽기, s-저장, f-단어 찾기, q-종료=>");
		command = getchar();
		switch (command) {
		case 'i':
			printf("  입력행 번호:");
			scanf("%d", &pos);
			printf("  입력행 내용:");
			my_fflush();
			fgets(line.str, MAX_CHAR_PER_LINE, stdin);
			insert(pos, line);
			break;
		case 'd':
			printf("  삭제행 번호:");
			scanf("%d", &pos);
			delete(pos);
			break;
		case 'r':
			printf("  변경행 번호:");
			scanf("%d", &pos);
			printf("  변경행 내용:");
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
		case 'p': display(stdout); break;
		case 'f':
			printf("찾을 단어 :");
			scanf("%s", text);
			fp = fopen("Test.txt", "r");
			if (fp != NULL) 
			{
				char tmp[MAX_CHAR_PER_LINE] = "";
				while (1)
				{
					fscanf(fp, "%s", ftext[0]);
					fscanf(fp, "%s", ftext[1]);
					if (strcmp(tmp, ftext[0]) == 0)
					{		//막줄 끝나면 종료
						break;
					}
					strcpy(tmp, ftext[0]);
					int marking ;
					marking = strcmp(ftext[1], text);			//같으면 0
					if (marking != 0) 
					{
						marking = strcmp(ftext[0], text);
					}
					if (marking == 0)
					{
						printf("찾은 단어 : %s %s\n", ftext[0], ftext[1]);
					}
					
				}
				fclose(fp);
			}
			break;
		}
		my_fflush();
	} while (command != 'q');

	return 0;
}