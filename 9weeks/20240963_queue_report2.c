#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  // 큐 최대 크기

// 프린터 작업 구조체
typedef struct {
    char documentName[50];  // 문서 이름
    int numPages;           // 페이지 수
} PrintJob;

// 원형 큐 구조체
typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;

//함수 프로토타입 선언 
void initQueue(PrintQueue* q);
bool isEmpty(PrintQueue* q);
bool isFull(PrintQueue* q);
bool enqueue(PrintQueue* q, char* documentName, int numPages);
PrintJob dequeue(PrintQueue* q);
void printQueue(PrintQueue* q);
void cancelJob(PrintQueue* q, const char* targetName);
void clearQueue(PrintQueue* q);

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (true) {
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 대기열 출력\n4. 종료\n");
        printf("5. 인쇄 취소\n6. 전체 대기열 초기화\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("문서 이름: ");
            scanf("%s", documentName);
            printf("페이지 수: ");
            scanf("%d", &numPages);
            enqueue(&q, documentName, numPages);
            break;
        case 2: {
            PrintJob job = dequeue(&q);
            if (strlen(job.documentName) > 0) {
                printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPages);
            }
            break;
        }
        case 3:
            printQueue(&q);
            break;
        case 4:
            printf("프로그램을 종료합니다.\n");
            return 0;
        case 5:
            printf("취소할 문서 이름: ");
            scanf("%s", documentName);
            cancelJob(&q, documentName);
            break;
        case 6:
            clearQueue(&q);
            break;
        default:
            printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
            break;
        }
    }
}

//큐 초기화
void initQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
}

// 큐가 비었는지 확인 
bool isEmpty(PrintQueue* q) {
    return q->front == q->rear;
}

//큐가 가득 찼는지 확인
bool isFull(PrintQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}

//  작업 추가 함수
bool enqueue(PrintQueue* q, char* documentName, int numPages) {
    if (numPages > 50) {
        printf("문서는 50페이지 이하여야 합니다. 추가할 수 없습니다.\n");
        return false;
    }
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }
    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPages);
    return true;
}

// 작업 처리 함수
PrintJob dequeue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다. 작업이 없습니다.\n");
        PrintJob emptyJob = { "", 0 };
        return emptyJob;
    }
    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

// 대기열 출력 함수
void printQueue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }
    printf("현재 대기 중인 작업:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("- %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}

// 특정 문서 인쇄 취소 함수
void cancelJob(PrintQueue* q, const char* targetName) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    int found = 0;
    int i = q->front;
    int count = (q->rear - q->front + SIZE) % SIZE;
    PrintJob tempQueue[SIZE];
    int tempRear = 0;

    for (int j = 0; j < count; j++) {
        if (strcmp(q->queue[i].documentName, targetName) == 0) {
            found = 1;
            printf("작업 '%s'이(가) 대기열에서 취소되었습니다.\n", targetName);
        }
        else {
            tempQueue[tempRear++] = q->queue[i];
        }
        i = (i + 1) % SIZE;
    }

    if (!found) {
        printf("해당 문서가 없습니다.\n");
        return;
    }

    q->front = 0;
    q->rear = tempRear;
    for (int k = 0; k < tempRear; k++) {
        q->queue[k] = tempQueue[k];
    }
}

//전체 대기열 초기화 함수
void clearQueue(PrintQueue* q) {
    initQueue(q);
    printf("대기열이 초기화되었습니다.\n");
}
