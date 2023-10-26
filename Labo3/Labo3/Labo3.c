#define _USE_MATH_DEFINES
#include <math.h>
#define pi 3.14156

#include <stdlib.h>
#include <stdio.h>

void convolution_2D(double**, double**, int, int, int, double**);
void printImage(double**, int, int);

int ksize = 3;
int rows = 5;
int cols = 5;

double** x;
double** h;
double** y;

int main(int argc, char* argv[]) {
	x = (double**)calloc(cols, sizeof(double*));
	y = (double**)calloc(cols, sizeof(double*));

	for (int i = 0; i < rows; i++) {
		x[i] = (double*)calloc(rows, sizeof(double));
		y[i] = (double*)calloc(rows, sizeof(double));
	}

	h = (double**)calloc(ksize, sizeof(double*));
	for (int i = 0; i < ksize; i++) {
		h[i] = (double*)calloc(ksize, sizeof(double));
	}
	
	//fill x 
	int index = 1;
	for (int c = 0; c < cols; c++)
	{	
		for (int r = 0; r < rows; r++)
		{
			if (r < rows-1 && r > 0 && c < cols-1 && c > 0) {
				x[c][r] = index;
				index++;
			}
			else {
				x[c][r] = 0;
			}
			
		}
	}
	//fill h
	h[0][0] = 0;
	h[0][1] = -1;
	h[0][2] = 0;
	h[1][0] = -1;
	h[1][1] = 4;
	h[1][2] = -1;
	h[2][0] = 0;
	h[2][1] = -1;
	h[2][2] = 0;

	for (int c = 0; c < ksize; c++)
	{
		for (int r = 0; r < ksize; r++)
		{
			printf("%.2lf  ", h[c][r]);
		}
		printf("\n\r");
	}
	printf("\n\r");
	printf("\n\r");

	printImage(x, rows, cols);

	convolution_2D(x, h, ksize, rows, cols, y);

	printImage(y, rows, cols);

	free(x);
	free(y);
	free(h);
}

void convolution_2D(double** x, double** h, int ksize, int rows, int cols, double** y) {
	double product = 0;
	int startPos = ksize / 2;

	for (int c = startPos; c < (cols - startPos); c++)
	{
		for (int r = startPos; r < (rows - startPos); r++)
		{
			product = 0;
			//offset
			for (int i = -1; i <= 1; i++) 
			{
				for (int j = -1; j <= 1; j++)
				{
					product += (x[c+i][r+j] * h[i+1][j+1]);
					//printf("c = %d r = %d \n\ri = %d j = %d\n\r", c, r, i, j);
					//printf("i = %d j = %d\n\r", i+1, j+1);
					//printf("%lf\n\r", product);
				}
			}
			//printf("\n\r");

			/*
			(-1-1) (-1 0) (-1 1)
			(0-1)  (0 0)  (0 1)
			(1-1)  (1 0)  (1 1)
			*/

			y[c][r] = product;
		}
	}
}

void printImage(double** x, int rows, int cols) {
	printf("\033[0;36m");
	for (int c = 0; c < cols; c++)
	{
		for (int r = 0; r < rows; r++)
		{
			printf("%.2lf  ", x[c][r]);
		}
		printf("\n\r");

	}
	printf("\n\r");
	printf("\n\r");
	printf("\033[0;37m");
}