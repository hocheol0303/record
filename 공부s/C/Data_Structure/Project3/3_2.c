#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100

typedef struct Student {
	int id;
	char name[32];
	char dept[32];
}Student;

typedef Student Element;

Element data[MAX_STACK_SIZE];
int top;

void error(char*);
void init_stack();
int is_empty();
int is_full();
int size();
void push(Element e);
Element pop();
Element peek();
void print_stack(char*);
Student get_student(int, char*, char*);

int main(void)
{
	init_stack();
	push(get_student(2018130007, "È«±æµ¿", "ÄÄÇ»ÅÍ°øÇÐ°ú"));
	push(get_student(2018130100, "ÀÌ¼ø½Å", "±â°è°øÇÐ°ú"));
	push(get_student(2018130135, "±è¿¬¾Æ", "Ã¼À°°ú"));
	push(get_student(1998130112, "È²Èñ", "¹ýÇÐ°ú"));
	print_stack("Ä£±¸ 4¸í »ðÀÔ ÇÔ");
	
	pop();
	print_stack("Ä£±¸ 1¸í »èÁ¦ ÈÄ");
}

void error(char msg[]) {
	printf("%s\n", msg);
}

void init_stack() {
	top = -1;
}

int is_empty() {
	return top == -1;
}
int is_full() {
	return top == MAX_STACK_SIZE - 1;
}
int size() {
	return top + 1;
}
void push(Element e) {
	if (is_full == -1) {
		error("Stack ±×µæ Ã¡À½");
	}
	else {
		top += 1;
		data[top].id = e.id;
		strcpy(data[top].name, e.name);
		strcpy(data[top].dept, e.dept);
	}
}
Element pop() {
	if (is_empty == -1) {
		error("Stack ÅÖ º³À½");
	}
	else {
		return data[top--];
	}
}
Element peek() {
	if (is_empty == -1) {
		error("ÅÖ º³À½");
	}
	else {
		return data[top];
	}
}
void print_stack(char* msg) {
	printf("%s[%2d]\n", msg, top+1);
	for(int i=top; i>-1; i--)
		printf("%15s %20d %15s\n", data[top-i].dept, data[top-i].id, data[top-i].name);
}
Student get_student(int id, char *name, char* dept) {
	Student s;
	s.id = id;
	strcpy(s.dept, dept);
	strcpy(s.name, name);
	return s;
}