#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define pi 3.1415

#define METHOD1 1
#define METHOD2 2

void idft(double*, double*, int, double*, double*, double*, double*, int);
void printValues(double*, int, char*);

// 0.35    0.35    0.65    1.06    0.35    -1.06   -1.35   -0.35

int inputSize = 8;
int DFTOutputBins = 8;
// Number of samples in each waveform
int N = 8;

int main(int argc, char* argv[]) {
	double* fReal = (double*)calloc(inputSize, sizeof(double));
	double* fImaginary = (double*)calloc(inputSize, sizeof(double));

	double* tReal = (double*)calloc(inputSize, sizeof(double));
	double* tImaginary = (double*)calloc(inputSize, sizeof(double));

	double* DFTMagnitude = (double*)calloc(inputSize, sizeof(double));
	double* DFTPhase = (double*)calloc(inputSize, sizeof(double));

	fReal[0] = 0;       fImaginary[0] = 0;
	fReal[1] = 0;       fImaginary[1] = -4;

	fReal[2] = 1.414;   fImaginary[2] = 1.414;
	fReal[3] = 0;       fImaginary[3] = 0;

	fReal[4] = 0;       fImaginary[4] = 0;
	fReal[5] = 0;       fImaginary[5] = 0;

	fReal[6] = 1.414;   fImaginary[6] = -1.414;
	fReal[7] = 0;       fImaginary[7] = 4;


	printValues(fReal, inputSize, "fReal");
	printValues(fImaginary, inputSize, "fImaginary");

	idft(fReal, fImaginary, DFTOutputBins, tReal, tImaginary, DFTMagnitude, DFTPhase, METHOD1);
	printf("Method 1\n");
	printValues(tReal, inputSize, "tReal");
	printValues(tImaginary, inputSize, "tImaginary");
	printValues(DFTMagnitude, inputSize, "DFTMagnitude");
	printValues(DFTPhase, inputSize, "DFTPhase");

	idft(fReal, fImaginary, DFTOutputBins, tReal, tImaginary, DFTMagnitude, DFTPhase, METHOD2);
	printf("Method 2\n");
	printValues(tReal, inputSize, "tReal");
	printValues(tImaginary, inputSize, "tImaginary");
	printValues(DFTMagnitude, inputSize, "DFTMagnitude");
	printValues(DFTPhase, inputSize, "DFTPhase");

	free(fReal);
	free(fImaginary);
	free(tReal);
	free(tImaginary);
	free(DFTMagnitude);
	free(DFTPhase);

	return 0;
}

void idft(double* fReal, double* fImaginary, int DFTOutputBins, double* tReal, double* tImaginary, double* DFTMagnitude, double* DFTPhase, int method) {
	if (method == METHOD1) {
		// * -1
		for (int i = 0; i < DFTOutputBins; i++)
		{
			fImaginary[i] = -fImaginary[i];
		}

		for (int k = 0; k < DFTOutputBins; k++) {
			tReal[k] = 0.0;
			tImaginary[k] = 0.0;

			for (int n = 0; n < N; n++) {
				tReal[k] += (fReal[n] * cos(2 * pi * (k * n) / N)) + (fImaginary[n] * sin(2 * pi * (k * n) / N));
				tImaginary[k] += (fReal[n] * sin(2 * pi * (k * n) / N)) - (fImaginary[n] * cos(2 * pi * (k * n) / N));
			}

			// normaliseren
			tReal[k] /= N;
			tImaginary[k] /= N;

			// Magnitude and phase
			DFTMagnitude[k] = sqrt(tReal[k] * tReal[k] + tImaginary[k] * tImaginary[k]);
			if (DFTMagnitude[k] < 0.001) {
				DFTMagnitude[k] = 0;
				DFTPhase[k] = 0;
			}
			else {
				DFTPhase[k] = (atan2(tImaginary[k], tReal[k]) * 180 / pi);
			}

		}

		// * -1
		for (int i = 0; i < DFTOutputBins; i++)
		{
			tImaginary[i] = -tImaginary[i];
		}

	}
	else if (method == METHOD2) {
		// Swap real and imaginary parts
		double* fRealTmp = (double*)calloc(DFTOutputBins, sizeof(double));
		double* fImaginaryTmp = (double*)calloc(DFTOutputBins, sizeof(double));

		for (int i = 0; i < DFTOutputBins; i++) {
			fRealTmp[i] = fImaginary[i];
			fImaginaryTmp[i] = fReal[i];
		}

		// Perform IDFT
		for (int k = 0; k < DFTOutputBins; k++) {
			tReal[k] = 0.0;
			tImaginary[k] = 0.0;

			for (int n = 0; n < N; n++) {
				tReal[k] += (fRealTmp[n] * sin(2 * pi * k * n / N)) + (fImaginaryTmp[n] * cos(2 * pi * k * n / N));
				tImaginary[k] += (fRealTmp[n] * cos(2 * pi * k * n / N)) - (fImaginaryTmp[n] * sin(2 * pi * k * n / N));
			}

			// Normalize
			tReal[k] /= N;
			tImaginary[k] /= N;

			// Magnitude and phase
			DFTMagnitude[k] = sqrt(tReal[k] * tReal[k] + tImaginary[k] * tImaginary[k]);
			if (DFTMagnitude[k] < 0.001) {
				DFTMagnitude[k] = 0;
				DFTPhase[k] = 0;
			}
			else {
				DFTPhase[k] = (atan2(tImaginary[k], tReal[k]) * 180 / pi);
			}
		}

		// Free temporary arrays
		free(fRealTmp);
		free(fImaginaryTmp);
	}
}

	/*
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



	*/

	void printValues(double* x, int size, char* text) {
		printf(text);
		printf("\n");
		for (int i = 0; i < size; i++)
		{
			printf("%.2lf\t", x[i]);
		}
		printf("\n\n");
	}
