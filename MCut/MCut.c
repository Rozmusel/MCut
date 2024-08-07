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


void menu(void);

int map(void);
int contour(void);
int cut(void);

void print_color(char* text, color c);


int main(void) {
	if (setlocale(LC_ALL, "ru") == NULL) {
		print_color("ERROR SET LOCALE", WHITE);
		return -1;
	}

	FILE* Vectors = NULL;
	FILE* Points = NULL;
	FILE* Output = NULL;
	errno_t read_res = NULL;	// Хранение результата открытия файла

	color b1 = WHITE, b2 = WHITE, b3 = WHITE;

	print_color(
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
	typedef enum {
		POINTS = 1,
		VECTORS = 2,
		CUTS = 3
	} mode;

	print_color(
		"[1] => Прочитать карту\n"
		"[2] => Прочитать контур\n"
		"[3] => Обрезать карту\n"
		"<< "
		"\n-------------------------------------------------\n"
		"\n-------------------------------------------------\n",
		WHITE
	);

	char input[256];
	while (1) {
		print_color(
			"\033[26;4H"
			"\33[K",
			WHITE
		);

		if (scanf_s("%s", &input, 256) != 1) printf("ERROR");
		int choice = atoi(input);
		
		print_color(
			"\033[28;0H"
			"\33[K",
			WHITE
		);
		
		switch (choice) {
		case POINTS:
			if (map()) {
				print_color(
					"Файл был успешно прочитан"
					"\033[23;8H"
					"Прочитать карту",
					GREEN
				);
			} else {
				print_color(
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
					"Файл был успешно прочитан"
					"\033[24;8H"
					"Прочитать контур",
					GREEN
				);
			}
			else {
				print_color(
					"Файл не был найден"
					"\033[24;8H"
					"Прочитать контур",
					DARK_RED
				);
			}
			break;

		case CUTS:
			print_color("Смена окна", WHITE);
			break;

		default:
			print_color(
				"                НЕИЗВЕСТНЫЙ РЕЖИМ",
				DARK_RED
			);
		}
	}
}


int map(void) {
	return 1;
}


int contour(void) {
	return 1;
}


int cut(void) {
	return 0;
}


void print_color(char* text, color c) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
	printf(text);
}
