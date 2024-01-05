#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define N 1000
int a[N][N], b[N][N], c[N][N];


int main() {
	int i, j, k;


#pragma omp parallel for
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			a[i][j] = rand() / RAND_MAX;
			b[i][j] = rand() / RAND_MAX;
		}
	}

	for (int threads = 1; threads <= 16; threads++) {
		double start = omp_get_wtime();

		#pragma omp parallel num_threads(threads)
		{
			#pragma omp for
			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++)
					for (k = 0; k < N; k++)
						c[i][j] += a[i][k] * b[k][j];
			}
		}
		double end = omp_get_wtime();

		printf("%d: %lf\n", threads, end - start);
	}
	return 0;
}
