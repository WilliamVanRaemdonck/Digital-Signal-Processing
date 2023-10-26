#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#define pi 3.14159265359

void convolution(double*, int, double*, int, double*);

double* x;
double* h;
double* y;

int xlen = 3;
int hlen = 2;
int L;

int kmax, kmin;

int main(int argc, char* argv) {

	x = (double*)calloc(xlen, sizeof(double));
	h = (double*)calloc(hlen, sizeof(double));
	L = xlen + hlen - 1;
	y = (double*)calloc(L, sizeof(double));
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;

	h[0] = 1;
	h[1] = 2;

	convolution(x, xlen, h, hlen, y);

	printf("\n\r");
	for (int i = 0; i < L; i++)
	{
		printf("%.0f ", y[i]);
	}
	printf("\n\r");

	free(x);
	free(h);
	free(y);

	return 0;
}


void convolution(double* x, int xlen, double* h, int hlen, double* y) {
	
	for (int n = 0; n < L; n++)
	{
		y[n] = 0;

		//kmin & kmax berekenen
		//kmin
		if (n > hlen -1) {
			kmin = n - (hlen -1);
		}
		else {
			kmin = 0;
		}

		//kmax
		if (n > xlen-1) {
			kmax = xlen -1;
		}
		else {
			kmax = n;
		}
		printf(" %d %d\n\r", kmin, kmax);

		//convolutie berekenen
		for (int k = kmin; k <= kmax; k++)
		{
			y[n] += x[k] * h[n - k];
		}

	}



}