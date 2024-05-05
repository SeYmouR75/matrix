#include "s21_test_matrix.h"

static int rows_normal[] = {3, 3, 1, 5, 2, 1, 5, 6, 2};
static int cols_normal[] = {3, 5, 6, 2, 5, 5, 1, 4, 2};

START_TEST(sub_normal_test){
    if (_i == 0){
        printf("\n\t______________\n");
        printf("\tNORMAL_VALS");
        printf("\n\t______________\n");
    }

    matrix_t A, B, res;
    double actual, expected;
    s21_create_matrix(rows_normal[_i], cols_normal[_i], &A);
    s21_create_matrix(rows_normal[_i], cols_normal[_i], &B);

    fill_matrix_rand(&A, rand());
    fill_matrix_rand(&B, rand());

    s21_sub_matrix(&A, &B, &res);

    printf("\n_________\n");
    print_matrix(&A);
    print_matrix(&B);
    print_matrix(&res);
    
    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < A.columns; j++){
            actual = res.matrix[i][j];
            expected = A.matrix[i][j] - B.matrix[i][j];
            ck_assert_double_eq(expected, actual);
            printf("actual:%lf expected:%lf\n", actual, expected);
        }
    }

    
    printf("\n_________\n");

    s21_remove_matrix(&res);    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}

static int rows_edge[] = {5, 0, 3, 5, 5};
static int cols_edge[] = {0, 0, 3, 4, 5};

static double A_filler_edge[] = {1, 1, 0, 0, 0};
static double B_filler_edge[] = {1, 1, 0, 0.00000001, -0};

START_TEST(sub_edge_test){
    if (_i == 0){
        printf("\n\t______________\n");
        printf("\tEDGE_VALS");
        printf("\n\t______________\n");
    }

    matrix_t A, B, res;
    double actual, expected;
    s21_create_matrix(rows_edge[_i], cols_edge[_i], &A);
    s21_create_matrix(rows_edge[_i], cols_edge[_i], &B);

    fill_matrix(&A, A_filler_edge[_i]);
    fill_matrix(&B, B_filler_edge[_i]);

    s21_sub_matrix(&A, &B, &res);

    printf("\n_________\n");
    print_matrix(&A);
    print_matrix(&B);
    print_matrix(&res);

    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < A.columns; j++){
            actual = res.matrix[i][j];
            expected = A.matrix[i][j] - B.matrix[i][j];
            ck_assert_double_eq(expected, actual);
            printf("actual:%lf expected:%lf\n", actual, expected);
        }
    }

    printf("\n_________\n");

    s21_remove_matrix(&res);   
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}


Suite *suite_s21_sub_matrix(){
    Suite *suite = suite_create("suite_s21_sub_matrix");

    TCase *normal_case = tcase_create("case_s21_sub_matrix_normal");
    tcase_add_loop_test(normal_case, sub_normal_test, 0, sizeof(rows_normal) / sizeof(int));
    suite_add_tcase(suite, normal_case);

    TCase *edge_case = tcase_create("case_s21_sub_matrix_edge");
    tcase_add_loop_test(edge_case, sub_edge_test, 0, sizeof(rows_edge) / sizeof(int));
    suite_add_tcase(suite, edge_case);


    return suite;
}