#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;                      // 노드에 저장할 데이터
    struct TreeNode* left;        // 왼쪽 자식 노드를 가리키는 포인터
    struct TreeNode* right;       // 오른쪽 자식 노드를 가리키는 포인터
} TreeNode;

TreeNode* createNode(int data);
void preorder(TreeNode* node);
void inorder(TreeNode* node);
void postorder(TreeNode* node);
void freeTree(TreeNode* node);

int getHeight(TreeNode* node);
int countNodes(TreeNode* node);
int countLeaves(TreeNode* node);

int getSum(TreeNode* node);
int getMax(TreeNode* node);
void searchRange(TreeNode* node, int min, int max);

int main(void) {
    // 트리 구성
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    // 순회 출력
    printf("전위 순회: ");
    preorder(root);
    printf("\n");

    printf("중위 순회: ");
    inorder(root);
    printf("\n");

    printf("후위 순회: ");
    postorder(root);
    printf("\n");

    // 분석 출력
    printf("트리 높이: %d\n", getHeight(root));
    printf("전체 노드 수: %d\n", countNodes(root));
    printf("리프 노드 수: %d\n", countLeaves(root));

    printf("노드 값 총합: %d\n", getSum(root)); 
    printf("최댓값: %d\n", getMax(root));  

    // 범위 탐색
    printf("값이 6 이상 20 이하인 노드: ");
    searchRange(root, 6, 20);             
    printf("\n");

    freeTree(root);
    return 0;
}

TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preorder(TreeNode* node) {
    if (node == NULL) return;

    printf("%d ", node->data);      // 1. 루트 방문
    preorder(node->left);           // 2. 왼쪽 서브트리 순회
    preorder(node->right);          // 3. 오른쪽 서브트리 순회
}

void inorder(TreeNode* node) {
    if (node == NULL) return;

    inorder(node->left);            // 1. 왼쪽 서브트리 순회
    printf("%d ", node->data);     // 2. 루트 방문
    inorder(node->right);          // 3. 오른쪽 서브트리 순회
}

void postorder(TreeNode* node) {
    if (node == NULL) return;

    postorder(node->left);         // 1. 왼쪽 서브트리 순회
    postorder(node->right);        // 2. 오른쪽 서브트리 순회
    printf("%d ", node->data);     // 3. 루트 방문
}

void freeTree(TreeNode* node) {
    if (node == NULL) return;

    freeTree(node->left);   // 왼쪽 서브트리 먼저 해제
    freeTree(node->right);  // 오른쪽 서브트리 해제
    free(node);             // 현재 노드 해제
}

int getHeight(TreeNode* node) {
    if (node == NULL) return -1;  // NULL 자식은 간선 없음 → 높이 -1

    int leftHeight = getHeight(node->left);   // 왼쪽 서브트리의 높이
    int rightHeight = getHeight(node->right); // 오른쪽 서브트리의 높이

    if (leftHeight > rightHeight) return leftHeight + 1;
    else return rightHeight + 1;
}

int countNodes(TreeNode* node) {
    if (node == NULL) return 0;

    return 1 + countNodes(node->left) + countNodes(node->right);
}

int countLeaves(TreeNode* node) {
    if (node == NULL) return 0;

    if (node->left == NULL && node->right == NULL)
        return 1;  // 리프 노드일 경우

    return countLeaves(node->left) + countLeaves(node->right);
}

int getSum(TreeNode* node) {
    if (node == NULL)
        return 0;

    int leftSum = getSum(node->left); // 왼쪽 서브트리 합
    int rightSum = getSum(node->right); // 오른쪽 서브트리 합

    return node->data + leftSum + rightSum;
}

int getMax(TreeNode* node) {
    if (node == NULL)
        return 0;

    int leftMax = getMax(node->left); // 왼쪽 서브트리 최댓값
    int rightMax = getMax(node->right); // 오른쪽 서브트리 최댓값

    int max = node->data;

    if (leftMax > max)
        max = leftMax;
    else if (rightMax > max)
        max = rightMax;

    return max;
}

void searchRange(TreeNode* node, int min, int max) {
    if (node == NULL)
        return;

    // 왼쪽 서브트리 탐색
    searchRange(node->left, min, max);

    // 오른쪽 서브트리 탐색
    searchRange(node->right, min, max);

    // 현재 노드 값이 min과 max 사이일 때 출력
    if (node->data >= min && node->data <= max)
        printf("%d ", node->data);

    
}
