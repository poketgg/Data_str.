#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char data[MAX];
    int top;
    int capacity;
} Stack;

void initStack(Stack* s, int initialSize);
int isEmpty(Stack* s);
int isFull(Stack* s);
void push(Stack* s, char ch);
char pop(Stack* s);
void checkBrackets(Stack* s, char str[]);

int main(void) {
    Stack s;
    initStack(&s, MAX);

    char str[MAX];

    printf("100자 이하의 괄호가 포함된 식/문자 입력 > ");
    fgets(str, sizeof(str), stdin);

    // 개행 문자 제거
    str[strcspn(str, "\n")] = '\0';

    checkBrackets(&s, str);

    return 0;
}


// 스택 초기화 함수
void initStack(Stack* s, int initialSize) {
    s->top = -1;
    s->capacity = initialSize;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* s) {
    return s->top == s->capacity - 1;
}

// 스택에 요소 추가
void push(Stack* s, char ch) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->data[++(s->top)] = ch;
}

// 스택에서 요소 제거
char pop(Stack* s) {
    if (isEmpty(s)) {
        return '\0';  // 비어있을 경우 null 문자 반환
    }
    return s->data[(s->top)--];
}

// 괄호 짝 검사 함수
void checkBrackets(Stack* s, char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        // 여는 괄호는 push
        if (ch == '(' || ch == '{' || ch == '[') {
            push(s, ch);
        }

        // 닫는 괄호일 경우
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(s)) {
                printf("유효하지 않은 괄호\n");
                return;
            }
            char top = pop(s);
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                printf("유효하지 않은 괄호\n");
                return;
            }
        }
    }

    // 모든 괄호가 짝이 맞고, 스택이 비어 있어야 유효
    if (isEmpty(s)) {
        printf("유효한 괄호\n");
    }
    else {
        printf("유효하지 않은 괄호\n");
    }
}
