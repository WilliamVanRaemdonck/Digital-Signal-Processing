#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define pi 3.14156

// Function prototypes
void printValues(double*, int, double*, int, char*);
void addsignals(double*, double*, double*, int);
void dft(double*, int, double*, double*, double*, double*);

// Sample rate for the waveforms
double fsample = 8000;
// Number of samples in each waveform
int N = 8;
// Number of output bins for the DFT
int outputBins = 8;

// Size of arrays
int sizeX = 10;
int sizeY = 10;

int main(int argc, char* argv) {
	// Allocate memory for input signals (x and y)
	double* x = (double*)calloc(sizeX, sizeof(double));
	double* y = (double*)calloc(sizeY, sizeof(double));

	// Allocate memory for DFT results of x
	double* realX = (double*)calloc(outputBins, sizeof(double));
	double* imaginaryX = (double*)calloc(outputBins, sizeof(double));
	double* magnitudeX = (double*)calloc(outputBins, sizeof(double));
	double* phaseX = (double*)calloc(outputBins, sizeof(double));

	// Allocate memory for DFT results of y
	double* realY = (double*)calloc(outputBins, sizeof(double));
	double* imaginaryY = (double*)calloc(outputBins, sizeof(double));
	double* magnitudeY = (double*)calloc(outputBins, sizeof(double));
	double* phaseY = (double*)calloc(outputBins, sizeof(double));

	// Allocate memory for the sum of x and y in time domain
	double* txy = (double*)calloc(sizeX, sizeof(double));

	// Allocate memory for the DFT results of the sum of x and y in time domain
	double* txyReal = (double*)calloc(outputBins, sizeof(double));
	double* txyImagineary = (double*)calloc(outputBins, sizeof(double));

	// Allocate memory for the DFT results of the sum of DFTs of x and y
	double* fXYReal = (double*)calloc(outputBins, sizeof(double));
	double* fXYImagineary = (double*)calloc(outputBins, sizeof(double));

	// Initialize input signals (x and y) to 1
	for (int i = 0; i < sizeX; i++)
	{
		x[i] = 1;
		y[i] = 1;
	}

	// Print original input signals (x and y)
	printValues(x, sizeX, y, sizeY, "original");

	// Perform DFT on x and print the results
	dft(x, outputBins, realX, imaginaryX, magnitudeX, phaseX);
	printValues(realX, outputBins, imaginaryX, outputBins, "DFT van x");

	// Perform DFT on y and print the results
	dft(y, outputBins, realY, imaginaryY, magnitudeY, phaseY);
	printValues(realY, outputBins, imaginaryY, outputBins, "DFT van y");

	// Calculate the sum of x and y in time domain and perform DFT
	addsignals(x, y, txy, sizeX);
	dft(txy, outputBins, txyReal, txyImagineary, magnitudeX, magnitudeY);
	printValues(txyReal, outputBins, txyImagineary, outputBins, "t Sum");

	// Calculate the sum of DFTs of x and y and print the results
	addsignals(realX, realY, fXYReal, outputBins);
	addsignals(imaginaryX, imaginaryY, fXYImagineary, outputBins);
	printValues(fXYReal, outputBins, fXYImagineary, outputBins, "f Sum");

	// Free allocated memory
	free(x);
	free(y);

	free(realX);
	free(imaginaryX);
	free(magnitudeX);
	free(phaseX);

	free(realY);
	free(imaginaryY);
	free(magnitudeY);
	free(phaseY);

	free(txy);
	free(txyReal);
	free(txyImagineary);
	free(fXYReal);
	free(fXYImagineary);

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

// Function to add two signals element-wise.
void addsignals(double* x, double* y, double* z, int size) {
	for (int i = 0; i < size; i++)
	{
		z[i] = x[i] + y[i];
	}
}

// Function to print values of two arrays.
void printValues(double* x, int xSize, double* y, int ySize, char* text) {
	printf(text);
	printf("\n");

	for (int i = 0; i < xSize; i++)
	{
		printf("%.2lf\t", x[i]);
	}
	printf("\n");

	for (int i = 0; i < ySize; i++)
	{
		printf("%.2lf\t", y[i]);
	}
	printf("\n");
	printf("\n");
}
