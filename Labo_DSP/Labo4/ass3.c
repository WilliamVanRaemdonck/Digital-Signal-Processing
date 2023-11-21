#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "ass1_2.h"

#define pi 3.1415

#define rectangular 0
#define triangular 1
#define Hamming 2
#define Hanning 3
#define BlackmanHarris 4

/*
Assignment 3: 
Combine the functions “zeropadding” and “windowing” to calculate the DFT of a zero
padded, windowed sequence. 

Does it matter which function you use first? Why (not)?
eerst windowing dan zero padding

*/

// Function to perform Discrete Fourier Transform (DFT) on input samples and store results in real, imaginary, magnitude, and phase arrays.
void dft(double*, int, double*, double*, double*, double*);

// Sample rate for the waveforms
double fsample = 8000;

// Number of samples in each waveform
int N = 8;

// Number of output bins for the DFT
int outputBins = 16;

int main3(int argc, char* argv[]) {
	int originalSize = 8;
	int newSize = 16;

	double* x = (double*)calloc(originalSize, sizeof(double));
	double* y = (double*)calloc(originalSize, sizeof(double));
	double* z = (double*)calloc(newSize, sizeof(double));

	double* real = (double*)calloc(outputBins, sizeof(double));
	double* imaginary = (double*)calloc(outputBins, sizeof(double));
	double* magnitude = (double*)calloc(outputBins, sizeof(double));
	double* phase = (double*)calloc(outputBins, sizeof(double));

	for (int i = 0; i < originalSize; i++)
		x[i] = 1;

	windowing(x, originalSize, rectangular, y);

	zeropadding(x, originalSize, newSize, z);

	dft(z, outputBins, real, imaginary, magnitude, phase);

	printf("Original:\n");
	for (int i = 0; i < originalSize; i++)
		printf("%.2lf\t", x[i]);
	printf("\n");

	printf("windowed:\n");
	for (int i = 0; i < originalSize; i++)
		printf("%.2lf\t", y[i]);
	printf("\n");

	printf("Zero padding:\n");
	for (int i = 0; i < newSize; i++)
		printf("%.2lf\t", z[i]);
	printf("\n");

	// Print the DFT values (real, imaginary, magnitude, and phase).
	printf("\tReal\t\t|\tImaginary\t|\tMagnitude\t|\tPhase\t\n\r");
	for (int i = 0; i < outputBins; i++) {
		printf("\t%lf\t|\t%lf\t|\t%lf\t|\t%lf\n\r", real[i], imaginary[i], magnitude[i], phase[i]);
	}
	printf("\n\r\n\r");


	free(x);
	free(y);
	free(z);

	free(real);
	free(imaginary);
	free(magnitude);
	free(phase);

	return 0;
}

// Function to perform Discrete Fourier Transform (DFT) on the input samples.
void dft(double* x, int outputBins, double* real, double* imaginary, double* magnitude, double* phase) {
	for (int k = 0; k < outputBins; k++) {
		real[k] = 0.0;
		imaginary[k] = 0.0;

		for (int n = 0; n < N; n++) {
			real[k] += x[n] * cos(2 * pi * (k * n) / N);
			imaginary[k] += x[n] * sin(2 * pi * (k * n) / N);
		}

		imaginary[k] = -imaginary[k];

		magnitude[k] = sqrt(real[k] * real[k] + imaginary[k] * imaginary[k]);
		if (magnitude[k] < 0.001) {
			magnitude[k] = 0;
			phase[k] = 0;
		}
		else {
			phase[k] = (atan2(imaginary[k], real[k]) * 180 / pi);
		}
	}
}