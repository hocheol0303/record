#include<stdio.h>
#include<stdlib.h>

#define MAX_CHAR_PER_LINE 1000
typedef struct Line {
    char str[MAX_CHAR_PER_LINE];
}Line;
typedef Line Element;
typedef struct LinkedNode {
    Element data;
    struct LinkedNode* link;
}Node;
Node* head;

void init_list() { head = NULL; }
int is_empty() { return head == NULL; }
Node* get_entry(int pos)
{
    Node* p = head;
    int i;
    for (i = 0; i < pos; i++, p = p->link)
        if (p == NULL)return NULL;
    return p;
}
int size()
{
    Node* p;
    int count = 0;
    for (p = head; p != NULL; p = p->link)
        count++;
    return count;
}
void replace(int pos, Element e)
{
    Node* node = get_entry(pos);
    if (node != NULL)
        node->data = e;
}
void insert_next(Node* prev, Node* n)
{
    if (n != NULL) {
        n->link = prev->link;
        prev->link = n;
    }
}
void insert(int pos, Element val)
{
    Node* new_node, * prev;

    new_node = (Node*)malloc(sizeof(Node));
    new_node->data = val;
    new_node->link = NULL;

    if (pos == 0) {
        new_node->link = head;
        head = new_node;
    }
    else {
        prev = get_entry(pos - 1);
        if (prev != NULL)
            insert_next(prev, new_node);
        else free(new_node);
    }
}
Node* remove_next(Node* prev)
{
    Node* removed = prev->link;
    if (removed != NULL)
        prev->link = removed->link;
    return removed;
}
void delete(int pos)
{
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
void clear_list()
{
    while (is_empty() == 0)
        delete(0);
}
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

void main()
{
    char command;
    int pos;
    char text[MAX_CHAR_PER_LINE];
    Line line;
    char ftext[2][MAX_CHAR_PER_LINE];
    FILE* fp;

    init_list();
    do {
        printf("[�޴�����] i-�Է�, d-����, r-����, p-���, l-�����б�, s-����, f-�ܾ� �˻�, q-����=> ");
        command = getchar();
        switch (command) {
        case'i':
            printf("  �Է��� ��ȣ:  ");
            scanf("%d", &pos);
            printf("  �Է��� ����:  ");
            my_fflush();
            fgets(line.str, MAX_CHAR_PER_LINE, stdin);
            insert(pos, line);
            break;
        case'd':
            printf("  ������ ��ȣ:  ");
            scanf("%d", &pos);
            delete(pos);
            break;
        case'r':
            printf("  ������ ��ȣ:  ");
            scanf("%d", &pos);
            printf("  ������ ����:  ");
            my_fflush();
            fgets(line.str, MAX_CHAR_PER_LINE, stdin);
            replace(pos, line);
            break;
        case'l':
            fp = fopen("Test.txt", "r");
            if (fp != NULL) {
                while (fgets(line.str, MAX_CHAR_PER_LINE, fp))
                    insert(size(), line);
                fclose(fp);
            }
            break;
        case's':
            fp = fopen("Test.txt", "w");
            if (fp != NULL) {
                display(fp);
                fclose(fp);
            }
            break;
        case'p':
            display(stdout);
            break;
        case 'f':
            printf("ã�� �ܾ� :");
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
                    {      //���� ������ ����
                        break;
                    }
                    strcpy(tmp, ftext[0]);
                    int marking;
                    marking = strcmp(ftext[1], text);         //������ 0
                    if (marking != 0)
                    {
                        marking = strcmp(ftext[0], text);
                    }
                    if (marking == 0)
                    {
                        printf("ã�� �ܾ� : %s %s\n", ftext[0], ftext[1]);

                    }
                    my_fflush();
                } while (command != 'q');
            }
        }
    } while (command != 'q');
    return 0;
}
