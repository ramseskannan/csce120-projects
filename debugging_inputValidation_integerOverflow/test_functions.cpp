/*
This is a driver for testing the functions.
You should add tests.
*/

#include <iostream>
#include <string>
#include "functions.h"

// these are test helpers.  cool, right?
#define report_unexpected_exception std::cout << "[FAIL] (" << __func__ << ":" << __LINE__ << ") caught an unexpected exception." << std::endl; throw;
#define report_mismatch(expression,expected,actual) std::cout << "[FAIL] (" << __func__ << ":" << __LINE__ << ") expected " << expression << " to be " << expected << ", got " << actual << std::endl;

#define expect_eq(A,X) {\
int64_t actual, expected;\
try { actual = A; expected = X; } catch (...) { report_unexpected_exception }\
if (!(actual == expected)) { report_mismatch(#A,expected,actual) } }

#define expect_true(A) {\
bool actual;\
try { actual = A; } catch (...) { report_unexpected_exception }\
if (!actual) { report_mismatch(#A,"true","false") } }

#define expect_false(A) {\
bool actual;\
try { actual = A; } catch (...) { report_unexpected_exception }\
if (actual) { report_mismatch(#A,"false","true") } }

#define expect_throw(A,X) {\
try { A; report_mismatch(#A,"\b\b\bthrow " + std::string(#X),"nothing") } catch (const X& err) {  } catch (...) { report_unexpected_exception } }

/*
test helper usage examples:
expect_eq(1 + 2, 3);
expect_true(1 + 2 == 3);
expect_false(1 + 2 == 4);
expect_throw(throw std::invalid_argument("hi"), std::invalid_argument);
*/

void test_largest() {
    // largest(3, 2, 1) should return 3
    expect_eq(largest(1, 2, 3), 3);
}

void test_sum_is_even() {
    // sum_is_even(3, 5) should return true
    expect_true(sum_is_even(3, 5));
}

void test_boxes_needed() {
    // boxes_needed(-13) should return 0
    expect_eq(boxes_needed(13), 1);
}

void test_smarter_section() {
    // smarter_section(40, 50, 75, 100) should return true
    expect_true(smarter_section(40, 50, 75, 100));
}

void test_good_dinner() {
    // good_dinner(13, false) should return true
    expect_true(good_dinner(13, false));
}

void test_sum_between() {
    // sum_between(1, 10) should return 55
    expect_eq(sum_between(1, 10), 55);
}

void test_product() {
    // product(2, 2) should return 4
    expect_eq(product(2, 2), 4);
}

int main() {
    test_largest();
    test_sum_is_even();
    test_boxes_needed();
    test_smarter_section();
    test_good_dinner();
    test_sum_between();
    test_product();

    return 0;
}
