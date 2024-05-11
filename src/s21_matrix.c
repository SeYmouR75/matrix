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

// int s21_calc_complements(matrix_t *A, matrix_t *result){
//     if (A->matrix == NULL) return INVALID_MATRIX;

//     res_code res = s21_create_matrix(A->rows, A->columns, result);
    
//     if (res == OK){
//         for (int i =0; i < A->rows; i++){
//             for (int j = 0; j < A->columns; j++){
//                 result->matrix[i][j] = 
//             }
//         }
//     }
// }

int s21_determinant(matrix_t *A, double *result){
    if (A->matrix == NULL) return INVALID_MATRIX;
    
    if (A->rows != A->columns) return INVALID_CALCULATIONS;

    matrix_t copy;
    res_code creation_res = s21_create_matrix(A->rows, A->columns, &copy);

    if (creation_res == OK){
        *result = 1.0;

        for (int i = 0; i < copy.rows; i++){
            for (int j = 0; j < copy.columns; j++){
                copy.matrix[i][j] = A->matrix[i][j];
            }
        }

        for (int i = 0; i < copy.rows; i++){

            int max_row = i;
            for (int j = i + 1; j < copy.columns; j++){
                if (fabs(copy.matrix[j][i]) > fabs(copy.matrix[max_row][i])){
                    max_row = j;
                }
            }

            if (i != max_row){
                for (int j = 0; j < copy.columns; j++){
                    double tmp = copy.matrix[i][j];
                    copy.matrix[i][j] = copy.matrix[max_row][i];
                    copy.matrix[max_row][i] = tmp;
                }
                *result *= -1;
            }

            for (int j = i + 1; j < copy.columns; j++){
                if(copy.matrix[i][i] == 0){
                    int nonzero_row = -1;
                    for (int k = i + 1; k < copy.columns && nonzero_row == -1; k++){
                        if (copy.matrix[k][j] != 0){
                            nonzero_row = k;
                        }
                    }

                    if (nonzero_row != -1){
                        for (int k = 0; k < copy.columns; k++){
                            double tmp = copy.matrix[i][k];
                            copy.matrix[i][k] = copy.matrix[nonzero_row][k];
                            copy.matrix[nonzero_row][k] = tmp;
                        }
                        *result *= -1;

                        for (int j = 0; j < i; j++) {
                            double temp = copy.matrix[j][i];
                            copy.matrix[j][i] = copy.matrix[j][nonzero_row];
                            copy.matrix[j][nonzero_row] = temp;
                        }
                    }else {
                        *result = 0;
                    }
                }
                double coefficient = copy.matrix[j][i] / copy.matrix[i][i];
                for (int k = i; k < copy.columns; k++){
                    copy.matrix[j][k] -= coefficient * copy.matrix[i][k];
                }
            }
        }

        for (int i = 0; i < A->rows; i++){
            printf("\n\n result %d = %lf \n\n", i, *result);
            *result *= copy.matrix[i][i];
        }

        s21_remove_matrix(&copy);
    }

    return creation_res;
}