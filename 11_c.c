#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 20
#define N 20

char* input =	"08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08 "
		"49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00 "
		"81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65 "
		"52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91 "
		"22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80 "
		"24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50 "
		"32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70 "
		"67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21 "
		"24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72 "
		"21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95 "
		"78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92 "
		"16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57 "
		"86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58 "
		"19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40 "
		"04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66 "
		"88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69 "
		"04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36 "
		"20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16 "
		"20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54 "
		"01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48";

typedef struct arg_t {
	int matrix[M][N];
	int res;
} arg_t;

void parseMatrix(const char* input, int matrix[M][N])
{
	int n, m;
	n = m = 0;

	char* dup_input = strdup(input);
	char* token = strtok(dup_input, " ");

	while (token != NULL) {
		matrix[n][m] = atoi(token);
		if (++m == M) {
			m = 0;
			n++;
		}

		token = strtok(NULL, " ");
	}
}

void* diag_1(void* arg)
{
	arg_t* args = (arg_t *) arg;

	int max = 0;
	for (int i = 3; i < M; i++) {
		for (int j = 0; j < N - 3; j++) {
			int product = args->matrix[i][j] *
				args->matrix[i - 1][j + 1] *
				args->matrix[i - 2][j + 2] *
				args->matrix[i - 3][j + 3];
			if (product > max)
				max = product;
		}
	}
	args->res = max;

	pthread_exit(NULL);
}

void* diag_2(void* arg)
{
	arg_t* args = (arg_t *) arg;

	int max = 0;

	for (int i = 0; i < M - 3; i++) {
		for (int j = 0; j < N - 3; j++) {
			int product = args->matrix[i][j] *
				args->matrix[i + 1][j + 1] *
				args->matrix[i + 2][j + 2] *
				args->matrix[i + 3][j + 3];
			if (product > max)
				max = product;
		}
	}
	args->res = max;

	pthread_exit(NULL);
}

void* vertical(void* arg)
{
	arg_t* args = (arg_t *) arg;

	int max = 0;

	for (int i = 0; i < M - 3; i++) {
		for (int j = 0; j < N; j++) {
			int product = args->matrix[i][j] *
				args->matrix[i + 1][j] *
				args->matrix[i + 2][j] *
				args->matrix[i + 3][j];
			if (product > max)
				max = product;
		}
	}
	args->res = max;

	pthread_exit(NULL);
}
void* horizontal(void* arg)
{
	arg_t* args = (arg_t *) arg;

	int max = 0;

	for (int i = 0;i < M; i++) {
		for (int j = 0; j < N - 3; j++) {
			int product = args->matrix[i][j] *
				args->matrix[i][j + 1] *
				args->matrix[i][j + 2] *
				args->matrix[i][j + 3];
			if (product > max)
				max = product;
		}
	}
	args->res = max;

	pthread_exit(NULL);
}

int main(void)
{
	int matrix[M][N];
	parseMatrix(input, matrix);

	pthread_t h, v, d1, d2;
	arg_t h_arg, v_arg, d1_arg, d2_arg;

	memcpy(&(h_arg.matrix), &matrix, N * M * sizeof(int));
	memcpy(&(v_arg.matrix), &matrix, N * M * sizeof(int));
	memcpy(&(d1_arg.matrix), &matrix, N * M * sizeof(int));
	memcpy(&(d2_arg.matrix), &matrix, N * M * sizeof(int));

	pthread_create(&h, NULL, horizontal, &h_arg);
	pthread_create(&v, NULL, vertical, &v_arg);
	pthread_create(&d1, NULL, diag_1, &d1_arg);
	pthread_create(&d2, NULL, diag_2, &d2_arg);

	pthread_join(h, NULL);
	pthread_join(v, NULL);
	pthread_join(d1, NULL);
	pthread_join(d2, NULL);

	int res = 0;
	int results[4] = {
		v_arg.res,
		h_arg.res,
		d1_arg.res,
		d2_arg.res
	};
	for (int i = 0; i < 4; i++) {
		if (results[i] > res)
			res = results[i];
	}

	printf("Largest product: %d\n", res);
	return 0;
}


