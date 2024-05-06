#include "s21_test_matrix.h"

static int rows[] = {3, 3, 1, 5, 2, 1, 5, 6, 2, 4};
static int cols[] = {3, 5, 6, 2, 5, 5, 1, 4, 2, 4};

double multipliers[] = {5, 324, 6578.96578, 10000.100, -543.1535, 0, 1.11111, 0.1, -0.1, 0.0000001};

START_TEST(mult_number_normal_test){
    if (_i == 0){
        printf("\n\t______________\n");
        printf("\tNORMAL_VALS");
        printf("\n\t______________\n");
    }

    matrix_t A, res;
    double actual, expected, number;
    s21_create_matrix(rows[_i], cols[_i], &A);

    fill_matrix_rand(&A, rand());

    number = accuracy_check(multipliers[_i], ACCURACY);

    s21_mult_number(&A, number, &res);

    // printf("\n_________\n");
    // print_matrix(&A);
    // printf("number:%lf\n", number);
    // print_matrix(&res);
    
    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < A.columns; j++){
            actual = res.matrix[i][j];
            expected = accuracy_check(A.matrix[i][j], ACCURACY) * number;

            // printf("actual:%lf expected:%lf\n", actual, expected);
            
            ck_assert_double_eq(expected, actual);
        }
    }

    
    // printf("\n_________\n");

    s21_remove_matrix(&res);    
    s21_remove_matrix(&A);
}

Suite *suite_s21_mult_number(){
    Suite *suite = suite_create("suite_s21_mult_number");

    TCase *normal_case = tcase_create("case_s21_mult_number");
    tcase_add_loop_test(normal_case, mult_number_normal_test, 0, sizeof(rows) / sizeof(int));
    suite_add_tcase(suite, normal_case);


    return suite;
}