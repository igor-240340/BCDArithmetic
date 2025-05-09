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

void test_division() {
    std::cout << "DIVISION\n";

    test_division_1();

    /*
    std::cout << '\n';
    test_division_2();
    */
}

int main() {
    /*
    test_addition();

    std::cout << '\n';
    test_subtraction();

    std::cout << '\n';
    test_multiplication();
    */

    std::cout << '\n';
    test_division();

    return 0;
}
