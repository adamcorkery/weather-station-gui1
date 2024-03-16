#include <stdio.h>
#include "functions.h"
#include <Windows.h>
#include <string.h>

void rsting(char* ptr, int x) {
	fgets(ptr, x, stdin);
	ptr[strcspn(ptr, "\n")] = 0;
}

void rint(int* a) {
	char buffer[255];
	fgets(buffer, 255, stdin);
	sscanf_s(buffer, "%d", a);
}

void rdub(double* a) {
	char buffer[255];
	fgets(buffer, 255, stdin);
	sscanf_s(buffer, "%Lf", a);
}

int SetDir() { // this is a function that detects the location of the .exe and sets the working dir there

	char buffer[MAX_PATH] = { 0 };
	size_t buffervaule;

	if (GetModuleFileNameA(NULL, buffer, MAX_PATH) == 0) { //gets the full file path including the .exe
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			printf("critial error, the filepath was too long, try placing the program in a folder closer to root directory");
		}
		printf("Failed to retrieve the path of the executable.\n");
		return 1;
	}


	buffervaule = strlen(buffer);
	buffervaule = buffervaule - 16; //16 is the amount of characters the .exe name is long + the / before the parent dir
	buffer[buffervaule] = 0;
	printf("%s\n", buffer);


	//printf("Directory of the executable: %s\n", buffer);

	if (chdir(buffer) != 0) {
		return 2;
	}


	return 0;
}