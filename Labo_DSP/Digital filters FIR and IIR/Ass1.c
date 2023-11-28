#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define pi 3.1415

typedef struct {
	double A;
	double f;
	double phi;
	double* x;
} signal;

double coeffs[20] = {
-0.0046344907284793296,
0.0087519416878243453,
0.0057896124151878871,
-0.028987910081502824,
0.0094840911173724798,
0.047781786872994558,
-0.030063781671853387,
-0.10075440783558906,
0.12227053266348673,
0.47010833750596753,
0.47010833750596753,
0.12227053266348673,
-0.10075440783558906,
-0.030063781671853387,
0.047781786872994558,
0.0094840911173724798,
-0.028987910081502824,
0.0057896124151878871,
0.0087519416878243453,
-0.0046344907284793296
};

// FIR filter function
void fir(double*, int, double*, int, double*);

// Function to perform Discrete Fourier Transform (DFT) on input samples and store results in real, imaginary, magnitude, and phase arrays.
void dft(double*, int, double*, double*, double*, double*);

// Function to generate a sine wave and store it in the wave's sample array.
void generate_sinewave(signal, int, double);

// Function to add two arrays of samples element-wise and store the result in a third array.
void add_waves(double*, double*, int, double*);

// Function to print values
void printValues(double*, int, char*);

//convolutie
void fir(double*, int, double*, int, double*);

// Sample rate for the waveforms
double fsample = 8000;
// Number of samples in each waveform
int N = 8;
// Number of output bins for the DFT
int outputBins = 8;

int coeffsize2 = sizeof(coeffs) / sizeof(coeffs[0]);

int main(int argc, char* argv[]) {
	signal signal1;
	signal signal2;
	signal signal3;
	signal signal4;

	// Initialize properties of signal1 (1 kHz sine wave).
	signal1.A = 1;
	signal1.f = 1000;
	signal1.phi = 0;
	signal1.x = (double*)calloc(N + coeffsize2, sizeof(double));

	// Initialize properties of signal2 (2 kHz sine wave).
	signal2.A = 0.5;
	signal2.f = 2000;
	signal2.phi = (3 * pi) / 4;
	signal2.x = (double*)calloc(N + coeffsize2, sizeof(double));

	// Initialize properties of summed signals
	signal3.x = (double*)calloc(N + coeffsize2, sizeof(double));

	// Initialize properties of firred signal
	signal4.x = (double*)calloc(coeffsize2 + N, sizeof(double));

	//values for DFT output
	double* x = (double*)calloc(outputBins, sizeof(double));
	double* real = (double*)calloc(outputBins, sizeof(double));
	double* imaginary = (double*)calloc(outputBins, sizeof(double));
	double* magnitude = (double*)calloc(outputBins, sizeof(double));
	double* phase = (double*)calloc(outputBins, sizeof(double));

	// Generate the sine waves using the generate_sinewave function.
	generate_sinewave(signal1, N + coeffsize2, fsample);
	generate_sinewave(signal2, N + coeffsize2, fsample);

	// Add the two sine waves and store the result in wave3.
	add_waves(signal1.x, signal2.x, N + coeffsize2, signal3.x);

	// summed signals
	printValues(signal3.x, N + coeffsize2, "signal3 (summed signals)");

	// DFT
	dft(signal3.x, outputBins, real, imaginary, magnitude, phase);

	// TEST PRINT
	printValues(magnitude, outputBins, "Magnitude part BEFORE FIR");

	printf("----------------------------------------------------------------------------\r\n");

	// FIR
	fir(signal3.x, N + coeffsize2, coeffs, coeffsize2, signal4.x);

	// firred signal
	printValues(signal4.x, N + coeffsize2, "signal AFTER FIR");

	// DFT
	dft(signal4.x + coeffsize2, outputBins, real, imaginary, magnitude, phase);

	// TEST PRINT
	printValues(magnitude, outputBins, "magnitude part AFTER FIR");


	return 0;
}

// Function to perform Discrete Fourier Transform (DFT) on the input samples.
void dft(double* x, int outputBins, double* real, double* imaginary, double* magnitude, double* phase) {
	for (int k = 0; k < outputBins; k++) {
		real[k] = 0.0;
		imaginary[k] = 0.0;

		for (int n = 0; n < N; n++) {
			real[k] += x[n] * cos(2 * pi * (k * n) / N);
			imaginary[k] -= x[n] * sin(2 * pi * (k * n) / N);
		}

		//imaginary[k] = -imaginary[k];

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

void printValues(double* x, int size, char* text) {
	printf(text);
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("%.2lf\t", x[i]);
	}
	printf("\n\n");
}

void fir(double* x, int xlen, double* h, int hlen, double* y) {
	int kmin = 0, kmax = 0;
	int L = hlen + xlen - 1;
	for (int n = 0; n < L; n++)
	{
		y[n] = 0;

		//kmin
		if (n > hlen - 1) {
			kmin = n - (hlen - 1);
		}
		else {
			kmin = 0;
		}

		//kmax
		if (n > xlen - 1) {
			kmax = xlen - 1;
		}
		else {
			kmax = n;
		}
		//printf("%d %d\n\r", kmin, kmax);

		//convolution som bereken tussen Kmin en Kmax
		for (int k = kmin; k <= kmax; k++)
		{
			//printf("%d) %f %f\n\r",n, h[k], x[k]);

			y[n] += x[k] * h[n - k];
		}
	}
}
