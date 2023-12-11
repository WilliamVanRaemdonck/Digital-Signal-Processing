#define _USE_MATH_DEFINES
#include <math.h>
#define pi 3.14156
#include "stdio.h"
#include "stdlib.h"


// Define a structure to represent a sine wave with amplitude, frequency, phase, and samples.
typedef struct {
	double A;
	double f;
	double phi;
	double* x;
} signal;

// Function to generate a sine wave and store it in the wave's sample array.
void generate_sinewave(signal, int, double);

// Function to add two arrays of samples element-wise and store the result in a third array.
void add_waves(double*, double*, int, double*);

// Function to perform Discrete Fourier Transform (DFT) on input samples and store results in real, imaginary, magnitude, and phase arrays.
void dft(double*, int, double*, double*, double*, double*);

// Sample rate for the waveforms
double fsample = 8000;

// Number of samples in each waveform
int N = 8;

// Number of output bins for the DFT
int outputBins = 8;

// Arrays to store the waveform samples and DFT results
double* x;
double* real;
double* imaginary;
double* magnitude;
double* phase;

int main(int argc, char* argv) {
	// Define three wave structures for the sine waves.
	signal wave1;
	signal wave2;
	signal wave3;

	// Initialize properties of wave1 (1 kHz sine wave).
	wave1.A = 1;
	wave1.f = 1000;
	wave1.phi = 0;
	wave1.x = (double*)calloc(N, sizeof(double));

	// Initialize properties of wave2 (0.5 * 2 kHz sine wave with a phase offset).
	wave2.A = 0.5;
	wave2.f = 2000;
	wave2.phi = (3 * pi) / 4;
	wave2.x = (double*)calloc(N, sizeof(double));

	// Create an array to store the result of adding wave1 and wave2 (wave3).
	wave3.x = (double*)calloc(N, sizeof(double));

	// Allocate memory for arrays to store DFT results.
	x = (double*)calloc(outputBins, sizeof(double));
	real = (double*)calloc(outputBins, sizeof(double));
	imaginary = (double*)calloc(outputBins, sizeof(double));
	magnitude = (double*)calloc(outputBins, sizeof(double));
	phase = (double*)calloc(outputBins, sizeof(double));

	// Generate the sine waves using the generate_sinewave function.
	generate_sinewave(wave1, N, fsample);
	generate_sinewave(wave2, N, fsample);

	// Add the two sine waves and store the result in wave3.
	add_waves(wave1.x, wave2.x, N, wave3.x);

	// Perform DFT on wave3 to calculate real, imaginary, magnitude, and phase.
	dft(wave3.x, outputBins, real, imaginary, magnitude, phase);

	// Print the values of wave1, wave2, and wave3.
	//setCmdColor("green");
	printf("wave 1: ");
	for (int i = 0; i < N; i++) {
		printf("%.2lf\t", wave1.x[i]);
	}
	printf("\n\r");

	printf("wave 2: ");
	for (int i = 0; i < N; i++) {
		printf("%.2lf\t", wave2.x[i]);
	}
	printf("\n\r");

	//setCmdColor("blue");
	printf("wave 3: ");
	for (int i = 0; i < N; i++) {
		printf("%.2lf\t", wave3.x[i]);
	}
	printf("\n\r\n\r");

	// Print the DFT values (real, imaginary, magnitude, and phase).
	//setCmdColor("red");
	printf("\tReal\t\t|\tImaginary\t|\tMagnitude\t|\tPhase\t\n\r");
	//setCmdColor("yellow");
	for (int i = 0; i < outputBins; i++) {
		printf("\t%lf\t|\t%lf\t|\t%lf\t|\t%lf\n\r", real[i], imaginary[i], magnitude[i], phase[i]);
	}
	printf("\n\r\n\r");
	//setCmdColor("reset");

	// Free memory allocated for dynamic arrays.
	free(wave1.x);
	free(wave2.x);
	free(wave3.x);

	free(x);
	free(real);
	free(imaginary);
	free(magnitude);
	free(phase);
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

// Function to add two arrays of samples element-wise.
void add_waves(double* x1, double* x2, int N, double* x3) {
	for (int n = 0; n < N; n++) {
		x3[n] = x1[n] + x2[n];
	}
}

// Function to generate a sine wave and store it in the wave's sample array.
void generate_sinewave(signal w, int N, double fs) {
	for (int n = 0; n < N; n++) {
		w.x[n] = w.A * sin((2 * pi) * (w.f / fs) * n + w.phi);
	}
}
