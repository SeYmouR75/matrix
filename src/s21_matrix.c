#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result){
    int flag = 0;
    if(rows <= 0 || columns <= 0){
        flag = INVALID_MATRIX;
    }
    result->matrix = NULL;
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if(result->matrix == NULL)
        flag = INVALID_MATRIX;
    for(int i = 0; i < rows; i++){
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
        if(result->matrix[i] == NULL)
            flag = INVALID_MATRIX;    
    }

    return flag;
}

void s21_remove_matrix(matrix_t *A){
    for(int i = 0; i < A->rows; i++){
        free(A->matrix[i]);
    }
    free(A->matrix);
    // for fun 
    A->rows = 0;
    A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B){
    int flag = SUCCESS;
    if(A->rows != B->rows) flag = FAILURE;
    if(A->columns != B->columns) flag = FAILURE;
    for(int i = 0; i < A->rows; i++){
        for(int j = 0; j < A->columns; j++){
            if(A->matrix[i][j] != B->matrix[i][j]) flag = FAILURE;
        }
    }

    return flag;
}