#define _USE_MATH_DEFINES
#include <math.h>
#define pi 3.14156

#include <stdlib.h>
#include <stdio.h>

void convolution(double*, int, double*, int, double*);
void blockconv(double*, int, double*, int, double*, int);

int L = 3;		//block size
int M;			//
int numblocks;	//#blocks

int hlen = 3;
int xlen = 6;
int ylen = 0;

int main(int argc, char* argv[]) {
	M = hlen - 1;
	numblocks = xlen / L;

	ylen = xlen + hlen - 1;	// L + M

	double* x = (double*)calloc(xlen, sizeof(double));	//input
	double* h = (double*)calloc(hlen, sizeof(double));	//kernel
	double* y = (double*)calloc(ylen, sizeof(double));	//output

	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	x[3] = 4;
	x[4] = 3;
	x[5] = 2;

	h[0] = 3;
	h[1] = 2;
	h[2] = 1;

	//yonline = 3 8 14 20 20 16 7 2 -> 8 waardes
	// 
	//yles = 1 4 10 16 20 20 13 6

	blockconv(x, xlen, h, hlen, y, L);

	printf("input:\n\r");
	for (int i = 0; i < xlen; i++)
	{
		printf("%.2lf\t", x[i]);
	}
	printf("\n\r");

	printf("kernel:\n\r");
	for (int i = 0; i < hlen; i++)
	{
		printf("%.2lf\t", h[i]);
	}
	printf("\n\r");

	printf("output:\n\r");
	for (int i = 0; i < ylen; i++)
	{
		printf("%.2lf\t", y[i]);
	}
	printf("\n\r");

	free(x);
	free(h);
	free(y);
}

void blockconv(double* x, int xlen, double* h, int hlen, double* y, int L) {

	printf("M = %d numblocks = %d ylen = %d sizeOfBlock = %d\n", M, numblocks, ylen, L);

	for (int i = 0; i < numblocks; i++)
	{
		int offset = i * L;

		// Roep de gewone 1D convolutie functie aan voor het huidige block
		convolution(x + offset, L, h, hlen, y + offset);
	}

	if (xlen % L != 0) {
		int offset = numblocks * L;
		convolution(y + offset, xlen % L, h, M + 1, y + offset);
	}


	/*
	* Voor mail
	for (int offset = 0; offset < xlen; offset++)
	{
		//input blok maken
		printf("input blok size: %d\n\r", L);
		double* inputBlok = (double*)calloc(L, sizeof(double));
		for (int j = 0; j < L; j++) {
			inputBlok[j] = x[j + offset];
			printf("%.2lf ", inputBlok[j]);
		}
		printf("\n\r");

		//output blok maken en convolutie berekenen
		printf("output blok size: %d\n\r", (L + hlen - 1));
		double* outputBlok = (double*)calloc((L + hlen - 1), sizeof(double));

		convolution(inputBlok, L, h, hlen, outputBlok);
		printf("convolution of blok %d\n\r", offset);
		for (int i = 0; i < (L + hlen - 1); i++)
		{
			printf("%.2lf ", outputBlok[i]);
		}
		printf("\n\r\n\r");

		//waardes optellen
		for (int j = 0; j < L; j++) {
			y[offset + j] += outputBlok[j];
		}

		free(inputBlok);
		free(outputBlok);
	}
	*/
}

void convolution(double* x, int xlen, double* h, int hlen, double* y) {
	int kmin = 0, kmax = 0;
	int Lc = xlen + hlen - 1;

	for (int n = 0; n < Lc; n++)
	{
		//y[n] = 0;

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