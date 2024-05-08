#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result){

    if ((rows <= 0 || columns <= 0)){
        result->columns = 0;
        result->rows = 0;
        return INVALID_MATRIX;
    }
    
    res_code res = OK;

    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)malloc(rows * sizeof(double *));

    if (result->matrix == NULL) res = INVALID_MATRIX;

    for (int i = 0; (i < rows) && (res == OK); i++){
        result->matrix[i] = (double *)malloc(columns * sizeof(double));

        if(result->matrix[i] == NULL)
            res = INVALID_MATRIX;    
    }

    return res;
}

void s21_remove_matrix(matrix_t *A){
    if (A == NULL) return;
    if (A->matrix == NULL) return;
    if ((A->rows == 0) || (A->columns == 0)) return;
    
    for (int i = 0; i < A->rows; i++){
        free(A->matrix[i]);
    }

    free(A->matrix);

    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B){
    if ((A == NULL) || (B == NULL)) return false;
    if ((A->rows != B->rows) || (A->columns != B->columns)) return false;

    for (int i = 0; i < A->rows; i++){
        for (int j = 0; j < A->columns; j++){
            if (!is_doubles_eq(A->matrix[i][j], B->matrix[i][j], 1e-6)) return false;
        }
    }

    return true;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    if (A->matrix == NULL || B->matrix == NULL) return INVALID_MATRIX;

    if (A->rows != B->rows) return INVALID_CALCULATIONS;
    if (A->columns != B->columns) return INVALID_CALCULATIONS;

    res_code res = s21_create_matrix(A->rows, A->columns, result);

    if (res == OK){
        for (int i = 0; i < A->rows; i++){
            for (int j = 0; j < A->columns; j++){
                result->matrix[i][j] = accuracy_check(A->matrix[i][j], ACCURACY) + accuracy_check(B->matrix[i][j], ACCURACY);
            }
        }
    }

    return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    if (A->matrix == NULL || B->matrix == NULL) return INVALID_MATRIX;

    if (A->rows != B->rows) return INVALID_CALCULATIONS;
    if (A->columns != B->columns) return INVALID_CALCULATIONS;

    res_code res = s21_create_matrix(A->rows, A->columns, result);

    if (res == OK){
        for (int i = 0; i < A->rows; i++){
            for (int j = 0; j < A->columns; j++){
                result->matrix[i][j] = accuracy_check(A->matrix[i][j], ACCURACY) - accuracy_check(B->matrix[i][j], ACCURACY);
            }
        }
    }
        
    return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result){
    if (A->matrix == NULL) return INVALID_MATRIX;

    res_code res = s21_create_matrix(A->rows, A->columns, result);

    if (res == OK){
        number = accuracy_check(number, ACCURACY);
        for (int i = 0; i < A->rows; i++){
            for (int j = 0; j < A->columns; j++){
                result->matrix[i][j] = accuracy_check(A->matrix[i][j], ACCURACY) * number;
            }
        }
    }

    return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    if (A->matrix == NULL || B->matrix == NULL) return INVALID_MATRIX;

    if (A->columns != B->rows) return INVALID_CALCULATIONS;

    res_code res = s21_create_matrix(A->rows, B->columns, result);

    if (res == OK){
        double sum;
        for (int i = 0; i < A->rows; i++){
            for (int j = 0; j < B->columns; j++){
                sum = 0;
                for (int k = 0; k < A->columns; k++){
                    sum += accuracy_check(A->matrix[i][k], ACCURACY) * accuracy_check(B->matrix[k][j], ACCURACY);
                }
                result->matrix[i][j] = sum;
            }
        }
    }

    return res;
}

int s21_transpose(matrix_t *A, matrix_t *result){
    if (A->matrix == NULL) return INVALID_MATRIX;

    res_code res = s21_create_matrix(A->columns, A->rows, result);

    if (res == OK){
        for (int i = 0; i < A->rows; i++){
            for (int j = 0; j < A->columns; j++){
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    }

    return res;
}