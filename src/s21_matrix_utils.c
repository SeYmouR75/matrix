#include "s21_matrix.h"

void fill_matrix(matrix_t *result, double value){
    if (result == NULL) exit(EXIT_FAILURE);
    if (result->matrix == NULL) exit(EXIT_FAILURE);

    for (int i = 0; i < result->rows; i++){
        for (int j = 0; j < result->columns; j++){
            result->matrix[i][j] = value;
        }
    }
}

void fill_matrix_rand(matrix_t *result, double entropy){
    if (result == NULL) exit(EXIT_FAILURE);
    if (result->matrix == NULL) exit(EXIT_FAILURE);

    for (int i = 0; i < result->rows; i++){
        for (int j = 0; j < result->columns; j++){
            result->matrix[i][j] = (double)rand() / ((double)RAND_MAX + 1) * entropy;
        }
    }
}

void print_matrix(matrix_t *A){
    for (int i = 0; i < A->rows; i++){
        for (int j = 0; j < A->columns; j++){
            printf("%lf ", A->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool is_doubles_eq(double a, double b, double EPS){
    return (fabs(a - b) < EPS);
}