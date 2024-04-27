#include "s21_test_matrix.h"

static int normal_vals[] = {5, 5, 6, 7, 1, 1, 4, 5, 2, 5};

START_TEST(remove_normal_test){
    if(_i == 0){
        printf("\n\t______________\n");
        printf("\tNORMAL_VALS");
        printf("\n\t______________\n");
    }

    int rows = normal_vals[_i];
    _i++;
    int columns = normal_vals[_i];

    printf("\n_________\n");
    printf("iteration:%d start.rows:%d start.cols:%d\n", _i - 1, rows, columns);

    matrix_t actual;
    s21_create_matrix(rows, columns, &actual);
    s21_fill_matrix(&actual, 1.32);
    s21_remove_matrix(&actual);
    ck_assert_ptr_null(actual.matrix);
    ck_assert_int_eq(actual.rows, 0);
    ck_assert_int_eq(actual.columns, 0);

    printf("act.rows:%d act.cols:%d", actual.rows, actual.columns);
    printf("\n_________\n");
}
END_TEST

static int edge_vals[] = {-1, 0, 0, -3, -3, 4, 0.132, 2, 0.0001};

START_TEST(remove_edge_test){
    if(_i == 0){
        printf("\n\t______________\n");
        printf("\tEDGE_VALS");
        printf("\n\t______________\n");
    }

    int rows = normal_vals[_i];
    _i++;
    int columns = normal_vals[_i];

    printf("\n_________\n");
    printf("iteration:%d start.rows:%d start.cols:%d\n", _i - 1, rows, columns);

    matrix_t actual;
    s21_create_matrix(rows, columns, &actual);
    s21_fill_matrix(&actual, 1.32);
    s21_remove_matrix(&actual);
    ck_assert_ptr_null(actual.matrix);
    ck_assert_int_eq(actual.rows, 0);
    ck_assert_int_eq(actual.columns, 0);

    printf("act.rows:%d act.cols:%d", actual.rows, actual.columns);
    printf("\n_________\n");
}
END_TEST

Suite *suite_s21_remove_matrix(){
    Suite *suite = suite_create("suite_s21_remove_matrix");

    TCase *normal_case = tcase_create("case_s21_remove_matrix_normal");
    tcase_add_loop_test(normal_case, remove_normal_test, 0, sizeof(normal_vals) / sizeof(int) - 1);
    suite_add_tcase(suite, normal_case);

    TCase *edge_case = tcase_create("case_s21_remove_matrix_edge");
    tcase_add_loop_test(edge_case, remove_edge_test, 0, sizeof(edge_vals) / sizeof(int) - 1);
    suite_add_tcase(suite, edge_case);


    return suite;
}