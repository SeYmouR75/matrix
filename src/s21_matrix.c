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
                result->matrix[j][i] = accuracy_check(A->matrix[i][j], ACCURACY);
            }
        }
    }

    return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result){
    if (A->matrix == NULL) return INVALID_MATRIX;
    if (A->rows != A->columns) return INVALID_CALCULATIONS;

    res_code res = s21_create_matrix(A->rows, A->columns, result);
    
    if (res != OK) return res;

    if (A->rows == 1){
        result->matrix[0][0] = accuracy_check(A->matrix[0][0], ACCURACY);
    } else{
        double det = 0;
        int sign = 0;
        matrix_t sub;
        res = s21_create_matrix(A->rows - 1, A->columns - 1, &sub);

        for (int i = 0; i < A->rows; i++){
            for (int j = 0; j < A->columns; j++){
                split_to_sub(*A, &sub, i, j);
                print_matrix(&sub);
                s21_determinant(&sub, &det);
                printf("det: %lf\n\n", det);
                sign = ((i + j) % 2 == 0) ? 1 : -1;
                result->matrix[i][j] = det * sign;
            }
        }

        s21_remove_matrix(&sub);
    }
    return res;
}

int s21_determinant(matrix_t *A, double *result) {
    if (A->matrix == NULL) return INVALID_MATRIX;
    if (A->rows != A->columns) return INVALID_CALCULATIONS;

    if (A->rows == 1){
        *result = accuracy_check(A->matrix[0][0], ACCURACY);
    } else if (A->rows == 2){
        *result = accuracy_check(A->matrix[0][0], ACCURACY) * accuracy_check(A->matrix[1][1], ACCURACY) - accuracy_check(A->matrix[0][1], ACCURACY) * accuracy_check(A->matrix[1][0], ACCURACY);
    } else {
        matrix_t sub;
        res_code res = s21_create_matrix(A->rows - 1, A->columns - 1, &sub);

        if (res != OK) return res;

        *result = 0;
        int sign = 1;

        for (int i = 0; i < A->rows; i++){

            split_to_sub(*A, &sub, 0, i);

            double rec_det = 0.0;
            s21_determinant(&sub, &rec_det);
            *result += sign * accuracy_check(A->matrix[0][i], ACCURACY) * rec_det;
            sign *= -1;
        }
        s21_remove_matrix(&sub);
    }

    return OK;
}
