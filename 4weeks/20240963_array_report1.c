#include <stdio.h>
#include <time.h>
int sumStudentScore(int scores[], int people);
double avgStudentScore(double sum, int people);
void searchScore(int scores[]);
void printScore(int scores[], int avg, int people);


int main(void) {
	int grade[30] = { "\0" };
	int sum, avg;

	srand(time(0));

	for (int i = 0; i < 30; i++) {
		grade[i] = rand() % 101;
	}

	sum = sumStudentScore(grade, 30);
	avg = avgStudentScore(sum, 30);

	searchScore(grade);
	printScore(grade, avg, 30);


	return 0;
}

int sumStudentScore(int scores[], int people) {
	int sum = 0;
	for (int i = 0; i < 30; i++) {
		sum += scores[i];

		//printf("학생 %d : %d 점\n", i, scores[i]);
	}
	return sum;
}

double avgStudentScore(double sum, int people) {
	double avg = (double)sum / people;
	printf("점수 평균 : %.2f\n", avg);

	return avg;
}

void searchScore(int scores[]) {
	int num;

	printf("검색할 학생의 번호 입력 (1~30) > ");

	while(1){
		scanf("%d", &num);
		if (num >= 1 && num <= 30) {
			printf("%d번 학생 : %d 점\n", num, scores[num]);
			break;
		}
		else {
			printf("잘못된 번호입니다. 다시 입력하여 주십시오. \n");
		}
	}

	return;
}

void printScore(int scores[], int avg, int people) {
	int option;
	printf("옵션을 선택 하시오. (0 : 모든 학생 점수 // 1: 평균 이상 점수 // 2: 평균 미만 학생 점수) > ");
	
	while (1) {
		scanf("%d", &option);
		if (option == 0) {
			for (int i = 0; i < people; i++) {
				printf("학생 %d : %d 점\n", i, scores[i]);
			}
			break;
		}
		else if (option == 1) {
			for (int i = 0; i < people; i++) {
				if (scores[i] >= avg)
					printf("학생 %d : %d 점\n", i, scores[i]);
			}
			break;
		}
		else if (option == 2) {
			for (int i = 0; i < people; i++) {
				if (scores[i] < avg)
					printf("학생 %d : %d 점\n", i, scores[i]);
			}
			break;
		}
		else {
			printf("잘못된 숫자입니다. 다시 입력하여 주십시오, \n");
		}
	}
}
