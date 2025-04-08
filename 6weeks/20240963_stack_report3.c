#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
	int data[MAX];
	int top;
} Stack;

void initStack(Stack* s);
int isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
int precedence(char op);
int infixToPostfix(char* infix, char* postfix);
int evaluatePostfix(char* postfix);


int main(void) {
	char infix[MAX];
	char postfix[MAX];
	int result = 0;

	printf("중위 표기식을 입력 > ");
	gets(infix);

	result = infixToPostfix(infix, postfix);

	printf("후위 표기식 : %s\n", postfix);
	printf("후위 표기식 계산 결과 : %d\n", result);

	return 0;

}
//스택 초기화
void initStack(Stack* s) {
	s->top = -1;
}

// 스택 비었는지 확인
int isEmpty(Stack* s) {
	return s->top == -1;
}

//스택에 요소 추가
void push(Stack* s, int value) {
	s->data[++(s->top)] = value;
}

// 스택 요소 제거
int pop(Stack* s) {
	if (isEmpty(s)) return '\0';
	return s->data[(s->top)--];
}

// 스택 최상단 요소 반환
int peek(Stack* s) {
	if (isEmpty(s)) return '\0';
	return s->data[s->top];
}

// 연산자 우선순위 설정
int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return -1;  // 여는 괄호는 우선순위 비교 대상 아님
}

//중위 표기식 -> 후위표기식으로 변환
int infixToPostfix(char* infix, char* postfix) {
	Stack s;
	initStack(&s);
	int j = 0;

	for (int i = 0; infix[i] != '\0'; i++) {
		char ch = infix[i];

		//1. 피연산자 (알파벳 or 숫자)
		if (isalpha(ch) || isdigit(ch)) {
			postfix[j++] = ch;
		}
		//2. 여는 괄호 '('
		else if (ch == '(') {
			push(&s, ch);
		}
		//3. 닫는 괄호 ')'
		else if (ch == ')') {
			while (!isEmpty(&s) && peek(&s) != '(') {
				postfix[j++] = pop(&s); //여는 괄호 전까지 pop
			}
			pop(&s); // 여는괄호 제거
		}
		//4. 연산자
		else {
			while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
				postfix[j++] = pop(&s); //우선순위 높은순으로 pop
			}
			push(&s, ch);
		}


	}

	//스택에 남은 연산자를 후위표기식에 추가
	while (!isEmpty(&s)) {
		postfix[j++] = pop(&s);
	}
	postfix[j] = '\0';

	// 후위표기식 계산함수 호출
	return evaluatePostfix(postfix);
}

// 후위표기식 계산 함수
int evaluatePostfix(char* postfix) {
	Stack s;
	initStack(&s); // 계산용 스택 초기화

	for (int i = 0; postfix[i] != '\0'; i++) {
		char ch = postfix[i];

		//1. 피연산자 (숫자)
		if (isdigit(ch)) {
			//문자열로 된 숫자 정수로 변환하여 push
			push(&s, ch - '0');
		}

		//2. 연산자
		else {
			int b = pop(&s); //두번째 피연산자 (스택 최상단)
			int a = pop(&s); //첫번째 피연산자
			int result = 0;

			switch (ch) {
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				result = a / b;
				break;

			default:
				printf("Invaild operator Encountered/.\n");
				exit(1);
			}

			// 연산결과를 스택에 push
			push(&s, result);
		}
	}
	//스택에 남은 최종결과 반환
	return pop(&s);
}
