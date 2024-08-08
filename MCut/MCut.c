#include <stdio.h>
#include <windows.h>
#include <locale.h>


#define NUMSIZE 16	// Максимальная длина считываемого числа
#define VECSIZE 64	// Максимальное количество векторов
#define STRSIZE 128	// Максимальная длина принимаемой строки


typedef enum {
	WHITE = 7,
	DARK_YELLOW = 6,
	GREEN = 10,
	DARK_RED = 4,
	GRAY = 8
} color;

FILE* Vectors = NULL;
FILE* Points = NULL;
FILE* Output = NULL;
errno_t read_res = NULL;	// Хранение результата открытия файла

void menu(void);

int map(void);
int contour(void);
int cut(void);

void print_color(HANDLE hConsole, char* text, color c);


int main(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (setlocale(LC_ALL, "ru") == NULL) {
		print_color(hConsole, "ERROR SET LOCALE", WHITE);
		return -1;
	}


	color b1 = WHITE, b2 = WHITE, b3 = WHITE;

	print_color(
		hConsole,
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
		"\n\n",
		DARK_YELLOW
	);

	menu();
}

void menu(void) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	typedef enum {
		POINTS = 1,
		VECTORS = 2,
		CUTS = 3
	} mode;

	print_color(
		hConsole,
		"[1] => Прочитать карту\n"
		"[2] => Прочитать контур\n"
		"[3] => Обрезать карту\n"
		"<< "
		"\n-------------------------------------------------\n"
		"\n-------------------------------------------------\n",
		WHITE
	);

	int fl_points = 0, fl_vectors = 0;
	char input[256];
	while (1) {
		print_color(
			hConsole,
			"\033[26;4H"
			"\33[K",
			WHITE
		);

		int choice = -1;
		for (int i = 0; (input[i] = getchar()) != '\n' && input[i] != EOF; i++) {}
		choice = atoi(input);
		
		print_color(
			hConsole,
			"\033[28;0H"
			"\33[K",
			WHITE
		);
		
		switch (choice) {
		case POINTS:
			if (map()) {
				print_color(
					hConsole,
					"Файл был успешно прочитан"
					"\033[23;8H"
					"Прочитать карту",
					GREEN
				);
				fl_points = 1;
			} else {
				print_color(
					hConsole,
					"Файл не был найден"
					"\033[23;8H"
					"Прочитать карту",
					DARK_RED
				);
			}
			break;

		case VECTORS:
			if (contour()) {
				print_color(
					hConsole,
					"Файл был успешно прочитан"
					"\033[24;8H"
					"Прочитать контур",
					GREEN
				);
				fl_vectors = 1;
			} else {
				print_color(
					hConsole,
					"Файл не был найден"
					"\033[24;8H"
					"Прочитать контур",
					DARK_RED
				);
			}
			break;

		case CUTS:
			if (fl_points && fl_vectors) {
				print_color(hConsole, "Смена окна", WHITE);
			} else {
				print_color(
					hConsole,
					"Недостаточно входных данных"
					"\033[25;8H"
					"Обрезать карту", 
					DARK_RED
				);
			}
			
			break;

		default:
			print_color(
				hConsole,
				"                НЕИЗВЕСТНЫЙ РЕЖИМ",
				DARK_RED
			);
		}
	}
}


int map(void) {
	read_res = fopen_s(&Points, "Points.txt", "r");
	if (read_res != 0) return 0;
	return 1;
}


int contour(void) {
	read_res = fopen_s(&Vectors, "Contour.txt", "r");
	if (read_res != 0) return 0;
	return 1;
}


int cut(void) {
	return 0;
}


void print_color(HANDLE hConsole, char* text, color c) {
	SetConsoleTextAttribute(hConsole, c);
	printf(text);
}
