// Вильковского О. С., 1 курс, ПИз-18
// Лабораторная 4, вариант 15
// Международная торговля -MPE, т. 9, с. 412
// В каком году оборот был минимальным?
// В каких годах разница в индексах экспорта США и ФРН была не большей за год P
#include <stdio.h> 
#include <locale.h>
#include <math.h> 
#define N 100
int countYears;

struct {
	int year;
	int rev;
	int index_usa;
	int index_ang;
	int index_ger;
} arr[N];

void setOptions() {
	setlocale(LC_ALL, "Russian");
	system("color F0");
	system("cls");
}

int inputInt(char *s) {
	int result, n;
	do {
		printf("%s", s);
		result = scanf("%d", &n);
		while (getchar() != '\n');
		if (result != 1) printf("%s", "Ошибка ввода!\n");
	} while (result != 1);
	return n;
}

int inputYears() {
	int n;
	int pr;
	do {
		n = inputInt("Введите количество вносимых лет: ");

		if (n<1 || n>N) {
			pr = 1;
			printf("Вы ошиблись!\n");
		}
		else {
			pr = 0;
		}
	} while (pr);
	return n;
}

void inputTable() {
	int pr;
	int i, j;
	do {
		for (i = 0; i < countYears; i++) {
			do {
				int t = inputInt("Год: ");
				for (j = 0; j < countYears; j++) {
					if (t == arr[j].year) {
						printf("Такой год уже есть в списке!\n");
						pr = 1;
						break;
					}
					else {
						pr = 0;
					}
				}
				if (pr == 0 && j == countYears) {
					arr[i].year = t;
				}
			} while (pr);

			arr[i].rev = inputInt("Оборот: ");
			arr[i].index_usa = inputInt("Индекс экспорта США: ");
			arr[i].index_ang = inputInt("Индекс экспорта Англии: ");
			arr[i].index_ger = inputInt("Индекс экспорта Германии: ");

			if (arr[i].year < 0 || arr[i].rev < 0 || arr[i].index_usa < 0 || arr[i].index_ang < 0 || arr[i].index_ger < 0) {
				pr = 1;
				printf("Вы ошиблись! Повторите ввод\n");
				i--;
			}
			else {
				pr = 0;
			}
		}
	} while (pr);
}

void outputTable() {
	printf("г===============================================================================¬\n");
	printf("¦Год	¦	Оборот(млрд $)	¦	Индекс экспорта(1953 год = 100)		¦\n");
	printf("¦-------------------------------------------------------------------------------¦\n");
	printf("¦	¦			¦	США	¦	Англия	¦Германия	¦\n");
	printf("¦-------------------------------------------------------------------------------¦\n");
	for (int i = 0; i < countYears; i++) {
		printf("%s%i%s%i%s%i%s%i%s%i%s", "¦", arr[i].year, "	¦	", arr[i].rev, "		¦	", arr[i].index_usa, "	¦	", arr[i].index_ang, "	¦	", arr[i].index_ger, "	¦\n");
	}
	printf("L===============================================================================-\n");
}

void findYearMinRev() {
	int year_min = arr[0].year;
	int rev_min = arr[0].rev;
	for (int i = 1; i < countYears; i++) {
		if (arr[i].rev < rev_min) {
			year_min = arr[i].year;
			rev_min = arr[i].rev;
		}
	}
	printf("%s%d%s", "Минимальный оборот был в ", year_min, " году\n");
}

int inputYear() {
	printf("Поиск годов, где разница индексов США и Германии меньше года P\n");
	int pr;
	int P, P_diff;
	int i, j;
	do {
		P = inputInt("Введите год P: ");
		for (i = 0; i < countYears; i++) {
			if (arr[i].year == P) {
				P_diff = abs(arr[i].index_usa - arr[i].index_ger);
				pr = 0;
				break;
			}
			else {
				pr = 1;
			}
		}
		if (pr == 1 && i == countYears) {
			printf("Такого года в таблице нет\n");
		}
	} while (pr);
	return P_diff;
}

void checkYear(int P_diff) {
	int pr;
	int i, j;
	for (i = 0; i < countYears; i++) {
		if (abs(arr[i].index_usa - arr[i].index_ger) < P_diff) {
			printf("%d%s", arr[i].year, " г.\n");
			pr = 1;
		}
	}

	if (pr == 0) {
		printf("Записей с меньшей разницей индексов нет!\n");
	}
}

int main() {
	setOptions();
	countYears = inputYears();
	inputTable();
	outputTable();
	findYearMinRev();
	checkYear(inputYear());
	getch();
	return 0;
}