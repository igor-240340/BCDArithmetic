#pragma once

#include <string>

// Binary-coded decimal.
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

        // NOTE: If carry is not zero here then we've got an overflow.

        return res;
    };

    BCD operator-(const BCD& right_op) const {
        BCD left_op_copy = *this;
        BCD right_op_copy = right_op;

        right_op_copy.is_negative = !right_op_copy.is_negative; // a - b = a + -b.

        return left_op_copy + right_op_copy;
    };

    BCD operator*(const BCD& right_op) const {
    };

    BCD operator/(const BCD& right_op) const {
    }

    std::string to_string() {
        std::string res;
        for (int i = 0; i < 8; i++) {
            if (i == 8 - frac_digits_count)
                res += '.';

            const char digit = ((rep >> (7 - i) * 4) & 0xf) + '0';
            if ((digit == '0') && res.empty()) // Skip leading zeroes.
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
};
