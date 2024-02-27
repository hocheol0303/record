#include<stdio.h>
#include<stdlib.h>

#define MAX_QUEUE_SIZE 100

int front;
int rear;

typedef int TElement;
typedef struct BinTrNode {
	TElement data;
	struct BinTrNode* left;
	struct BinTrNode* right;
} TNode;

TNode* root = NULL;
TNode* data[MAX_QUEUE_SIZE];

void init_tree() { root = NULL; }
int is_empty_tree() { return root == NULL; }
TNode* get_root() { return root; }

TNode* create_tree(TElement val, TNode* l, TNode* r) {
	TNode* n = (TNode*)malloc(sizeof(TNode));			//mallco : stdlib
	n->data = val;
	n->left = l;
	n->right = r;
	return n;
}

void preOrder(TNode* p) {
	if(p != NULL){
		printf("[%c] ", p->data);
		preOrder(p->left);
		preOrder(p->right);
	}
}
void inOrder(TNode* p) {
	if (p != NULL) {
		inOrder(p->left);
		printf("[%c] ", p->data);
		inOrder(p->right);
	}
}
void postOrder(TNode* p) {
	if (p != NULL) {
		postOrder(p->left);
		postOrder(p->right);
		printf("[%c] ", p->data);
	}
}
////////////////////////////////////////// Queue
void error(char* str) {
	printf("%s\n", str);
	exit(1);
}

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }				//가득차도 한자리 빔
int size() { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(TNode* val)
{
	if (is_full())
		error(" 큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}

TNode* dequeue()
{
	if (is_empty())
		error(" 큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}

TNode* peek()
{
	if (is_empty())
		error(" 큐 공백 에러");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}

////////////////////////////////////////// Queue

void levelOrder()
{
	TNode* n;
	if (root == NULL) return;
	init_queue();
	enqueue(root);
	while (!is_empty())
	{
		n = dequeue();
		if (n != NULL)
		{
			printf("[%c] ", n->data);
			enqueue(n->left);
			enqueue(n->right);
		}
	}
}

int count_node(TNode* n)
{
	if (n == NULL) return 0;
	return 1 + count_node(n->left) + count_node(n->right);
}
int count_leaf(TNode* n)
{
	if (n == NULL) return 0;
	if (n->left == NULL && n->right == NULL) return 1;
	else return count_leaf(n->left) + count_leaf(n->right);
}
int calc_height(TNode* n) {
	int hLeft, hRight;
	if (n == NULL) return 0;
	hLeft = calc_height(n->left);
	hRight = calc_height(n->right);
	return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
}


int data_sum(TNode* t) 
{
	
	if (t==NULL) return 0;
	TNode* Left, *Right;
	Left = t->left;
	Right = t->right;
	return t->data + data_sum(Left) + data_sum(Right);
}

int main(void)
{
	TNode* b, * c, * d, * e, * f;
	init_tree();
	d = create_tree('D', NULL, NULL);
	e = create_tree('E', NULL, NULL);
	f = create_tree('F', NULL, NULL);
	
	b = create_tree('B', d, e);
	c = create_tree('C', f, NULL);

	root = create_tree('A', b, c);
	//아래서부터 생성

	printf("\n   In-Order : ");
	inOrder(root);
	printf("\n  Pre-Order : ");
	preOrder(root);
	printf("\n Post-Order : ");
	postOrder(root);
	printf("\nLevel-Order : ");
	levelOrder();
	printf("\n");
	printf(" 노드의 개수 = %d\n", count_node(root));
	printf(" 단말의 개수 = %d\n", count_leaf(root));
	printf(" 트리의 높이 = %d\n", calc_height(root));

	printf("%d", data_sum(root));
}