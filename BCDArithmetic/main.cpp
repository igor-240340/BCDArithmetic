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

    std::cout << std::format("{} * {} = {}\n", a.to_string(), b.to_string(), (a * b).to_string());
}

void test_multiplication() {
    std::cout << "MULTIPLICATION\n";

    test_multiplication_1();

    std::cout << '\n';
    test_multiplication_2();
}

int main() {
    /*
    test_addition();

    std::cout << '\n';
    test_subtraction();
    */

    std::cout << '\n';
    test_multiplication();

    return 0;
}