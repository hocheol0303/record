#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	if (p != NULL) {
		printf("[%d] ", p->data);
		preOrder(p->left);
		preOrder(p->right);
	}
}
void inOrder(TNode* p) {
	if (p != NULL) {
		inOrder(p->left);
		printf("[%d] ", p->data);
		inOrder(p->right);
	}
}
void postOrder(TNode* p) {
	if (p != NULL) {
		postOrder(p->left);
		postOrder(p->right);
		printf("[%d] ", p->data);
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
			printf("[%d] ", n->data);
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

	if (t == NULL) return 0;
	TNode* Left, * Right;
	Left = t->left;
	Right = t->right;
	return t->data + data_sum(Left) + data_sum(Right);
}
TNode* search(TNode* n, int key)
{
	if (n == NULL) return NULL;
	else if (key == n->data) return n;
	else if (key < n->data) return search(n->left, key);
	else return search(n->right, key);
}
TNode* search_iter(TNode* n, int key)
{
	while (n != NULL)
	{
		if (key == n->data) return n;
		else if (key < n->data) n = n->left;
		else n = n->right;
	}
	return NULL;
}
int insert(TNode* r, TNode* n)
{
	if (n->data == r->data) return 0;
	else if (n->data < r->data)
	{
		if (r->left == NULL) r->left = n;
		else insert(r->left, n);
	}
	else
	{
		if (r->right == NULL) r->right = n;
		else insert(r->right, n);
	}
	return 1;
}
void delete(TNode* parent, TNode* node)
{
	TNode* child, * succ, * succp;
	if ((node->left == NULL && node->right == NULL))
	{
		if (parent == NULL) root = NULL;
		else {
			if (parent->left == node) parent->left = NULL;
			else parent->right = NULL;
		}
	}
	else if (node->left == NULL || node->right == NULL)
	{
		child = (node->left != NULL) ? node->left : node->right;
		if (node == root) root = child;
		else {
			if (parent->left == node)parent->left = child;
			else parent->right = child;
		}
	}
	else {
		succp = node;
		succ = node->right;
		while (succ->left != NULL) {
			succp = succ;
			succ = succ->left;
		}
		if (succp->left == succ) succp->left = succ->right;
		else succp->right = succ->right;
		node->data = succ->data;
		node = succ;
	}
	free(node);
}
void search_BST(int key)
{
	TNode* n = search(root, key);
	if (n != NULL) printf("[탐색연산] : 성공 [%d] = 0x%x\n", n->data, n);
	else printf("[탐색연산] : 실패: No %d!\n", key);
}
void insert_BST(int key)
{
	TNode* n = create_tree(key, NULL, NULL);
	if (is_empty_tree()) root = n;
	else if (insert(root, n) == 0) free(n);
}

void delete_BST(int key)
{
	TNode* parent = NULL;
	TNode* node = root;

	if (node == NULL) return;
	while (node != NULL && node->data != key) {
		parent = node;
		node = (key < node->data) ? node->left : node->right;
	}
	if (node == NULL)printf(" Error: key is not in ther tree!\n");
	else delete(parent, node);
}

int main(void)
{
	printf("[삽입 연산] : 35 18 7 26 12 3 68 22 30 99");
	init_tree();
	insert_BST(35);
	insert_BST(18);
	insert_BST(7);
	insert_BST(26);
	insert_BST(12);
	insert_BST(3);
	insert_BST(68);
	insert_BST(22);
	insert_BST(30);
	insert_BST(99);

	printf("\n   In-Order : "); inOrder(root);
	printf("\n  Pre-Order : "); preOrder(root);
	printf("\n Post-Order : "); postOrder(root);
	printf("\nLevel-Order : "); levelOrder(root);

	printf("\n 노드의 개수 = %d\n", count_node(root));
	printf(" 단말의 개수 = %d\n", count_leaf(root));
	printf(" 트리의 높이 = %d\n", calc_height(root));

	search_BST(26);
	search_BST(25);

	printf("\noriginal bintree: LevelOrder: "); levelOrder(root);
	delete_BST(3);
	printf("\ncase1: < 3> 삭제: LevelOrder: "); levelOrder(root);
	delete_BST(68);
	printf("\ncase2: <68> 삭제: LevelOrder: "); levelOrder(root);
	delete_BST(18);
	printf("\ncase3: <18> 삭제: LevelOrder: "); levelOrder(root);
	delete_BST(35);
	printf("\ncase4: <35> 삭제: LevelOrder: "); levelOrder(root);
	
	printf("\n 노드의 개수 = %d\n", count_node(root));
	printf(" 단말의 개수 = %d\n", count_leaf(root));
	printf(" 트리의 높이 = %d\n", calc_height(root));
	
	return 0;
}