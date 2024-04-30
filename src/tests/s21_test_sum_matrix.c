#include "s21_test_matrix.h"

static int rows_normal[] = {3, 3, 1, 5, 2, 0, 5, 6, 2};
static int cols_normal[] = {3, 5, 6, 2, 5, 5, 0, 4, 2};

START_TEST(sum_normal_test){
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

    s21_sum_matrix(&A, &B, &res);

    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < B.columns; j++){
            actual = res.matrix[i][j];
            expected = A.matrix[i][j] + B.matrix[i][j];
            ck_assert_double_eq(expected, actual);
            printf("\n_________\n");
            printf("actual:%lf expected:%lf\n", actual, expected);
        }
    }

    
    printf("\n_________\n");

    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}

// static int rows_edge[] = {5, 0, -1, 3, 5, 5};
// static int cols_edge[] = {0, 0, 5, 3, 4, 5};

// static double A_filler_edge[] = {1, 0, 1.00000001, 324.4123142, 0, 1};
// static double B_filler_edge[] = {1, 0, 0.00000001, 324.4123143, 0.000001, 1};

// START_TEST(sum_edge_test){
//     if (_i == 0){
//         printf("\n\t______________\n");
//         printf("\tEDGE_VALS");
//         printf("\n\t______________\n");
//     }

//     matrix_t A, B;
//     s21_create_matrix(rows_edge[_i], cols_edge[_i], &A);
//     s21_create_matrix(rows_edge[_i], cols_edge[_i], &B);

//     fill_matrix(&A, A_filler_edge[_i]);
//     fill_matrix(&B, B_filler_edge[_i]);

   
//     printf("\n_________\n");
//     printf("\n_________\n");


//     s21_remove_matrix(&A);
//     s21_remove_matrix(&B);
// }


Suite *suite_s21_sum_matrix(){
    Suite *suite = suite_create("suite_s21_sum_matrix");

    TCase *normal_case = tcase_create("case_s21_sum_matrix_normal");
    tcase_add_loop_test(normal_case, sum_normal_test, 0, sizeof(rows_normal) / sizeof(int));
    suite_add_tcase(suite, normal_case);

    // TCase *edge_case = tcase_create("case_s21_sum_matrix_edge");
    // tcase_add_loop_test(edge_case, sum_edge_test, 0, sizeof(rows_edge) / sizeof(int));
    // suite_add_tcase(suite, edge_case);


    return suite;
}