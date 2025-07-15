#include "naive.h"

void naive_matrix_mult(int N, const double A[N][N], const double B[N][N],
                       double C[N][N]) {

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      C[i][j] = 0.0;
      for (int k = 0; k < N; k++)
        C[i][j] += A[i][k] * B[k][j];
    }
}
