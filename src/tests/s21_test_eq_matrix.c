#include "s21_test_matrix.h"

static int rows_normal[] = {3, 3, 1, 5, 2};
static int cols_normal[] = {3, 5, 6, 2, 5};

static double A_filler_normal[] = {4.324, 5, -445.343, 0.3242, -54.00001};
static double B_filler_normal[] = {4.324, 5, -445.342, 0.3422, -54.00001};

START_TEST(eq_normal_test){
    matrix_t A, B;
    s21_create_matrix(rows_normal[_i], cols_normal[_i], &A);
    s21_create_matrix(rows_normal[_i], cols_normal[_i], &B);

    s21_fill_matrix(&A, A_filler_normal[_i]);
    s21_fill_matrix(&B, B_filler_normal[_i]);
    
    ck_assert_int_eq(is_doubles_eq(A_filler_normal[_i], B_filler_normal[_i], 1e-6), s21_eq_matrix(&A, &B));
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}

static int rows_edge[] = {0, -1, 3, 5, 5};
static int cols_edge[] = {0, 5, 3, 4, 5};

static double A_filler_edge[] = {0, 1.00000001, 324.4123142, 0, 1};
static double B_filler_edge[] = {0, 0.00000001, 324.4123143, 0.00000001, 1};

START_TEST(eq_edge_test){
    matrix_t A, B;
    s21_create_matrix(rows_edge[_i], cols_edge[_i], &A);
    if (_i > 3) 
        s21_create_matrix(rows_edge[_i] + 1, cols_edge[_i], &B);
    else 
        s21_create_matrix(rows_edge[_i], cols_edge[_i], &B);

    s21_fill_matrix(&A, A_filler_edge[_i]);
    s21_fill_matrix(&B, B_filler_edge[_i]);

    ck_assert_int_eq(is_doubles_eq(A_filler_edge[_i], B_filler_edge[_i], 1e-6), s21_eq_matrix(&A, &B));

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