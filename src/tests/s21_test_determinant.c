#include "s21_test_matrix.h"

START_TEST(determinant_test_2x2) {
    matrix_t m;
    s21_create_matrix(2, 2, &m);
    m.matrix[0][0] = 32.54;
    m.matrix[0][1] = 167.546;
    m.matrix[1][0] = 1368.67;
    m.matrix[1][1] = 134.032;

    double act_det = 0.0;
    double exp_det = -224953.78254;
    int res = s21_determinant(&m, &act_det);

    ck_assert_int_eq(res, OK);
    ck_assert_double_eq_tol(act_det, exp_det, ACCURACY);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_test_3x3) {
    matrix_t m;
    s21_create_matrix(3, 3, &m);
    m.matrix[0][0] = -5.345761;
    m.matrix[0][1] = 14.634432;
    m.matrix[0][2] = -7.154367;
    m.matrix[1][0] = 1.111111;
    m.matrix[1][1] = -3.345786;
    m.matrix[1][2] = 9.756643;
    m.matrix[2][0] = -10.101211;
    m.matrix[2][1] = 3.514411;
    m.matrix[2][2] = -44.756541;

    double act_det = 0.0;
    double exp_det = -1117.867605;
    int res = s21_determinant(&m, &act_det);

    ck_assert_int_eq(res, OK);
    ck_assert_double_eq_tol(act_det, exp_det, ACCURACY);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_test_4x4) {
    matrix_t m;
    s21_create_matrix(4, 4, &m);
    m.matrix[0][0] = 14.532;
    m.matrix[0][1] = 7.453;
    m.matrix[0][2] = -20.368;
    m.matrix[0][3] = -14.680;
    m.matrix[1][0] = 5.757;
    m.matrix[1][1] = 4.145;
    m.matrix[1][2] = -17.602;
    m.matrix[1][3] = 3.935;
    m.matrix[2][0] = 10.165;
    m.matrix[2][1] = 8.533;
    m.matrix[2][2] = -18.812;
    m.matrix[2][3] = -21.756;
    m.matrix[3][0] = -1.598;
    m.matrix[3][1] = 0.187;
    m.matrix[3][2] = -1.598;
    m.matrix[3][3] = -13.967;

    double act_det = 0.0;
    double exp_det = -6249.460171;
    int res = s21_determinant(&m, &act_det);

    ck_assert_int_eq(res, OK);
    ck_assert_double_eq_tol(act_det, exp_det, ACCURACY);

    s21_remove_matrix(&m);
}
END_TEST

Suite *suite_s21_determinant(){
    Suite *suite = suite_create("suite_s21_determinant");

    TCase *normal_case = tcase_create("case_s21_determinant");

    tcase_add_test(normal_case, determinant_test_2x2);
    tcase_add_test(normal_case, determinant_test_3x3);
    tcase_add_test(normal_case, determinant_test_4x4);

    suite_add_tcase(suite, normal_case);

    return suite;
}