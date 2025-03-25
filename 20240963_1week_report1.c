#include <stdio.h>
#include <time.h>

int main(void) {
	int grade[10] = { "\0" };
	int sum = 0;

	for (int i = 0; i < 10; i++) {
		grade[i] = (rand() % 100) + 1;
		sum += grade[i];

		printf("학생 1 : %d 점\n", grade[i]);
	}

	printf("점수 합계 : %d", sum);
}
