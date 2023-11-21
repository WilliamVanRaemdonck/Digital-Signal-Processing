#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define pi 3.1415

#include "ass1_2.h"

#define rectangular 0
#define triangular 1
#define Hamming 2
#define Hanning 3
#define BlackmanHarris 4

//TODO help 
int man12(int argc, char* argv[]) {
	int originalSize = 8;
	int newSize = 16;

	double* x = (double*)calloc(originalSize, sizeof(double));
	double* y = (double*)calloc(newSize, sizeof(double));
	double* z = (double*)calloc(originalSize, sizeof(double));

	for (int i = 0; i < originalSize; i++)
		x[i] = 1;

	printf("Original: \n\r");
	printf("\t");
	for (int i = 0; i < originalSize; i++)
	{
		printf("%.2lf  ", x[i]);
	}
	printf("\n\r\n\r");

	zeropadding(x, originalSize, newSize, y);

	printf("zeropadding: \n\r");
	printf("\t");
	for (int i = 0; i < newSize; i++)
	{
		printf("%.2lf  ", y[i]);
	}
	printf("\n\r\n\r");
	clearOutput(y, newSize);

	//------------------------------------------------------------------------------------------
	//rectangle
	windowing(x, originalSize, rectangular, z);

	printf("windowing rectangle: \n\r");
	printf("\t");
	for (int i = 0; i < originalSize; i++)
	{
		printf("%.2lf  ", z[i]);
	}
	printf("\n\r\n\r");
	clearOutput(z, originalSize);

	//triangular	0.00 0.29 0.57 0.86 0.86 0.57 0.29 0.00
	windowing(x, originalSize, triangular, z);

	printf("windowing triangular: \n\r");
	printf("\t");
	for (int i = 0; i < originalSize; i++)
	{
		printf("%.2lf  ", z[i]);
	}
	printf("\n\r\n\r");
	clearOutput(z, originalSize);

	//Hamming	0.08 0.25 0.64 0.95 0.95 0.64 0.25 0.08
	windowing(x, originalSize, Hamming, z);

	printf("windowing Hamming: \n\r");
	printf("\t");
	for (int i = 0; i < originalSize; i++)
	{
		printf("%.2lf  ", z[i]);
	}
	printf("\n\r\n\r");
	clearOutput(z, originalSize);

	//Hanning	0.00 0.19 0.61 0.95 0.95 0.61 0.19 0.00
	windowing(x, originalSize, Hanning, z);

	printf("windowing Hanning: \n\r");
	printf("\t");
	for (int i = 0; i < originalSize; i++)
	{
		printf("%.2lf  ", z[i]);
	}
	printf("\n\r\n\r");
	clearOutput(z, originalSize);

	//Blackman-Harris	0.00 0.03 0.33 0.89 0.89 0.33 0.03 0.00 
	windowing(x, originalSize, BlackmanHarris, z);

	printf("windowing Blackman-Harris: \n\r");
	printf("\t");
	for (int i = 0; i < originalSize; i++)
	{
		printf("%.2lf  ", z[i]);
	}
	printf("\n\r\n\r");
	clearOutput(z, originalSize);

	free(x);
	free(y);
	free(z);

	return 0;
}


void zeropadding(double* input, int amoutOfSamples, int newLength, double* output) {
	for (int i = 0; i < newLength; i++) {
		if (i < amoutOfSamples) {
			output[i] = input[i];
		}
		else {
			output[i] = 0.0; // Zero-padding
		}
	}
}

void windowing(double* input, int amoutOfSamples, int windowType, double* output) {
	/*
	0) rectangular
	1) triangular
	2) Hamming
	3) Hanning
	4) Blackman-Harris
	*/

	int middle = 0;

	switch (windowType) {
	case 0:
		//	rectangular	w(n) = 1 ∀n = 0, 1, 2, ..., N − 1
		for (int i = 0; i < amoutOfSamples; i++)
		{
			output[i] = input[i];
		}
		break;

	case 1:
		//	triangular
		middle = amoutOfSamples / 2;
		for (int i = 0; i < amoutOfSamples; i++) {
			if (i <= middle) {
				output[i] = i / (double)middle;
			}
			else {
				output[i] = 2.0 - i / (double)middle;
			}
		}

		break;

	case 2:
		//	Hamming	w(n) = 0, 54 − 0, 46cos(2πn/(N − 1)) ∀n = 0, 1, 2, ..., N − 1
		for (int i = 0; i < amoutOfSamples; i++) {
			output[i] = 0.54 - 0.46 * cos(2 * pi * i / (amoutOfSamples - 1));
		}
		break;

	case 3:
		//	Hanning	w(n) = 0, 5 − 0, 5cos(2πn/(N − 1)) ∀n = 0, 1, 2, ..., N − 1
		for (int i = 0; i < amoutOfSamples; i++) {
			output[i] = 0.5 - 0.5 * cos(2 * pi * i / (amoutOfSamples - 1));
		}
		break;

	case 4:
		//	Blackman-Harris	w(n) = 0, 42 − 0, 5cos(2πn/(N − 1)) + 0, 08cos(4πn/(N − 1)) 0 ≤ n ≤ N − 1
		for (int i = 0; i < amoutOfSamples; i++) {
			output[i] = 0.42 - 0.5 * cos(2 * pi * i / (amoutOfSamples - 1)) + 0.08 * cos(4 * pi * i / (amoutOfSamples - 1));
		}
		break;

	default:
		//	rectangular	w(n) = 1 ∀n = 0, 1, 2, ..., N − 1
		for (int i = 0; i < amoutOfSamples; i++)
		{
			output[i] = input[i];
		}
		break;
	}
}

void clearOutput(double* output, int size) {
	for (int i = 0; i < size; i++)
	{
		output[i] = 0;
	}
}