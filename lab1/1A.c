#include <stdio.h>

int main(void) {
	FILE* fin;
	FILE* fout;
	int a = 0, b = 0;
	fin = fopen("aplusb.in", "r");
	fout = fopen("aplusb.out", "w");
	fscanf(fin, "%i%i", &a, &b);
	fprintf(fout, "%i", a + b);
	fclose(fin);
	fclose(fout);
	return 0;
}