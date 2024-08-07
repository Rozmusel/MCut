#include <stdio.h>
#include <windows.h>
#include <locale.h>
#define NUMSIZE 16	// Максимальная длина считываемого числа
#define VECSIZE 64	// Максимальное количество векторов
#define STRSIZE 128	// Максимальная длина принимаемой строки

enum colors { WHITE = 7, DARK_YELLOW = 6, GREEN = 10, DARK_RED = 4, GRAY = 8 } b1, b2, b3;

void menu();
int map();
int contour();
int cut();

int main() {
	FILE* Vectors;
	FILE* Points;
	FILE* Output;

	errno_t read_res;	// Хранение результата открытия файла
	b1 = b2 = b3 = WHITE;


	setlocale(LC_ALL, "rus");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, DARK_YELLOW);	// Меняю цвет символов
	printf(
		"                 @@@@@     @@@@@					\n"
		" @@@@@@@@@@@@@   @@@@@@@ @@@@@@@@    @@@@@@@@@@@@	\n"
		"@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@    @@@@@@@@@@@@	\n"
		"@@@@@          @@@@@  @@@@@  @@@@@       @@@@		\n"
		"@@@@@         @@@@@           @@@@@      @@@@		\n"
		"@@@@@         @@@@             @@@@@     @@@@		\n"
		"@@@@@        @@@@@              @@@@     @@@@		\n"
		"@@@@@       @@@@@               @@@@@    @@@@		\n"
		"@@@@@      @@@@@ @@@@       @@@@ @@@@@   @@@@		\n"
		"@@@@@     @@@@@  @@@@       @@@@  @@@@@  @@@@		\n"
		"@@@@@     @@@@   @@@@       @@@@   @@@@@ @@@@		\n"
		"@@@@@       @@   @@@@       @@@@    @@   @@@@		\n"
		"@@@@@            @@@@       @@@@         @@@@		\n"
		"@@@@@            @@@@       @@@@         @@@@		\n"
		"@@@@@            @@@@       @@@@         @@@@		\n"
		"@@@@@            @@@@       @@@@         @@@@		\n"
		"@@@@@            @@@@       @@@@         @@@@		\n"
		"@@@@@@@@@@@@@@   @@@@       @@@@         @@@@		\n"
		" @@@@@@@@@@@@@   @@@@@@@@@@@@@@@         @@@@		\n"
		"                 @@@@@@@@@@@@@@@					\n"
	);
	printf("\n\n");
	SetConsoleTextAttribute(hConsole, WHITE);

	menu();
}

void menu() {
	enum mode { POINTS = 1, VECTORS, CUTS };
	int choice;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	printf(	"[1] => Прочитать карту\n"
			"[2] => Прочитать контур\n"
			"[3] => Обрезать карту\n"	);

	printf("<< ");
	printf(	"\n-------------------------------------------------\n"
			"\n-------------------------------------------------\n"	);
	for (;;) {
		SetConsoleTextAttribute(hConsole, WHITE);
		printf("\033[26;4H");
		printf("\33[K");

		scanf_s("%d", &choice);

		printf("\033[28;0H");
		printf("\33[K");
		switch (choice) {
		case POINTS:
			if (map()) {
				SetConsoleTextAttribute(hConsole, GREEN);
				printf("Файл был успешно прочитан");
				printf("\033[23;8H");
				printf("Прочитать карту");
			} else {
				SetConsoleTextAttribute(hConsole, DARK_RED);
				printf("Файл не был найден");
				printf("\033[23;8H");
				printf("Прочитать карту");
			}
			break;
		case VECTORS:
			if (contour()) {
				SetConsoleTextAttribute(hConsole, GREEN);
				printf("Файл был успешно прочитан");
				printf("\033[24;8H");
				printf("Прочитать контур");
			}
			else {
				SetConsoleTextAttribute(hConsole, DARK_RED);
				printf("Файл не был найден");
				printf("\033[24;8H");
				printf("Прочитать контур");
			}
			break;
		case CUTS:
			printf("Смена окна");
			break;
		default:
			SetConsoleTextAttribute(hConsole, DARK_RED);
			printf("                НЕИЗВЕСТНЫЙ РЕЖИМ");

		}

	}
}

int map() {
	return 1;
}

int contour() {
	return 1;
}
int cut() {
	return 0;
}