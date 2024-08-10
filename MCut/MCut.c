#include <stdio.h>
#include <windows.h>
#include <locale.h>


#define NUMSIZE 16	// Максимальная длина считываемого числа
#define VECSIZE 64	// Максимальное количество векторов
#define STRSIZE 128	// Максимальная длина принимаемой строки

#define V_KEY_SIZE 8
#define P_KEY_SIZE 4

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

int is_key(char str[STRSIZE], const char key[V_KEY_SIZE], const int size);
float get_number(char str[STRSIZE], int *read_pos);
int get_flag(char str[STRSIZE], int* read_pos);
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
		int i = -1;
		do {
			i++;
			input[i] = getchar();
		} while (input[i] != '\n');
		choice = atoi(input);
		
		print_color(
			hConsole,
			"\033[28;0H"
			"\33[K",
			WHITE
		);

		int result;
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
			result = contour();
			if (result > 0) {
				print_color(
					hConsole,
					"Количество найденных элементов: "
					"\033[24;8H"
					"Прочитать контур",
					GREEN
				);
				printf("\033[28;33H");
				printf("%d", result);
				fl_vectors = 1;
			} else if (result == 0){
				print_color(
					hConsole,
					"Ошибка чтения: контур не найден"
					"\033[24;8H"
					"Прочитать контур",
					DARK_RED
				);
			} else {
				print_color(
					hConsole,
					"Файл не найден"
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
	if (read_res != 0) return -1;


	float mlines[VECSIZE][2][2] = { 0 };	//[Номер элемента][Начало и конец][координаты (x, y)]
	float mrad[VECSIZE][3] = {0};	// [Номер элемента][Тип данных о дуге (радиус, флаг большой дуги, флаг направления)]

	char str[STRSIZE] = { 0 };

	const char vec_key[V_KEY_SIZE] = "<path d=";

	int counter = 0; //счётчик прочитанных объектов



	while(!feof(Vectors)) {
		int read_pos = 10;
		fgets(str, STRSIZE, Vectors);
		if (is_key(str, vec_key, V_KEY_SIZE)) {
			mlines[counter][0][0] = get_number(str, &read_pos);
			read_pos++;
			mlines[counter][0][1] = get_number(str, &read_pos);
			if (str[read_pos] == ' ') {	// Если после второй цифры пробел - записана дуга
				read_pos += 2;
				mrad[counter][0] = get_number(str, &read_pos);
				int space = 0;
				while (space < 2) { // Пропуск трёх чисел
					read_pos++;
					if (str[read_pos] == ' ') {
						space++;
					}
				}
				read_pos++;
				mrad[counter][1] = get_flag(str, &read_pos);
				read_pos++;
				mrad[counter][2] = get_flag(str, &read_pos);
				read_pos++;
				mlines[counter][1][0] = get_number(str, &read_pos);
				read_pos++;
				mlines[counter][1][1] = get_number(str, &read_pos);
				counter++;
				continue;
			}
			read_pos = 1;
			fgets(str, STRSIZE, Vectors);
			mlines[counter][1][0] = get_number(str, &read_pos);
			read_pos++;
			mlines[counter][1][1] = get_number(str, &read_pos);
			counter++;
		}
	}
	/* Если нужно посмотреть что считалось из файла, раскоментировать
	printf("\033[22;0H");
	printf("\033[0J");
	for (int i = 0; i < counter; i++) {
		printf("x1:%.4f y1:%.4f\tx2:%.4f y2:%.4f\tr:%.4f f1:%.0f f2:%.0f\n", mlines[i][0][0], mlines[i][0][1], mlines[i][1][0], mlines[i][1][1], mrad[i][0], mrad[i][1], mrad[i][2]);
	}
	exit(0); 
	*/
	return counter;
}


int cut(void) {
	return 0;
}


void print_color(HANDLE hConsole, char* text, color c) {
	SetConsoleTextAttribute(hConsole, c);
	printf(text);
}

int is_key(char str[STRSIZE], const char key[V_KEY_SIZE], const int size) {
	for (int i = 0; i < size; i++) {
		if (key[i] != str[i]) return 0;
	}
	return 1;
}

float get_number(char str[STRSIZE], int *read_pos) {
	float result = 0;
	int dot_pos = 0;
	int num[NUMSIZE] = { 0 };
	int inum = 0;
	float power = 1;
	while (!(str[*read_pos] == ' ' || str[*read_pos] == '\n' || str[*read_pos] == '"')) {
		if (str[*read_pos] == '.') {
			dot_pos = inum;
			(*read_pos)++;
			continue;
		}
		num[inum] = (int)str[*read_pos] - 48;
		(*read_pos)++;
		inum++;
	}
	for (int i = 1; i < dot_pos; i++) {
		power *= 10;
	}
	for (int i = 0; i < inum; i++) {
		result += num[i] * power;
		power *= 0.1;
	}
	return result;
}

int get_flag(char str[STRSIZE], int* read_pos) {
	(*read_pos)++;
	return (int)str[*read_pos - 1] - 48;
}