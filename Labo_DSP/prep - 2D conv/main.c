#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void printImage(double**, int, int);
void convolution2D(double**, double**, int, int, int, double**);

double** x;
double** y;
double** h;

int ksize = 3;
int rows = 5;
int collums = 5;


int main(int argc, char* argv) {
	// make mem
	x = (double**)calloc(collums, sizeof(double*));
	y = (double**)calloc(collums, sizeof(double*));
	h = (double**)calloc(ksize, sizeof(double*));

	for (int c = 0; c < rows; c++)
	{
		x[c] = (double*)calloc(rows, sizeof(double));
		y[c] = (double*)calloc(rows, sizeof(double));
	}

	for (int c = 0; c < ksize; c++)
		h[c] = (double*)calloc(ksize, sizeof(double));

	// init mem
	int index = 1;
	for (int i = 1; i < collums-1; i++)
	{
		for (int j = 1; j < rows-1; j++)
		{
			x[i][j] = index;
			index++;
		}
	}

	h[0][0] = 0;
	h[0][1] = -1;
	h[0][2] = 0;
	h[1][0] = -1;
	h[1][1] = 4;
	h[1][2] = -1;
	h[2][0] = 0;
	h[2][1] = -1;
	h[2][2] = 0;

	// print
	printImage(x, collums, rows);
	printImage(h, ksize, ksize);

	convolution2D(x, h, ksize, collums, rows, y);

	printImage(y, collums, rows);

	free(x);
	free(y);
	free(h);

	return 0;
}

void printImage(double** x, int colt, int rowt) {

	for (int c = 0; c < colt; c++)
	{
		for (int r = 0; r < rowt; r++)
		{
			printf("%.2lf\t", x[c][r]);
		}
		printf("\n");
	}
	printf("\n");
}

void convolution2D(double** x, double** h, int ksize, int cols, int rows, double** y) {
	int startPos = ksize / 2;
	double som;

	for (int c = startPos; c < cols- startPos; c++)
	{
		for (int r = startPos; r < rows- startPos; r++)
		{
			som = 0;
			//offset

			for (int yoffset = -1; yoffset <= 1; yoffset++)
			{
				for (int xoffset = -1; xoffset <= 1; xoffset++)
				{
					som += (x[c+yoffset][r+xoffset] * h[yoffset+1][xoffset+1]);
				}
			}
			y[c][r] = som;
		}
	}
}