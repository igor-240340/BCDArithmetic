#include <iostream>
#include <format>

#include "BCD.h"

void test_addition_1() {
    BCD a("116.45");
    BCD b("37374.042");

    std::cout << std::format("{} + {} = {}\n", a.to_string(), b.to_string(), (a + b).to_string());
}

void test_addition_2() {
    BCD a("116.45");
    BCD b("-37374.042");

    std::cout << std::format("{} + {} = {}\n", a.to_string(), b.to_string(), (a + b).to_string());
}

void test_addition_3() {
    BCD a("-116.45");
    BCD b("37374.042");

    std::cout << std::format("{} + {} = {}\n", a.to_string(), b.to_string(), (a + b).to_string());
}

void test_addition_4() {
    BCD a("-116.45");
    BCD b("-37374.042");

    std::cout << std::format("{} + {} = {}\n", a.to_string(), b.to_string(), (a + b).to_string());
}

void test_subtraction_1() {
    BCD a("116.45");
    BCD b("37374.042");

    std::cout << std::format("{} - {} = {}\n", a.to_string(), b.to_string(), (a - b).to_string());
}

void test_subtraction_2() {
    BCD a("-116.45");
    BCD b("37374.042");

    std::cout << std::format("{} - {} = {}\n", a.to_string(), b.to_string(), (a - b).to_string());
}

void test_subtraction_3() {
    BCD a("116.45");
    BCD b("-37374.042");

    std::cout << std::format("{} - {} = {}\n", a.to_string(), b.to_string(), (a - b).to_string());
}

void test_subtraction_4() {
    BCD a("-116.45");
    BCD b("-37374.042");

    std::cout << std::format("{} - {} = {}\n", a.to_string(), b.to_string(), (a - b).to_string());
}

void test_addition() {
    std::cout << "ADDITION\n";

    test_addition_1();

    std::cout << '\n';
    test_addition_2();

    std::cout << '\n';
    test_addition_3();

    std::cout << '\n';
    test_addition_4();
}

void test_subtraction() {
    std::cout << "SUBTRACTION\n";

    test_subtraction_1();

    std::cout << '\n';
    test_subtraction_2();

    std::cout << '\n';
    test_subtraction_3();

    std::cout << '\n';
    test_subtraction_4();
}

void test_multiplication_1() {
    BCD a("116.45");
    BCD b("37374.042");

    std::cout << std::format("{} * {} = {}\n", a.to_string(), b.to_string(), (a * b).to_string());
}

void test_multiplication_2() {
    BCD a("37374.042");
    BCD b("37374.042");

    // True prod is 1396819015.417764, but after packing into uint32_t we have 13968190.
    std::cout << std::format("{} * {} = {}\n", a.to_string(), b.to_string(), (a * b).to_string());
}

void test_multiplication_3() {
    BCD a("-116.45");
    BCD b("37374.042");

    std::cout << std::format("{} * {} = {}\n", a.to_string(), b.to_string(), (a * b).to_string());
}

void test_multiplication_4() {
    BCD a("-116.45");
    BCD b("-37374.042");

    std::cout << std::format("{} * {} = {}\n", a.to_string(), b.to_string(), (a * b).to_string());
}

void test_multiplication_5() {
    BCD a("0.0020013");
    BCD b("-0.042");

    std::cout << std::format("{} * {} = {}\n", a.to_string(), b.to_string(), (a * b).to_string());
}

void test_multiplication() {
    std::cout << "MULTIPLICATION\n";

    test_multiplication_1();

    std::cout << '\n';
    test_multiplication_2();

    std::cout << '\n';
    test_multiplication_3();

    std::cout << '\n';
    test_multiplication_4();

    std::cout << '\n';
    test_multiplication_5();
}

void test_division_1() {
    BCD a("116.45");
    BCD b("37374.042");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

// Save integer part but truncate fractional.
void test_division_2() {
    BCD a("37374.042");
    BCD b("0.0302729");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

// Min quotient = 0.000000000000001 but truncates to 0.0000000.
void test_division_3() {
    BCD a("0.0000001");
    BCD b("99999999");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

// Max quotient = 999999990000000.0000000 but truncates to 99999999.
void test_division_4() {
    BCD a("99999999");
    BCD b("0.0000001");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division_5() {
    BCD a("12.3445");
    BCD b("12345.042");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division_6() {
    BCD a("0.308513");
    BCD b("0.00023");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division_7() {
    BCD a("0.00023");
    BCD b("0.308513");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division_8() {
    BCD a("54789.321");
    BCD b("9.12475");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division_9() {
    BCD a("123.4567");
    BCD b("0.0001");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division_10() {
    BCD a("123.45678");
    BCD b("0.00001");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division_11() {
    BCD a("123.2343");
    BCD b("3.737425");

    std::cout << std::format("{} / {} = {}\n", a.to_string(), b.to_string(), (a / b).to_string());
}

void test_division() {
    std::cout << "DIVISION\n";

    test_division_1();

    std::cout << '\n';
    test_division_2();

    std::cout << '\n';
    test_division_3();

    std::cout << '\n';
    test_division_4();

    std::cout << '\n';
    test_division_5();

    std::cout << '\n';
    test_division_6();

    std::cout << '\n';
    test_division_7();

    std::cout << '\n';
    test_division_8();

    std::cout << '\n';
    test_division_9();

    std::cout << '\n';
    test_division_10();

    std::cout << '\n';
    test_division_11();
}

int main() {
    test_addition();

    std::cout << '\n';
    test_subtraction();

    std::cout << '\n';
    test_multiplication();

    std::cout << '\n';
    test_division();

    return 0;
}
