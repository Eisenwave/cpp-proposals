// Exposition-only helper.
// Equivalent to: (x >> (INT_WIDTH - 1)) | 1
constexpr int sgn2(int x) {
    return x < 0 ? -1 : 1;
}

// Idea: trivial implementation.
constexpr int div_to_zero(int x, int y) {
    return x / y;
}

// Idea: since '/' truncates,
//       we need to increase the quotient magnitude
//       in all cases except when the remainder is zero.
constexpr int div_away_zero(int x, int y) {
    int quotient_sign = sgn2(x) * sgn2(y);
    return x / y + int(x % y != 0) * quotient_sign;
}

// Idea: since '/' truncates,
//       the result is one greater than what we want
//       for negative quotients, unless the remainder is zero.
constexpr int div_to_inf(int x, int y) {
    int quotient_negative = (x ^ y) < 0;
    return x / y + (x % y != 0 && !quotient_negative); 
}

// Idea: since '/' truncates,
//       the result is one lower than what we want
//       for positive quotients, unless the remainder is zero.
constexpr int div_to_neg_inf(int x, int y) {
    int quotient_negative = (x ^ y) < 0;
    return x / y - (x % y != 0 && quotient_negative); 
}

// Idea: same as div_away_zero,
//       but we only magnify when this gets us away
//       from an even integer.
constexpr int div_to_odd(int x, int y) {
    int quotient = x / y;
    int quotient_sign = sgn2(x) * sgn2(y);
    return quotient + int(x % y != 0 && quotient % 2 == 0) * quotient_sign;
}

// Idea: same as div_away_zero,
//       but we only magnify when this gets us away
//       from an odd integer.
constexpr int div_to_even(int x, int y) {
    int quotient = x / y;
    int quotient_sign = sgn2(x) * sgn2(y);
    return quotient + int(x % y != 0 && quotient % 2 != 0) * quotient_sign;
}

// Idea: same as div_away_zero,
//       but we only magnify when the remainder
//       is greater than abs(y / 2).
constexpr int div_ties_to_zero(int x, int y) {
    int quotient_sign = sgn2(x) * sgn2(y);
    int abs_rem = x % y * sgn2(x);
    int abs_half_y = y / 2 * sgn2(y);
    bool increment = abs_rem > abs_half_y;
    return x / y + int(increment) * quotient_sign;
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
constexpr int div_ties_away_zero(int x, int y) {
    int quotient_sign = sgn2(x) * sgn2(y);
    int abs_rem = x % y * sgn2(x);
    int abs_half_y = y / 2 * sgn2(y);
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0);
    return x / y + int(increment) * quotient_sign;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is positive.
constexpr int div_ties_to_inf(int x, int y) {
    int quotient_sign = sgn2(x) * sgn2(y);
    int abs_rem = x % y * sgn2(x);
    int abs_half_y = y / 2 * sgn2(y);
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient_sign < 0);
    return x / y + int(increment) * quotient_sign;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is negative.
constexpr int div_ties_to_neg_inf(int x, int y) {
    int quotient_sign = sgn2(x) * sgn2(y);
    int abs_rem = x % y * sgn2(x);
    int abs_half_y = y / 2 * sgn2(y);
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient_sign > 0);
    return x / y + int(increment) * quotient_sign;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is even.
constexpr int div_ties_to_odd(int x, int y) {
    int quotient_sign = sgn2(x) * sgn2(y);
    int abs_rem = x % y * sgn2(x);
    int abs_half_y = y / 2 * sgn2(y);
    int quotient = x / y;
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient % 2 != 0);
    return quotient + int(increment) * quotient_sign;
}

// Idea: same as div_ties_away_zero,
//       but we only magnify on ties when the quotient is odd.
constexpr int div_ties_to_even(int x, int y) {
    int quotient_sign = sgn2(x) * sgn2(y);
    int abs_rem = x % y * sgn2(x);
    int abs_half_y = y / 2 * sgn2(y);
    int quotient = x / y;
    bool increment = abs_rem >= abs_half_y + int(y % 2 != 0 || quotient % 2 == 0);
    return quotient + int(increment) * quotient_sign;
}

// Idea: trivial implementation.
constexpr int rem_dividend_sign(int x, int y) {
    return x % y;
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
constexpr int rem_divisor_sign(int x, int y) {
    bool quotient_negative = (x ^ y) < 0;
    int rem = x % y;
    return rem + y * int(rem != 0 && quotient_negative);
}

// Idea: if the remainder is negative, we add abs(y).
//       However, this requires some unsigned hackery because abs(INT_MIN) is undefined.
constexpr int rem_positive(int x, int y) {
    int rem = x % y;
    return int(unsigned(rem) + unsigned(rem < 0) * (y < 0 ? -unsigned(y) : unsigned(y)));
}
