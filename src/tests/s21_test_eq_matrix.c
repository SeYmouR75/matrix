#include "s21_test_matrix.h"

static int rows_normal[] = {3, 3, 1, 5, 2};
static int cols_normal[] = {3, 5, 6, 2, 5};

static double A_filler_normal[] = {4.324, 5, -445.343, 0.3242, -54.00001};
static double B_filler_normal[] = {4.324, 5, -445.342, 0.3422, -54.00001};

START_TEST(eq_normal_test){
    if (_i == 0){
        printf("\n\t______________\n");
        printf("\tNORMAL_VALS");
        printf("\n\t______________\n");
    }

    matrix_t A, B;
    bool expected, actual;
    s21_create_matrix(rows_normal[_i], cols_normal[_i], &A);
    s21_create_matrix(rows_normal[_i], cols_normal[_i], &B);

    fill_matrix(&A, A_filler_normal[_i]);
    fill_matrix(&B, B_filler_normal[_i]);

    expected = is_doubles_eq(A_filler_normal[_i], B_filler_normal[_i], 1e-6);
    actual = s21_eq_matrix(&A, &B);

    printf("\n_________\n");
    printf("value_1:%lf value_2:%lf\n",A_filler_normal[_i], B_filler_normal[_i]);
    printf("actual:%d expected:%d\n", actual, expected);
    printf("\n_________\n");

    ck_assert_int_eq(expected, actual);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}

static int rows_edge[] = {5, 0, -1, 3, 5, 5};
static int cols_edge[] = {0, 0, 5, 3, 4, 5};

static double A_filler_edge[] = {1, 0, 1.00000001, 324.4123142, 0, 1};
static double B_filler_edge[] = {1, 0, 0.00000001, 324.4123143, 0.000001, 1};

START_TEST(eq_edge_test){
    if (_i == 0){
        printf("\n\t______________\n");
        printf("\tEDGE_VALS");
        printf("\n\t______________\n");
    }

    matrix_t A, B;
    int res_A, res_B;
    bool expected, actual;
    res_A = s21_create_matrix(rows_edge[_i], cols_edge[_i], &A);
    if (_i > 4) 
        res_B = s21_create_matrix(rows_edge[_i] + 1, cols_edge[_i], &B);
    else 
        res_B = s21_create_matrix(rows_edge[_i], cols_edge[_i], &B);

    fill_matrix(&A, A_filler_edge[_i]);
    fill_matrix(&B, B_filler_edge[_i]);

    if (res_A == OK && res_B == OK) {
        expected = is_doubles_eq(A_filler_edge[_i], B_filler_edge[_i], 1e-6);
        actual = s21_eq_matrix(&A, &B);
    }else {
        expected = 0;
        actual = 0;
    }

    if (_i > 4) expected = 0;

    printf("\n_________\n");
    printf("value_1:%lf value_2:%lf\n",A_filler_edge[_i], B_filler_edge[_i]);
    printf("actual:%d expected:%d\n", actual, expected);
    printf("\n_________\n");

    ck_assert_int_eq(expected, actual);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}


Suite *suite_s21_eq_matrix(){
    Suite *suite = suite_create("suite_s21_eq_matrix");

    TCase *normal_case = tcase_create("case_s21_eq_matrix_normal");
    tcase_add_loop_test(normal_case, eq_normal_test, 0, sizeof(rows_normal) / sizeof(int));
    suite_add_tcase(suite, normal_case);

    TCase *edge_case = tcase_create("case_s21_eq_matrix_edge");
    tcase_add_loop_test(edge_case, eq_edge_test, 0, sizeof(rows_edge) / sizeof(int));
    suite_add_tcase(suite, edge_case);


    return suite;
}