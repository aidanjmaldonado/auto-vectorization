// Libraries
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <papi.h>
#include <papiStdEventDefs.h>
#include <time.h>

int main(void) {

    // Time step
    double h = 1e-4;
    double area = 0;

    // Bounds
    unsigned a = 0;
    unsigned b = 10;

    // Iterations
    unsigned n = (b - a) / h;

    // Initialize domain array
    double * restrict x = (double *)calloc(n, sizeof(double));
    for (unsigned i = 0; i < n; i++) {
        x[i] = h * i;
    }

    // Walltime struct
    struct timespec start, end;

    // Start timer
    int EventSet = PAPI_NULL;
    long long values[2];

    // Debugging PAPI
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI initialization error!\n");
        return 1;
    }

    if (PAPI_create_eventset(&EventSet) != PAPI_OK) {
        fprintf(stderr, "PAPI create eventset error!\n");
        return 1;
    }

    if (PAPI_add_event(EventSet, PAPI_TOT_INS) != PAPI_OK) {
        fprintf(stderr, "PAPI add event (TOT_INS) error!\n");
        return 1;
    }

    if (PAPI_add_event(EventSet, PAPI_FP_INS) != PAPI_OK) {
        fprintf(stderr, "PAPI add event (FP_INS) error!\n");
        return 1;
    }

    if (PAPI_start(EventSet) != PAPI_OK) {
        fprintf(stderr, "PAPI start error!\n");
        return 1;
    }

    // Get start walltime
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Trapezoidal rule to calculate are of f(x) = 2 * (sin(4x) * cos(2x) over [a, b]
    for (unsigned i = 1; i < n - 1; i++) {
        area += 2 * (sin(4 * x[i]) * cos(2 * x[i]));
    }

    // End walltime
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_ms = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1.0e6;
    printf("Elapsed Time: %.3f ms\n", elapsed_ms);

    // Stop and read counters
    if (PAPI_stop(EventSet, values) != PAPI_OK) {
        fprintf(stderr, "PAPI stop error!\n");
        return 1;
    }
    printf("Total Instructions: %lld\n", values[0]);
    printf("Floating Point Instructions: %lld\n", values[1]);

    area += 0.5 * 2 * (sin(4 * x[0]) * cos(2 * x[0]) + sin(4 * x[n - 1]) * cos(2 * x[n - 1]));
    area *= h;

    // Report area
    printf("Area of f(x) = 2 * (sin(4x) * cos(2x)) over [a, b]: %f\n", area);
    
    // Free memory
    free(x);

    return 0;
}