#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void remove_student(int** arr, int* size, int index);
void add_students(int** arr, int* size, int new_students[], int num_new);
void print_students(int* arr, int size);

int main(void) {
    int size = 5;
    int* students = (int*)malloc(size * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        students[i] = (rand() % 100) + 1;
    }

    print_students(students, size);

    remove_student(&students, &size, 2);
    print_students(students, size);

    int new_students[2] = { 80, 90 };
    add_students(&students, &size, new_students, 2);
    print_students(students, size);

    // 메모리 해제
    free(students);
    return 0;
}

void remove_student(int** arr, int* size, int index) {
    if (index < 0 || index >= *size) {
        printf("잘못된 인덱스입니다.\n");
        return;
    }

    for (int i = index; i < *size - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }

    (*size)--;
    *arr = (int*)realloc(*arr, (*size) * sizeof(int));
}

void add_students(int** arr, int* size, int new_students[], int num_new) {
    *arr = (int*)realloc(*arr, (*size + num_new) * sizeof(int));

    for (int i = 0; i < num_new; i++) {
        (*arr)[*size + i] = new_students[i];
    }

    *size += num_new;
}

void print_students(int* arr, int size) {
    printf("학생 목록: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
