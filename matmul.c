/*
 * matmul.c — Matrix multiplication (C version). No timing code:
 * hyperfine measures the whole program from the outside.
 *
 * Usage:   ./matmul <N> <order>
 *          order = ijk  (standard: B read down columns -> cache misses)
 *          order = ikj  (swapped:  A and B read across rows -> cache friendly)
 *
 * Build:   gcc -O0 matmul.c -o matmul_O0
 *          gcc -O3 matmul.c -o matmul_O3
 *
 * Prints a checksum of C so you can verify every version computes the same
 * answer, and so the compiler can't delete the multiply as dead code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Matrices are ONE contiguous block of n*n doubles, stored row-major:
 * element (i, j) lives at index i*n + j. Walking along a row = walking
 * through consecutive memory addresses.
 */

/* Standard order: inner loop walks B DOWN A COLUMN -> stride of n doubles */
static void matmul_ijk(int n, const double *A, const double *B, double *C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
                sum += A[i*n + k] * B[k*n + j];   /* B jumps n*8 bytes each step */
            C[i*n + j] = sum;
        }
}

/* Swapped order: inner loop walks B and C ACROSS A ROW -> stride of 1 */
static void matmul_ikj(int n, const double *A, const double *B, double *C) {
    memset(C, 0, (size_t)n * n * sizeof(double));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            double a = A[i*n + k];
            for (int j = 0; j < n; j++)
                C[i*n + j] += a * B[k*n + j];     /* consecutive addresses */
        }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s N ijk|ikj\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    const char *order = argv[2];

    double *A = malloc((size_t)n * n * sizeof(double));
    double *B = malloc((size_t)n * n * sizeof(double));
    double *C = malloc((size_t)n * n * sizeof(double));

    /* Same deterministic inputs as the Python version */
    for (int i = 0; i < n * n; i++) {
        A[i] = (i % 7) * 0.5;
        B[i] = (i % 5) * 0.25;
    }

    if (strcmp(order, "ikj") == 0)
        matmul_ikj(n, A, B, C);
    else
        matmul_ijk(n, A, B, C);

    double checksum = 0.0;
    for (int i = 0; i < n * n; i++) checksum += C[i];
    printf("checksum = %.1f\n", checksum);

    free(A); free(B); free(C);
    return 0;
}