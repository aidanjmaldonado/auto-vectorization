// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Type declarations
double foo(double * restrict x, double * restrict y, unsigned n);

int main(void) {

    // Domain
    unsigned h = 100;

    // Initialize domain and range arrays
    double * restrict x = (double *)calloc(h, sizeof(double));
    double * restrict y = (double *)calloc(h, sizeof(double));

    // x filled with values from 0 to 2π
    for (unsigned i = 0; i < h; i++) {
        x[i] = (2.0 * M_PI * i) / h;
    }

    // Iterate
    foo(x, y, h);

    for (unsigned i = 0; i < h; i++) {
        printf("y[%u] = %f\n", i, y[i]);
    }
    
    // Free memory
    free(x);
    free(y);

    return 0;
}

/*
Example function that invokes math operation within a loop
parameters:
    - double * restrict :: x - array of x values over domain
    - double * restrict :: y - empty array of the function sin(x) evaluated
    - unsigned :: n - upper bound of the domain [0, n]
*/
double foo(double * restrict x, double * restrict y, unsigned n) {
            
    // Calculate y(x) = sin(x) over the domain [0, n]
    for(unsigned i = 0; i < n; i++) {
        y[i] = sin(x[i]);
    }
}