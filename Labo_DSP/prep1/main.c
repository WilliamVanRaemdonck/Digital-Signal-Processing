#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void generateSineWave(double, double, double, double, int, double*);

double* x1;
double amplitude1 = 1;
double freq1 = 1000;
double sfreq1 = 8000;
double phase1 = 0;

double* x2;
double amplitude2 = 0.5;
double freq2 = 2000;
double sfreq2 = 8000;
double phase2 = (3*M_PI/4);

int N = 8;



int main(int argc, char* argv[]) {
	

	x1 = (double*)calloc(N, sizeof(double));

	generateSineWave(amplitude1, freq1, sfreq1, phase1, N, x1);

	for (int i = 0; i < N; i++)
	{
		printf("%.2lf\t", x1[i]);
	}
	printf("\n");

	free(x1);
	free(x2);

	return;
}


/*
- the amplitude “A” (double)
- the input signal’s frequency “f “(double)
- the sampling frequency “fs” (double)
- the phase “phi” (double)
- the required number of samples “N” (integer)
- a pointer to the resulting sequence “x” (double *)
*/
void generateSineWave(double amplitude, double freq, double sfreq, double phase, int samples, double* x) {
	for (int n = 0; n < samples; n++)
	{
		x[n] = amplitude * sin((2 * M_PI) * (freq / sfreq) * n + phase);
	}
}