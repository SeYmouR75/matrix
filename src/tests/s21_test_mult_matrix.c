#include "s21_test_matrix.h"

static int rows_A[] = {5,3,2,5,7,5,1,2};
static int cols_A[] = {3,4,1,5,4,6,3,2};
static int rows_B[] = {3,4,1,5,4,6,3,2};
static int cols_B[] = {1,4,2,6,4,2,2,2};

START_TEST(mult_normal_test){
    if (_i == 0){
        printf("\n\t______________\n");
        printf("\tNORMAL_VALS");
        printf("\n\t______________\n");
    }

    matrix_t A, B, actual, expected;
    
    s21_create_matrix(rows_A[_i], cols_A[_i], &A);
    s21_create_matrix(rows_B[_i], cols_B[_i], &B);

    fill_matrix_rand(&A, rand() / 1000000);
    fill_matrix_rand(&B, rand() / 1000000);

    s21_mult_matrix(&A, &B, &actual);
    s21_create_matrix(A.rows, B.columns, &expected);
    
    ck_assert_int_eq(expected.rows, actual.rows);
    ck_assert_int_eq(expected.columns, actual.columns);

    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < B.columns; j++){
            for (int k = 0; k < A.columns; k++){
                expected.matrix[i][j] += accuracy_check(A.matrix[i][k], ACCURACY) * accuracy_check(B.matrix[k][j], ACCURACY);
            }
        }
    }

    printf("\n_________\n");
    print_matrix(&A);
    print_matrix(&B);
    print_matrix(&expected);
    printf("\n_________\n");

    for (int i = 0; i < expected.rows; i++){
        for (int j = 0; j < expected.columns; j++){
            ck_assert_double_eq_tol(expected.matrix[i][j], actual.matrix[i][j], ACCURACY);
        }
    }
}

// static int rows_edge[] = {5, 0, 3, 5, 5};
// static int cols_edge[] = {0, 0, 3, 4, 5};

// static double A_filler_edge[] = {1, 1, 0, 0, 0};
// static double B_filler_edge[] = {1, 1, 0, 0.00000001, -0};

// START_TEST(mult_edge_test){
//     if (_i == 0){
//         printf("\n\t______________\n");
//         printf("\tEDGE_VALS");
//         printf("\n\t______________\n");
//     }

//     matrix_t A, B, res;
//     double actual, expected;
//     s21_create_matrix(rows_edge[_i], cols_edge[_i], &A);
//     s21_create_matrix(rows_edge[_i], cols_edge[_i], &B);

//     fill_matrix(&A, A_filler_edge[_i]);
//     fill_matrix(&B, B_filler_edge[_i]);

//     s21_mult_matrix(&A, &B, &res);

//     // printf("\n_________\n");
//     // print_matrix(&A);
//     // print_matrix(&B);
//     // print_matrix(&res);

//     for (int i = 0; i < A.rows; i++){
//         for (int j = 0; j < A.columns; j++){
//             actual = res.matrix[i][j];
//             expected = accuracy_check(A.matrix[i][j], ACCURACY) * accuracy_check(B.matrix[i][j], ACCURACY);

//             ck_assert_double_eq(expected, actual);

//             // printf("actual:%lf expected:%lf\n", actual, expected);
//         }
//     }

//     // printf("\n_________\n");

//     s21_remove_matrix(&res);   
//     s21_remove_matrix(&A);
//     s21_remove_matrix(&B);
// }


Suite *suite_s21_mult_matrix(){
    Suite *suite = suite_create("suite_s21_mult_matrix");

    TCase *normal_case = tcase_create("case_s21_mult_matrix_normal");
    tcase_add_loop_test(normal_case, mult_normal_test, 0, sizeof(rows_A) / sizeof(int));
    suite_add_tcase(suite, normal_case);

    // TCase *edge_case = tcase_create("case_s21_mult_matrix_edge");
    // tcase_add_loop_test(edge_case, mult_edge_test, 0, sizeof(rows_edge) / sizeof(int));
    // suite_add_tcase(suite, edge_case);


    return suite;
}