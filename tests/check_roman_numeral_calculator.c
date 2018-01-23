#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "roman_numeral_calculator.h"

//operand1 operator operand2 = result
// I + I = II
typedef struct{ 
	char * operand1;
    char operator;    
	char * operand2;
	char * result;
}ROMAN_NUMERAL_TEST_OPERATION;


//To do: Read these in from files
static const ROMAN_NUMERAL_TEST_OPERATION romanNumeralTestOperations[2] = { 
                                                                            {"I", '+', "I", "II"},
                                                                            {"II", '+', "I", "III"}
                                                                          };

char roman_numeral_operation_valid(ROMAN_NUMERAL_TEST_OPERATION test){
    printf("Checking roman numeral operation: %s %c %s = %s \r\n", test.operand1, test.operator, test.operand2, test.result);
	return 1;
}


START_TEST (check_roman_numeral_operation)
{
    RomanNumeralCalculator * rnc;
    rnc = rnc_create();
    ck_assert (roman_numeral_operation_valid (romanNumeralTestOperations[_i]));
    rnc_free(rnc);
}
END_TEST


Suite * roman_numeral_calculator_test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RomanNumeralCalculator");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_loop_test (tc_core, check_roman_numeral_operation, 0, 2);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = roman_numeral_calculator_test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

