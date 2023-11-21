#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stdlib.h"

#include "bro.h"

// William Van Raemdonck - Bro - V1.0

/*
    setCmdColor
        - red
        - green
        - yellow
        - blue
        - white (reset)
*/

/*
double* x;


int main(int argc, char* argv[]) {
    // Test main
    setCmdColor("red");
    printf("text\n");

    setCmdColor("green");
    printf("text\n");

    setCmdColor("yellow");
    printf("text\n");

    setCmdColor("blue");
    printf("text\n");

    setCmdColor("reset");  // Reset the text color
    printf("text\n");

    x = (double*)calloc(10, sizeof(double));

    x[0] = 2;
    x[1] = 5;
    x[2] = 2;
    x[3] = 3;
    x[4] = 4;

    x[5] = 3;
    x[6] = 2;
    x[7] = 1;
    x[8] = 0;
    x[9] = 1;


    generateGraph(10, x, 10);

    free(x);

    return 0;
}
*/



void setCmdColor(char* color) {
    if (strcmp(color, "red") == 0) {
        printf("\033[31m");  // Set text color to red
    }
    else if (strcmp(color, "green") == 0) {
        printf("\033[32m");  // Set text color to green
    }
    else if (strcmp(color, "yellow") == 0) {
        printf("\033[33m");  // Set text color to yellow
    }
    else if (strcmp(color, "blue") == 0) {
        printf("\033[34m");  // Set text color to blue
    }
    else if (strcmp(color, "reset") == 0) {
        printf("\033[0m");   // Reset text color to default
    }
}


void generateGraph(int ValuesX, double* data, int size) {
    // Find the maximum value in the data
    double maxData = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] > maxData) {
            maxData = data[i];
        }
    }
    
    setCmdColor("blue");
    printf("   ^\n");
    // Generate the graph
    for (int i = maxData; i >= 1; i--) {
        setCmdColor("green");
        printf("%.3d", i),
        setCmdColor("blue");
        printf("|\t");

        setCmdColor("reset");
        for (int j = 0; j < size; j++) {
            if (data[j] >= i) {
                printf("|\t");
            }
            else {
                printf("\t");
            }
        }
        printf("\n");
    }

    setCmdColor("blue");

    printf("   +");
    // Print the X-axis labels
    for (int i = 0; i < size; i++) {
        printf("---------");
    }
    printf(">\n\t");

    setCmdColor("green");
    // Print the X-axis labels
    for (int i = 0; i < size; i++) {
        printf("%d\t", i);
    }
    printf("\n");
    
    setCmdColor("reset");
}
