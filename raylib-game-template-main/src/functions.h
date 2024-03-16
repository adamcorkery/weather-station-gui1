#pragma once


struct reading {
	int humidity;
	double temperature;
};


void rsting(char* ptr, int x);
void rint(int* a);
void rdub(double* a);
int SetDir(void);
/*	error code list:
		1: the program wasn't able to locate the .exe or the buffer is too long, (if this is the case the program will print this as well as return code 1)
		2: the program wasnt able to set the WD to the directory of the .exe
	*/