#include<stdio.h>
#include<stdlib.h>

typedef int Element;
typedef struct LinkedNode {
	Element data;
	struct LinkedNode* link;
} Node;

Node* head = NULL;

void init_list() { head = NULL; }			//초기화
int is_empty() { return head == NULL; }		//비었니?
Node* get_entry(int pos) {					//index peek
	Node* p = head;
	int i;
	for (i = 0; i < pos; i++, p = p->link)	//pos (=index) 만큼 들어가서 노드 반환, 그 전에 NULL 만나면 NULL 반환
		if (p == NULL)
			return NULL;
	return p;
}
int size() {
	Node* p;
	int count = 0;
	for (p = head; p != NULL; p = p->link)
		count++;
	return count;
}
void replace(int pos, Element val) {		//원하는 index의 값을 바꾸고 싶어요
	Node* node = get_entry(pos);
	if (node != NULL)
		node->data = val;
}
Node* find(Element e) {						//값을 가진 놈 탐색, 맨 뒤에꺼만 찾음
	Node* p;
	for (p = head; p != NULL; p = p->link)
		if (p->data == e)
			return p;
	return NULL;
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
void clear_list() {
	while (is_empty() == 0)
		delete(0);
}
void print_list(char* msg) {
	Node* p;
	printf("%s[%2d]: ", msg, size());
	for (p = head; p != NULL; p = p->link)
		printf("%2d ", p->data);
	printf("\n");
}

int main(void)
{
	init_list();
	insert(0, 10);
	insert(0, 20);
	insert(1, 30);
	insert(size(), 40);
	insert(2, 50);
	print_list("단순 연결리스트로 구현한 List(삽입x5)");
	
	replace(2, 90);
	print_list("단순 연결리스트로 구현한 List(교체x1)");

	delete(2);
	delete(size() - 1);
	delete(0);
	print_list("단순 연결리스트로 구현한 List(삭제x3)");

	clear_list();
	print_list("단순 연결리스트로 구현한 List(청소)");

}