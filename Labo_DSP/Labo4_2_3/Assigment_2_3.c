#define _USE_MATH_DEFINES
#include <math.h>
#define pi 3.14156

#include "stdio.h"
#include "stdlib.h"

/*
- a pointer to the input samples (double *)
- the number of DFT output bins (integer)
- a pointer to the real part of the DFT (double *)
- a pointer to the imaginary part of the DFT (double *),
- a pointer to the DFT magnitude (double *)
- a pointer to the DFT phase (double *)
*/

/*
{
(-0.000000) + j(0.000000)
(0.000003) + j(-3.994041)
(1.399998) + j(1.420002)
(-0.000001) + j(0.005958)
(-0.000000) + j(-0.000001)
(0.000001) + j(-0.005960)
(1.400006) + j(-1.419992)
(-0.000020) + j(3.994039)


}*/

typedef struct {
	double A;
	double f;
	double phi;
	double* x;
}signal;

//double A, double f, double fs, double phi, int N, double* x
void generate_sinewave(signal, int, double);

//double* x1, double* x2, int N, double* x3
void add_waves(double*, double*, int, double*);

//double* x, int outputBins, double* real , double* imaginary, double* magnitude, double* phase
void dft(double*, int, double*, double*, double*, double*);

double fsample = 8000;
int N = 8; //samples for sine wave


int outputBins = 8;
double* x;
double* real;
double* imaginary;
double* magnitude;
double* phase;

int main(int argc, char* argv) {
	/*
		generate 2 signals
		Signal “x1”: sin(2*pi*1000*t)
		Signal “x2”: 0,5 * sin(2*pi*2000*t + 3π/4)
	*/
	signal wave1;


	wave1.A = 1;
	wave1.f = 6000;
	wave1.phi = 0;
	wave1.x = (double*)calloc(N, sizeof(double));

	x = (double*)calloc(outputBins, sizeof(double));
	real = (double*)calloc(outputBins, sizeof(double));;
	imaginary = (double*)calloc(outputBins, sizeof(double));;
	magnitude = (double*)calloc(outputBins, sizeof(double));;
	phase = (double*)calloc(outputBins, sizeof(double));;

	// make waves
	generate_sinewave(wave1, N, fsample);

	// dft
	dft(wave1.x, outputBins, real, imaginary, magnitude, phase);

	// print values
	// wave 1
	printf("\033[0;32mwave 1: ");
	for (int i = 0; i < N; i++)
	{
		printf("%.2lf\t", wave1.x[i]);
	}
	printf("\n\r\n\r");

	// values
	printf("\033[0;31m\tReal\t\t|\tImaginary\t|\tMagnitude\t|\tPhase\t\n\r");
	for (int i = 0; i < outputBins; i++)
	{
		printf("\033[0;33m\t%lf\t|\t%lf\t|\t%lf\t|\t%lf\n\r", real[i], imaginary[i], magnitude[i], phase[i]);
	}
	printf("\n\r\n\r");

	free(wave1.x);

	free(x);
	free(real);
	free(imaginary);
	free(magnitude);
	free(phase);
}

void dft(double* x, int outputBins, double* real, double* imaginary, double* magnitude, double* phase) {

	for (int k = 0; k < outputBins; k++) {
		real[k] = 0.0;
		imaginary[k] = 0.0;

		for (int n = 0; n < N; n++) {
			real[k] += x[n] * cos(2 * pi * (k * n) / N);
			imaginary[k] += x[n] * sin(2 * pi * (k * n) / N);

			//printf("Re = %.2lf Im -j%.2lf \n\r", (x[n] * cos(2 * pi * (k * n) / N)), (x[n] * sin(2 * pi * (k * n) / N)));
		}
		//printf("Ret = %.2lf Imt = %.2lf", real[k], imaginary[k]);
		//printf("\n\r\n\r");
		imaginary[k] = -imaginary[k];

		magnitude[k] = sqrt(real[k] * real[k] + imaginary[k] * imaginary[k]);
		if (magnitude[k] < 0.001)
		{
			magnitude[k] = 0;
			phase[k] = 0;
		}
		else {
			phase[k] = (atan2(imaginary[k], real[k]) * 180 / pi);	// in radialen omzetten naar graden *180/pi
		}
	}
}

void add_waves(double* x1, double* x2, int N, double* x3) {
	for (int n = 0; n < N; n++)
	{
		x3[n] = x1[n] + x2[n];
	}
}

void generate_sinewave(signal w, int N, double fs) {
	for (int n = 0; n < N; n++)
	{
		w.x[n] = w.A * sin((2 * pi) * (w.f / fs) * n + w.phi);
		//printf("%lf %lf %lf %lf \n\r", w.A, w.f, w.phi, w.x[n]);
	}
}