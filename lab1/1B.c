#include <stdio.h>

int main(void) {
	FILE* i;
	FILE* o;
	i = fopen("aplusbb.in", "r");
	o = fopen("aplusbb.out", "w");
	long long int a, b;
	fscanf(i, "%lli%lli", &a, &b);
	fprintf(o, "%lli", a + b * b);
	fclose(i);
	fclose(o);
	return 0;
}