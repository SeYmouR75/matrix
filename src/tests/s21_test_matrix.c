#include "s21_test_matrix.h"

void run_suite(Suite *suite) {
  SRunner *sr = srunner_create(suite);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);  // CK_MINIMAL CK_NORMAL CK_VERBOSE

  srunner_free(sr);
}

void run_tests() {
  Suite *suites_core[] = {
        suite_s21_create_matrix(),   
        // suite_s21_remove_matrix(),  
        // suite_s21_eq_matrix(), 
        // suite_s21_sum_matrix(),   
        // suite_s21_sub_matrix(), 
        // suite_s21_mult_number(),  
        // suite_s21_mult_matrix(),   
        // suite_s21_transpose(),  
        // suite_s21_calc_complements(),  
        // suite_s21_determinant(),   
        // suite_s21_inverse_matrix(),
        NULL};

  for (Suite **cur = suites_core; *cur != NULL; cur++) {
    printf("\n==================================\n");
    run_suite(*cur);
    printf("\n==================================\n");
  }
}

int main() {
  run_tests();
  return 0;
}