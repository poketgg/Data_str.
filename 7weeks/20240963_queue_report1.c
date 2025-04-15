#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#define SIZE 30

typedef struct {
	int data[SIZE];
	int front; // 큐의 첫번째 요소 인덱스
	int rear; // 큐의 마지막 요소 인덱스  
}LinearQueue;

void initQueue(LinearQueue* q);
void printQueue(LinearQueue q);
bool isEmpty(LinearQueue* q);
bool isFull(LinearQueue* q);
bool enqueue(LinearQueue* q, int value);
int dequeue(LinearQueue* q);

int main(void) {
	LinearQueue q;
	initQueue(&q);

	int menu_num = 0;
	int num;
	while (menu_num != 4) {
		printf("===== M  E  N  U =====\n");
		printf("사용할 기능을 선택하시오.\n");
		printf("1. 삽입\n");
		printf("2. 삭제\n");
		printf("3. 큐 데이터 출력\n");
		printf("4. 종료\n");

		scanf("%d", &menu_num);
		
		Sleep(300);
		system("cls");
		Sleep(300);

		switch (menu_num) {
		case 1:
			printf("1. 삽입을 선택.\n");
			printf(" ㄴ 삽입할 숫자 입력 > ");
			scanf("%d", &num);
			enqueue(&q, num);
			Sleep(500);
			system("cls");
			break;
		case 2:
			printf("2. 삭제를 선택.\n");
			dequeue(&q);
			printf(" ㄴ 데이터가 삭제되었습니다.");
			Sleep(500);
			system("cls");
			break;
		case 3:
			printf("3. 큐 데이터 출력을 선택.\n");
			printQueue(q);
			break;

		case 4:
			printf("4. 종료를 선택.\n");
			printf(" ㄴ 프로그램이 종료됩니다..");
			break;
			
		default:
			printf("잘못된 숫자를 입력하셨습니다. 다시 입력해주세요.");
			Sleep(500);
			system("cls");
			break;
		}
	}
	
	return 0;
}

void initQueue(LinearQueue* q) {
	q->front = 0;
	q->rear = -1; // rear를 -1로 설정, 첫번째 삽입시 0이 되도록 함,
}

void printQueue(LinearQueue q) {
	for (int i = q.front; i <= q.rear; i++) {
		if (q.data[i] != 0)
			printf("%d ", q.data[i]);
		if (i == 5) {
			printf("\n");
		}
	}
	printf("\n");
	
}

bool isEmpty(LinearQueue* q) {
	return q->rear < q->front; //rear가 front보다 작으면 비어있음.
}

bool isFull(LinearQueue* q) {
	return q->rear == SIZE - 1; //rear가 배열 끝에 도달하면 가득 참. (맨끝 = size -1 // 0부터 시작이므로)
}

bool enqueue(LinearQueue* q, int value) {
	if (isFull(q)) {
		printf("큐가 가득참. \n");
		return false;
	}
	q->rear++;
	q->data[q->rear] = value; //rear 위치에 데이터 추가

	return true;
}

int dequeue(LinearQueue* q) {
	if (isEmpty(q)) {
		printf("큐가 비어있음. \n");
		initQueue(&q);
		return -1;// 큐가 비어있을때 -1 반환.
	}
	int value = q->data[q->front];
	q->front++;
	return value;
}
