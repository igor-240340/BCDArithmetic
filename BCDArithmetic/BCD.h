#pragma once

#include <string>
#include <array>
#include <vector>
#include <algorithm>

// Binary-coded decimal.
// NOTE: Decimal point is fixed only for one operand,
// so you can for example represent both 1.2345 and 1234.5.
class BCD {
public:
    BCD() = default;

    BCD(const std::string& str) {
        size_t dot_pos = str.find('.');
        std::string int_part = (dot_pos == std::string::npos) ? str : str.substr(0, dot_pos);
        std::string frac_part = (dot_pos == std::string::npos) ? "" : str.substr(dot_pos + 1);

        if (int_part[0] == '-') {
            is_negative = true;
            int_part = int_part.substr(1);
        }

        frac_digits_count = frac_part.size();

        std::string all_digits = int_part + frac_part;
        const size_t total_digits = all_digits.size();
        for (int i = 0; i < total_digits; i++) {
            rep |= (all_digits[total_digits - 1 - i] - '0') << (i * 4);
        }
    }

    // NOTE: We don't care about correct decimal rounding when aligns operands before addition -
    // just truncate the longest fractional part to the shortest one.
    // The latest means that we can get not the best possible precision in 32 bit representation.
    BCD operator+(const BCD& right_op) const {
        BCD left_op_copy = *this;
        BCD right_op_copy = right_op;
        BCD res;

        res.frac_digits_count = std::min(left_op_copy.frac_digits_count, right_op_copy.frac_digits_count);

        left_op_copy.truncate_frac_to(res.frac_digits_count);
        right_op_copy.truncate_frac_to(res.frac_digits_count);

        const bool both_positive = !left_op_copy.is_negative && !right_op_copy.is_negative;
        const bool both_negative = left_op_copy.is_negative && right_op_copy.is_negative;
        const bool same_signs = both_positive || both_negative;
        if (same_signs) {
            res.is_negative = left_op_copy.is_negative; // Take the sign of any operand.

            int carry = 0;
            for (int i = 0; i < 8; i++) {
                int digit_lh = (left_op_copy.rep >> (i * 4)) & 0xf;
                int digit_rh = (right_op_copy.rep >> (i * 4)) & 0xf;

                int sum = digit_lh + digit_rh + carry;

                carry = sum / 10;
                sum = sum % 10;
                res.rep = res.rep | (static_cast<uint32_t>(sum) << (i * 4));
            }

            // NOTE: If carry is not zero here then we've got an overflow.
        }
        else {
            if (left_op_copy.rep < right_op_copy.rep) {
                std::swap(left_op_copy, right_op_copy);
            }
            // Take the sign of the operand with the largest absolute value.
            res.is_negative = left_op_copy.is_negative;

            int borrow = 0;
            for (int i = 0; i < 8; i++) {
                int digit_l = (left_op_copy.rep >> (i * 4)) & 0xf;
                int digit_r = (right_op_copy.rep >> (i * 4)) & 0xf;

                int diff = (digit_l - borrow) - digit_r;
                if (diff >= 0)
                    borrow = 0;
                else {
                    diff += 10;
                    borrow = 1;
                }

                res.rep = res.rep | (static_cast<uint32_t>(diff) << (i * 4));
            }
        }

        return res;
    };

    BCD operator-(const BCD& right_op) const {
        BCD right_op_copy = right_op;
        right_op_copy.is_negative = !right_op_copy.is_negative; // a - b = a + -b.

        return *this + right_op_copy;
    };

    // NOTE: We don't care about an overflow.
    BCD operator*(const BCD& right_op) const {
        BCD left_op_copy = *this;
        BCD right_op_copy = right_op;

        // Extract decimal digits from least significant to most significant.
        std::array<int, 8> left_op_digits, right_op_digits;
        for (int i = 0; i < 8; i++) {
            left_op_digits[i] = (left_op_copy.rep >> (i * 4)) & 0xf;
            right_op_digits[i] = (right_op_copy.rep >> (i * 4)) & 0xf;
        }

        // Long multiplication without carry.
        std::array<int, 16> result_digits{};
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                result_digits[i + j] += right_op_digits[i] * left_op_digits[j];
            }
        }

        // Carry propagation.
        for (int i = 0; i < 15; ++i) {
            if (result_digits[i] >= 10) {
                result_digits[i + 1] += result_digits[i] / 10;
                result_digits[i] = result_digits[i] % 10;
            }
        }

        // Temporarily pack true product without any loss.
        int prod_frac_count = left_op_copy.frac_digits_count + right_op_copy.frac_digits_count;
        uint64_t extended_rep = 0;
        int packed_cnt = 0;
        for (int i = 15; i >= 0; i--) {
            const int current_digit = result_digits[i];
            const int first_non_frac_digit_index = prod_frac_count;
            // Skip only leading zero digits except one leading zero of the integer part if result < 1.
            if (current_digit == 0 && extended_rep == 0 && i > first_non_frac_digit_index)
                continue;

            extended_rep = extended_rep | static_cast<uint64_t>(current_digit) << (i * 4);
            packed_cnt++;
        }
        // Align to fit into 32 bit.
        if (packed_cnt > 8) {
            const int diff = packed_cnt - 8;
            extended_rep = extended_rep >> diff * 4;
            prod_frac_count -= diff;

            // Totally lost fractional part.
            // So, we will print only high-order part of the true product.
            if (prod_frac_count < 0)
                prod_frac_count = 0;
        }

        BCD res;
        res.rep = static_cast<uint32_t>(extended_rep);
        res.frac_digits_count = prod_frac_count;
        res.is_negative = left_op_copy.is_negative ^ right_op_copy.is_negative;

        return res;
    };

    // Naive decimal long division.
    // NOTE: Internally it calculates the true quotient with 7 decimal digits
    // but then packes only 8 digits starting with the integer part.
    // So, it can truncate fractional part and even the lower part of the integer part.
    //
    // It can also be optimized by maintaining scaled divisor immovable as we usually do in a binary division
    // but we don't care as it's purely educational project to catch the concepts.
    BCD operator/(const BCD& right_op) const {
        BCD left_op_copy = *this;
        BCD right_op_copy = right_op;

        const int dividend_frac_len = left_op_copy.frac_digits_count;
        const int divisor_frac_len = right_op_copy.frac_digits_count;

        // Unpack.
        // shift of dividend: 7+(7-frac_count). Filling left with zeroes: 14+(8-int_count).
        // shift of divisor: (7-frac_count) + (14+7). max = 999.999.990.000.000.
        std::vector<uint8_t> remainder;
        std::vector<uint8_t> divisor_scaled;
        for (int i = 7; i >= 0; i--) {
            remainder.push_back((left_op_copy.rep >> (i * 4)) & 0xf);
            divisor_scaled.push_back((right_op_copy.rep >> (i * 4)) & 0xf);
        }

        // Align the dividend in the 36-length decimal grid.
        // (dividend * 10^7) * 10^7. Get rid of fractional part and make some space for 7 fractional digits of the quotient.
        remainder.insert(remainder.end(), 7 + (7 - dividend_frac_len), 0);
        const int remainder_int_part_len = 8 - dividend_frac_len;
        remainder.insert(remainder.begin(), 14 + (8 - remainder_int_part_len), 0);

        // Align the divisor so on the first iteration it is the partial product divisor * 10^(14+7), where 7 is for 7 fractional digits.
        divisor_scaled.insert(divisor_scaled.end(), (7 - divisor_frac_len) + (14 + 7), 0);
        const int divisor_int_part_len = 8 - divisor_frac_len;
        divisor_scaled.insert(divisor_scaled.begin(), 8 - divisor_int_part_len, 0);

        std::array<uint8_t, 22> quotient{};
        for (int i = 0; i < 22; i++) {
            int counter = 0;
            while (difference_can_be_positive(remainder, divisor_scaled)) {
                subtract(remainder, divisor_scaled);
                counter++;
            }
            quotient[i] = counter;

            // Downscale the divisor - shift right on one decimal place.
            divisor_scaled.pop_back();
            divisor_scaled.insert(divisor_scaled.begin(), 0);
        }

        // Now the quotient contains 7 fractional digits in the high part.
        BCD res;
        const int int_part_begin = 14;
        for (int i = 0, unpacked = 8; i < quotient.size() && unpacked > 0; i++) {
            // Skip only leading zeroes of the integer part excluding the very first integer digit.
            if (quotient[i] == 0 && unpacked == 8 && i < int_part_begin)
                continue;

            res.rep = res.rep | (quotient[i] << (unpacked - 1) * 4);
            unpacked--;

            // We are in the fractional part of the quotient.
            if (i > int_part_begin)
                res.frac_digits_count++;
        }

        return res;
    }

    std::string to_string() {
        std::string res;
        for (int i = 0; i < 8; i++) {
            // Check for the first fractional digit.
            if (i == (8 - frac_digits_count))
                res += '.';

            const char digit = ((rep >> (7 - i) * 4) & 0xf) + '0';
            // Skip leading zeroes except one leading zero of the integer part if result < 1.
            if ((digit == '0') && res.empty() && i < (8 - frac_digits_count - 1))
                continue;

            res += digit;
        }

        return is_negative ? '-' + res : res;
    }

private:
    uint32_t rep = 0; // Packed BCD, 8 decimal digits.
    uint8_t frac_digits_count = 0;
    bool is_negative = false;

    void truncate_frac_to(uint8_t target_count) {
        if (frac_digits_count == target_count)
            return;

        const uint8_t diff = frac_digits_count - target_count;
        rep = rep >> (diff * 4);

        frac_digits_count = target_count;
    }

    // NOTE: The divisor is scaled by the weight of the current digit of the quotient.
    static bool difference_can_be_positive(const std::vector<uint8_t>& remainder, const std::vector<uint8_t>& divisor_scaled) {
        size_t rem_begin = 0; // The index of the first non-zero digit of the remainder.
        while (rem_begin < remainder.size() && remainder[rem_begin] == 0)
            rem_begin++;

        size_t div_begin = 0; // The same for divisor_scaled.
        while (div_begin < divisor_scaled.size() && divisor_scaled[div_begin] == 0)
            div_begin++;

        if (rem_begin < div_begin) return true;
        if (rem_begin > div_begin) return false;

        size_t i = rem_begin; // rem_begin == div_begin.
        while (i < remainder.size()) {
            if (remainder[i] > divisor_scaled[i]) return true;
            if (remainder[i] < divisor_scaled[i]) return false;
            i++;
        }

        return true; // remainder == divisor_scaled.
    }

    static void subtract(std::vector<uint8_t>& remainder, const std::vector<uint8_t>& divisor_scaled) {
        uint8_t borrow = 0;
        for (int i = 35; i >= 0; i--) {
            int8_t diff = (remainder[i] - borrow) - divisor_scaled[i];
            if (diff >= 0)
                borrow = 0;
            else {
                diff += 10;
                borrow = 1;
            }

            remainder[i] = static_cast<uint8_t>(diff);
        }
    }
};
