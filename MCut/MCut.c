#include <stdio.h>
#include <windows.h>

#define NUMSIZE 16
#define LINSIZE 64
#define STRSIZE 128


int main() {

	FILE* Vectors;
	FILE* Points;
	FILE* Output;

	errno_t read_res;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	printf(
 "                 @@@@@     @@@@@\n"
 " @@@@@@@@@@@@@   @@@@@@@ @@@@@@@@    @@@@@@@@@@@@\n"
 "@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@    @@@@@@@@@@@@\n"
 "@@@@@          @@@@@  @@@@@  @@@@@       @@@@\n"
 "@@@@@         @@@@@           @@@@@      @@@@\n"
 "@@@@@         @@@@             @@@@@     @@@@\n"
 "@@@@@        @@@@@              @@@@     @@@@\n"
 "@@@@@       @@@@@               @@@@@    @@@@\n"
 "@@@@@      @@@@@ @@@@       @@@@ @@@@@   @@@@\n"
 "@@@@@     @@@@@  @@@@       @@@@  @@@@@  @@@@\n"
 "@@@@@     @@@@   @@@@       @@@@   @@@@@ @@@@\n"
 "@@@@@       @@   @@@@       @@@@    @@   @@@@\n"
 "@@@@@            @@@@       @@@@         @@@@\n"
 "@@@@@            @@@@       @@@@         @@@@\n"
 "@@@@@            @@@@       @@@@         @@@@\n"
 "@@@@@            @@@@       @@@@         @@@@\n"
 "@@@@@            @@@@       @@@@         @@@@\n"
 "@@@@@@@@@@@@@@   @@@@       @@@@         @@@@\n"
 " @@@@@@@@@@@@@   @@@@@@@@@@@@@@@         @@@@\n"
 "                 @@@@@@@@@@@@@@@\n"
);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	
}
