#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE   100
int front;
int rear;

typedef char TElement;
typedef struct BinTrNode {
    TElement   data;
    struct BinTrNode* left;
    struct BinTrNode* right;
} TNode;

TNode* data[MAX_QUEUE_SIZE];
TNode* root = NULL;

void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

void init_queue() { front = rear = 0; ; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(TNode* val)
{
    if (is_full())
        error("   ť ��ȭ ����");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}
TNode* dequeue()
{
    if (is_empty())
        error("   ť ���� ����");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}

TNode* peek()
{
    if (is_empty())
        error("   ť ���� ����");
    return data[(front + 1) % MAX_QUEUE_SIZE];
}

void levelorder(TNode* root)
{
    TNode* n;
    if (root == NULL) return;
    init_queue();
    enqueue(root);
    while (!is_empty()) {
        n = dequeue();
        if (n != NULL) {
            printf("[%c] ", n->data);
            enqueue(n->left);
            enqueue(n->right);
        }
    }
}


void init_tree() { root = NULL; }
int is_empty_tree() { return root == NULL; }
TNode* get_root() { return root; }

TNode* create_tree(TElement val, TNode* l, TNode* r)
{
    TNode* n = (TNode*)malloc(sizeof(TNode));
    n->data = val;
    n->left = l;
    n->right = r;
    return n;
}

void preorder(TNode* n)
{
    if (n != NULL) {
        printf("[%c] ", n->data);
        preorder(n->left);
        preorder(n->right);
    }
}

void inorder(TNode* n)
{
    if (n != NULL) {
        inorder(n->left);
        printf("[%c] ", n->data);
        inorder(n->right);
    }
}

void postorder(TNode* n)
{
    if (n != NULL) {
        postorder(n->left);
        postorder(n->right);
        printf("[%c] ", n->data);
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

int calc_height(TNode* n)
{
    int hLeft, hRight;
    if (n == NULL) return 0;
    hLeft = calc_height(n->left);
    hRight = calc_height(n->right);
    return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
}

void main()
{
    TNode* b, * c, * d, * e, * f;
    init_tree();
    d = create_tree('D', NULL, NULL);
    e = create_tree('E', NULL, NULL);
    b = create_tree('B', d, e);
    f = create_tree('F', NULL, NULL);
    c = create_tree('C', f, NULL);
    root = create_tree('A', b, c);

    printf("\n   In-Order : ");      inorder(root);
    printf("\n  Pre-Order : ");      preorder(root);
    printf("\n Post=Order : ");      postorder(root);
    printf("\nLevel=Order : ");      levelorder(root);
    printf("\n");
    printf(" ����� ���� = %d\n", count_node(root));
    printf(" �ܸ��� ���� = %d\n", count_leaf(root));
    printf(" Ʈ���� ���� = %d\n", calc_height(root));
}