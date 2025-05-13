#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[20];              // 이름
    char phone[20];             // 전화번호
    struct Node* next;          // 다음 노드 포인터
} Node;

// 함수 선언
Node* insertLast(Node* head, const char* name, const char* phone);
void searchContact(Node* head, const char* name);
Node* deleteContact(Node* head, const char* name);
void printContacts(Node* head);
void freeList(Node* head);

int main(void) {
    Node* head = NULL;
    int menu = 0;
    char name[20];
    char phone[20];

    while (menu != 9) {
        printf("\n== 전화번호부 관리 시스템 ==\n");
        printf("1. 새로운 연락처 추가\n");
        printf("2. 연락처 검색\n");
        printf("3. 연락처 삭제\n");
        printf("4. 전화번호부 출력\n");
        printf("9. 종료\n");
        printf("> ");
        scanf("%d", &menu);

        switch (menu) {
        case 1:
            printf("이름 입력: ");
            scanf("%s", name);
            printf("전화번호 입력: ");
            scanf("%s", phone);
            head = insertLast(head, name, phone);
            printf("연락처가 추가되었습니다.\n");
            break;
        case 2:
            printf("검색할 이름 입력: ");
            scanf("%s", name);
            searchContact(head, name);
            break;
        case 3:
            printf("삭제할 이름 입력: ");
            scanf("%s", name);
            head = deleteContact(head, name);
            break;
        case 4:
            printContacts(head);
            break;
        case 9:
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 입력입니다. 다시 선택해주세요.\n");
        }
    }

    // 메모리 해제
    freeList(head);
    return 0;
}

// 마지막에 노드 추가
Node* insertLast(Node* head, const char* name, const char* phone) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    Node* current = head;
    while (current->next != NULL)
        current = current->next;

    current->next = newNode;
    return head;
}

// 연락처 검색
void searchContact(Node* head, const char* name) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("검색 결과: %s - %s\n", current->name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("연락처를 찾을 수 없습니다.\n");
}

// 연락처 삭제
Node* deleteContact(Node* head, const char* name) {
    if (head == NULL) {
        printf("삭제할 연락처가 없습니다.\n");
        return NULL;
    }

    if (strcmp(head->name, name) == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        printf("연락처가 삭제되었습니다.\n");
        return head;
    }

    Node* current = head;
    while (current->next != NULL && strcmp(current->next->name, name) != 0) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("연락처를 찾을 수 없습니다.\n");
        return head;
    }

    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    printf("연락처가 삭제되었습니다.\n");

    return head;
}

// 전체 연락처 출력
void printContacts(Node* head) {
    if (head == NULL) {
        printf("전화번호부가 비어 있습니다.\n");
        return;
    }

    Node* current = head;
    printf("\n[전화번호부 목록]\n");
    while (current != NULL) {
        printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
        current = current->next;
    }
}

// 리스트 전체 해제
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}
