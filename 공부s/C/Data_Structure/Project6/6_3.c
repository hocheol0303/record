#include<stdio.h>

typedef int Element;
typedef struct DblLinkedNode {
	Element data;
	struct DblLinkedNode* prev;
	struct DblLinkedNode* next;
} Node;
Node org;
void init_list() { org.next = NULL; }
Node* get_head() { return org.next; }
int is_empty() { return get_head() == NULL; }
Node* get_entry(int pos) {
	Node* n = &org;
	int i = -1;
	for (i = -1; i < pos; i++, n = n->next)
		if (n == NULL) break;
	return n;
}
void replace(int pos, Element val) {
	Node* node = get_entry(pos);
	if (node != NULL)
		node->data = val;
}
int size() {
	Node* p;
	int count = 0;
	for (p = get_head(); p != NULL; p = p->next)
		count++;
	return count;
}
Node* find(Element val) {
	Node* p;
	for (p = get_head(); p != NULL; p = p->next)
		if (p->data == val)
			return p;
	return NULL;
}
void print_list(char* msg) {
	Node* p;
	printf("%s[%2d]: ", msg, size());
	for (p = get_head(); p != NULL; p = p->next)
		printf("%2d ", p->data);
	printf("\n");
}


int main(void)
{

}