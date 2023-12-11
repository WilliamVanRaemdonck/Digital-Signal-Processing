#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void convolution(double*, int, double*, int, double*);
void convolution1(double*, int, double*, int, double*);
void convolution2(double*, int, double*, int, double*);
void convolution3(double*, int, double*, int, double*);

double* x;
double* h;
double* y;

int xlen = 3;
int hlen = 2;
int L;


int main(int argc, char* argv[]) {
	L = xlen + hlen - 1;

	x = (double*)calloc(xlen, sizeof(double));
	h = (double*)calloc(hlen, sizeof(double));
	y = (double*)calloc(L, sizeof(double));

	x[0] = 1;
	x[1] = 2;
	x[2] = 3;

	h[0] = 1;
	h[1] = 2;

	for (int i = 0; i < xlen; i++)
	{
		printf("%.2lf\t", x[i]);
	}
	printf("\n");

	for (int i = 0; i < hlen; i++)
	{
		printf("%.2lf\t", h[i]);
	}
	printf("\n");

	convolution(x, xlen, h, hlen, y);
	for (int i = 0; i < L; i++)
	{
		printf("%.2lf\t", y[i]);
	}
	printf("\n");
	for (int i = 0; i < L; i++)
		y[i] = 0;
	//--------------------------------------------------

	convolution1(x, xlen, h, hlen, y);
	for (int i = 0; i < L; i++)
	{
		printf("%.2lf\t", y[i]);
	}
	printf("\n");
	for (int i = 0; i < L; i++)
		y[i] = 0;
	//--------------------------------------------------

	convolution2(x, xlen, h, hlen, y);
	for (int i = 0; i < L; i++)
	{
		printf("%.2lf\t", y[i]);
	}
	printf("\n");
	for (int i = 0; i < L; i++)
		y[i] = 0;
	//--------------------------------------------------

	convolution3(x, xlen, h, hlen, y);
	for (int i = 0; i < L; i++)
	{
		printf("%.2lf\t", y[i]);
	}
	printf("\n");
	for (int i = 0; i < L; i++)
		y[i] = 0;
	//--------------------------------------------------




	free(x);
	free(y);
	free(h);

	return 0;
}

void convolution(double* x, int xlen, double* h, int hlen, double* y) {

	int kmin = 0;
	int kmax = 0;

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

		for (int k = kmin; k <= kmax; k++) {
			y[n] += x[k] * h[n - k];
		}
	}
}

void convolution1(double* x, int xlen, double* h, int hlen, double* y) {
	int kmin;
	int kmax;

	for (int n = 0; n < L; n++)
	{
		y[n] = 0;

		//kmin
		if (n > (hlen - 1 )) {
			kmin = hlen - 1;
		}
		else {
			kmin = 0;
		}

		//kmax
		if (n > (xlen - 1)) {
			kmax = xlen - 1;
		}
		else {
			kmax = n;
		}

		//conv
		for (int k = kmin; k <= kmax; k++)
		{
			y[n] += x[k] * h[n - k];
		}

	}

}

void convolution2(double* x, int xlen, double* h, int hlen, double* y) {

	int kmin;
	int kmax;

	for (int n = 0; n < L; n++)
	{
		y[n] = 0;

		//kmin
		if (n > (hlen - 1)) {
			kmin = hlen - 1;
		}
		else {
			kmin = 0;
		}

		//kmax
		if (n > (xlen - 1)) {
			kmax = xlen - 1;
		}
		else {
			kmax = n;
		}

		//conv
		for (int k = kmin; k <= kmax; k++)
		{
			y[n] += x[k] * h[n - k];
		}
	}


}

void convolution3(double* x, int xlen, double* h, int hlen, double* y) {
	int kmin;
	int kmax;

	for (int n = 0; n < L; n++)
	{
		y[n] = 0;
		
		//kmin
		if (n > (hlen - 1)) {
			kmin = hlen - 1;
		}
		else {
			kmin = 0;
		}

		//kmax
		if (n > (xlen - 1)) {
			kmax = xlen - 1;
		}
		else {
			kmax = n;
		}

		//conv
		for (int k = kmin; k <= kmax; k++)
		{
			y[n] += x[k] * h[n - k];
		}
	}
}