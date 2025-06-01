template<class T>
struct div_result {
    T quotient;
    T remainder;
    friend bool operator<=>(const div_result&, const div_result&) = default;
};

constexpr int __sgn2(int x) {
    // Equivalent to: (x >> (INT_WIDTH - 1)) | 1
    return x < 0 ? -1 : 1;
}

constexpr div_result<int> __div_rem_impl(
    // Dividend.
    int x,
    // Divisor.
    int y,
    // If true, truncating division gives us the wrong result,
    // and increasing the magnitude of the quotient by one would be correct.
    bool increment,
    // The quotient sign (1 or -1).
    int quotient_sign
) {
    int quotient_change = int(increment) * quotient_change;
    return {
        .quotient = x / y + quotient_change,
        // This is (x % y - quotient_change * y),
        // except that we use unsigned int to avoid overflow when y is INT_MIN.
        // Due to modular arithmetic rules, when we multiply y with -1,
        // the remainder is congruent to (x % y + y),
        // so simply doing it all with unsigned integers fixes our overflow problems.
        .remainder = int(unsigned(x % y) - unsigned(quotient_change) * unsigned(y))
    };
}

// Idea: trivial implementation.
constexpr div_result<int> div_rem_to_zero(int x, int y) {
    return { .quotient = x / y, .remainder = x % y };
}

constexpr int div_to_zero(int x, int y) {
    return x / y;
}

// Idea: since '/' truncates,
//       we need to increase the quotient magnitude
//       in all cases except when the remainder is zero.
constexpr div_result<int> div_rem_away_zero(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    bool increment = x % y != 0;
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_away_zero(int x, int y) {
    return div_rem_away_zero(x, y).quotient;
}

// Idea: since '/' truncates,
//       the result is one greater than what we want
//       for negative quotients, unless the remainder is zero.
constexpr div_result<int> div_rem_to_inf(int x, int y) {
    int quotient_positive = (x ^ y) >= 0;
    bool adjust = x % y != 0 && quotient_positive;
    return {
        .quotient  = x / y + int(adjust),
        .remainder = x % y - int(adjust) * y,
    };
}

constexpr int div_to_inf(int x, int y) {
    return div_rem_to_inf(x, y).quotient;
}

// Idea: since '/' truncates,
//       the result is one lower than what we want
//       for positive quotients, unless the remainder is zero.
constexpr div_result<int> div_rem_to_neg_inf(int x, int y) {
    bool quotient_negative = (x ^ y) < 0;
    bool adjust = x % y != 0 && quotient_negative;
    return {
        .quotient  = x / y - int(adjust),
        .remainder = x % y + int(adjust) * y,
    };
}

constexpr int div_to_neg_inf(int x, int y) {
    return div_rem_to_neg_inf(x, y).quotient;
}

// Idea: same as div_away_zero,
//       but we only magnify when this gets us away
//       from an even integer.
constexpr div_result<int> div_rem_to_odd(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    bool increment = x % y != 0 && x / y % 2 == 0;
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_to_odd(int x, int y) {
    return div_rem_to_odd(x, y).quotient;
}

// Idea: same as div_away_zero,
//       but we only magnify when this gets us away
//       from an odd integer.
constexpr div_result<int> div_rem_to_even(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    bool increment = x % y != 0 && x / y % 2 != 0;
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_to_even(int x, int y) {
    return div_rem_to_even(x, y).quotient;
}

// Idea: same as div_away_zero,
//       but we only magnify when the remainder
//       is greater than abs(y / 2).
constexpr div_result<int> div_rem_ties_to_zero(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    int abs_rem = x % y * __sgn2(x);
    int abs_half_y = y / 2 * __sgn2(y);
    bool increment = abs_rem > abs_half_y;
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_ties_to_zero(int x, int y) {
    return div_rem_ties_to_zero(x, y).quotient;
}

// Idea: same as div_away_zero, but we only magnify when the remainder
//       is greater or equal to abs(y / 2).
//       This is actually somewhat tricky because abs(y / 2) drops one bit of precision,
//       i.e. the bit indicating .5 or .0 in the number,
//       and (abs(2 * x % y) >= abs(y)) may overflow, so we cannot use that instead.
//       However, we can get back that one bit of precision using (y % 2 != 0),
//       which optimizes to (y & 1).
//       When y is even, that bit is zero and we didn't drop any precision anyway.
//       When y is odd, there are no exact ties, and we increase the right hand side
//       of the comparison to bias more towards truncation instead of magnification.
constexpr div_result<int> div_rem_ties_away_zero(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    int abs_rem = x % y * __sgn2(x);
    int abs_half_y = y / 2 * __sgn2(y);
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0);
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_ties_away_zero(int x, int y) {
    return div_rem_ties_away_zero(x, y).quotient;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is positive.
constexpr div_result<int> div_rem_ties_to_inf(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    int abs_rem = x % y * __sgn2(x);
    int abs_half_y = y / 2 * __sgn2(y);
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient_sign < 0);
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_ties_to_inf(int x, int y) {
    return div_rem_ties_to_inf(x, y).quotient;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is negative.
constexpr div_result<int> div_rem_ties_to_neg_inf(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    int abs_rem = x % y * __sgn2(x);
    int abs_half_y = y / 2 * __sgn2(y);
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient_sign > 0);
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_ties_to_neg_inf(int x, int y) {
    return div_rem_ties_to_neg_inf(x, y).quotient;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is even.
constexpr div_result<int> div_rem_ties_to_odd(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    int abs_rem = x % y * __sgn2(x);
    int abs_half_y = y / 2 * __sgn2(y);
    int quotient = x / y;
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient % 2 != 0);
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_ties_to_odd(int x, int y) {
    return div_rem_ties_to_odd(x, y).quotient;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is odd.
constexpr div_result<int> div_rem_ties_to_even(int x, int y) {
    int quotient_sign = __sgn2(x) * __sgn2(y);
    int abs_rem = x % y * __sgn2(x);
    int abs_half_y = y / 2 * __sgn2(y);
    int quotient = x / y;
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient % 2 == 0);
    return __div_rem_impl(x, y, increment, quotient_sign);
}

constexpr int div_ties_to_even(int x, int y) {
    return div_rem_ties_to_even(x, y).quotient;
}

// Idea: if the there is a mismatch between the x and y being negative,
//       the result sign would be wrong, and we need to flip it;
//       If they match (i.e. if the quotient is positive),
//       we already have the right result.
//       If the mismatch is caused by the dividend being negative,
//       the remainder is also negative and we should add the (positive) divisor.
//       If the mismatch is caused by the divisor being negative,
//       we should add the (negative) divisor to get a negative remainder.
//       In either case, adding the divisor is the right thing to do.
constexpr int mod(int x, int y) {
    bool quotient_negative = (x ^ y) < 0;
    int rem = x % y;
    return rem + y * int(rem != 0 && quotient_negative);
}
