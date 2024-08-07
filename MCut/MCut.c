#include <stdio.h>
#include <windows.h>
#include <locale.h>
#define NUMSIZE 16	// Максимальная длина считываемого числа
#define VECSIZE 64	// Максимальное количество векторов
#define STRSIZE 128	// Максимальная длина принимаемой строки

enum colors { WHITE = 7, DARK_YELLOW = 6, GREEN = 10, DARK_RED = 4, GRAY = 8 } b1, b2, b3;
int test;

void menu();

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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	printf("[1] => ");
	SetConsoleTextAttribute(hConsole, b1);
	printf("Прочитать карту\n");
	SetConsoleTextAttribute(hConsole, WHITE);

	printf("[2] => ");
	SetConsoleTextAttribute(hConsole, b2);
	printf("Прочитать контур\n");
	SetConsoleTextAttribute(hConsole, WHITE);

	printf("[3] => ");
	SetConsoleTextAttribute(hConsole, b3);
	printf("Обрезать карту\n");
	SetConsoleTextAttribute(hConsole, WHITE);

	printf("<< ");
	printf(	"\n-------------------------------------------------\n"
			"\n-------------------------------------------------\n");
	printf("\033[26;4H");

	scanf_s("%d", &test);
	return 0;
}