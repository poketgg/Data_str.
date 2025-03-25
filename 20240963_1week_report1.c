#include <stdio.h>
#include <time.h>

int main(void) {
	int grade[10] = { "\0" };
	int sum = 0;
	double avg = 0;

	srand(time(0));

	for (int i = 0; i < 10; i++) {
		grade[i] = (rand() % 100) + 1;
		sum += grade[i];

		printf("학생 %d : %d 점\n", i, grade[i]);
	}

	avg = (double)sum / 10;
	printf("점수 합계 : %d\n", sum);
	printf("점수 평균 : %.2f", avg);
}
