#include <stdio.h>

#define N 500
static double A[N][N], B[N][N];

int main(void) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = ((i * N + j) % 7) * 0.5;
            B[i][j] = ((i * N + j) % 5) * 0.25;
        }

    double checksum = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];
            checksum += sum;              /* the only place the result goes */
        }

#ifdef USE_RESULT
    printf("checksum = %.1f\n", checksum);
#else
    (void)checksum;                       /* never looked at -> dead code */
#endif
    return 0;
}