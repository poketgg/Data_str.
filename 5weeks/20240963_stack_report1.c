#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
	char data[MAX];
	int top;
	int capacity;
}Stack;

void initStack(Stack* s, int initialSize);
int isEmpty(Stack* s);
int isFull(Stack* s);
void push(Stack* s, char str);
int pop(Stack* s);
void display(Stack* s);
void reverseString(Stack* s, char str[]);



int main(void) {
	Stack s;
	initStack(&s, 100);
	char str[100] = "";

	printf("100자 이하의 문자 입력 > ");
	scanf("%s", str);

	reverseString(&s, str);

	display(&s);

}

void initStack(Stack* s, int initialSize) {
	s->top = -1;
	s->capacity = initialSize;
}

int isEmpty(Stack* s) {
	return s->top == -1;
}

int isFull(Stack* s) {
	return s->top == s->capacity - 1;
}


void push(Stack* s, char str) {
	if (isFull(s)) {
		printf("Stack OverFlow!\n");
		return;
	}
	s->data[++(s->top)] = str;
}

int pop(Stack* s) {
	if (isEmpty(s)) {
		printf("스택 언더플로우! 제거할 요소가 없습니다.\n");
		return -1;
	}
	printf("제거된 값 : %d\n", s->data[s->top]);
	return s->data[(s->top)--];
}

int peek(Stack* s) {
	if (isEmpty(s)) {
		printf("스택이 비어있습니다. 확인할 값이 없습니다.\n");
		return -1;
	}
	printf("최상단 값 : %d\n", s->data[s->top]);
}

void display(Stack* s) {
	if (isEmpty(s)) {
		printf("스택이 비어있습니다!\n");
		return;
	}
	printf("스택 내용 : ");
	for (int i = 0; i <= s->top; i++) {
		printf("%c", s->data[i]);
	}
	printf("\n");
}

void reverseString(Stack* s, char str[]) {
	for (int i = 99; i > -1; i--) {
		if (str[i] != '\0')
			push(s, str[i]);
	}
}
