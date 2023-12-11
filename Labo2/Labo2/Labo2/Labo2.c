#define _USE_MATH_DEFINES
#include <math.h>
#define pi 3.14156

#include <stdlib.h>
#include <stdio.h>

double* x;
double* h;
double* y;

const int xlen = 3;
const int hlen = 2;
int L;

void convolution(double*, int, double*, int, double*);

int main(int argc, char* argv[]) {
	x = (double*)calloc(xlen, sizeof(double));
	h = (double*)calloc(hlen, sizeof(double));

	L = xlen + hlen - 1;
	y = (double*)calloc(L, sizeof(double));

	// Initialize the arrays
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;

	h[0] = 1;
	h[1] = 2;

	convolution(x, xlen, h, hlen, y);

	printf("L = %d\n\r", L);
	printf("convolution = ");

	for (int i = 0; i < L; i++)
	{
		printf("%f ", y[i]);
	}
	printf("\n\r");

	free(x);
	free(h);
	free(y);
}

void convolution(double* x, int xlen, double* h, int hlen, double* y) {
	int kmin = 0, kmax = 0;
	int L = hlen + xlen - 1;

	for (int n = 0; n < L; n++)
	{
		y[n] = 0;

		//kmin
		if (n > hlen-1) {
			kmin = n - (hlen - 1);
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
		//printf("%d %d\n\r", kmin, kmax);

		//convolution som bereken tussen Kmin en Kmax
		for (int k = kmin; k <= kmax; k++)
		{
			//printf("%d) %f %f\n\r",n, h[k], x[k]);

			y[n] += x[k] * h[n - k];
		}
	}
}