#define _USE_MATH_DEFINES
#include <math.h>
#define pi 3.14156

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	double A;
	double f;
	double fs;
	double phi;
	double* x;
}wave;

void generate_sinewave(double, double, double, double, int, double*);
void add_waves(double*, double*, int, double*);

int main(int argc, char *argv[]) {
	wave wave1;
	wave wave2;
	wave wave3;
	int N = 8;

	wave1.A = 1;
	wave1.f = 1000;
	wave1.fs = 8000;
	wave1.phi = 0;
	wave1.x = (double*)calloc(N, sizeof(double));

	wave2.A = 0.5;
	wave2.f = 2000;
	wave2.fs = 8000;
	wave2.phi = (3*pi)/4;
	wave2.x = (double*)calloc(N, sizeof(double));

	wave3.x = (double*)calloc(N, sizeof(double));

	//generate waves
	generate_sinewave(wave1.A, wave1.f, wave1.fs, wave1.phi, N, wave1.x);
	generate_sinewave(wave2.A, wave2.f, wave2.fs, wave2.phi, N, wave2.x);

	//Add waves
	add_waves(wave1.x, wave2.x, N, wave3.x);

	//print values wave
	for (int i = 0; i < N; i++)
	{
		printf("x(%d)= %f\n\r", i, wave3.x[i]);
	}
	printf("\n\r");

	//free memory
	free(wave1.x);
	free(wave2.x);
	free(wave3.x);

	return 0;
}

void add_waves(double* x1, double* x2, int N, double* x3) {
	for (int n = 0; n < N; n++)
	{
		x3[n] = x1[n] + x2[n];
	}
}

void generate_sinewave(double A, double f, double fs, double phi, int N, double* x) {
	for (int n = 0; n < N; n++)
	{
		x[n] = A * sin((2*pi) * (f/fs) * n + phi);
	}
}