# My C++ Proposals

Author: Jan Schultke

## Active

### P3103: More bitset operations

**Status**: Active<br>
**Audience**: LEWG-I, LEWG

- [Latest](more-bitset-operations.html)
- [P3103R2](more-bitset-operations-p3103r2.html)
- [P3103R1](more-bitset-operations-p3103r1.html)
- [P3103R0](more-bitset-operations-p3103r0.html)

### P3104: Bit permutations

**Status**: Active<br>
**Audience**: LEWG-I, LEWG<br>
**Slides:** [P3192](../slides/p3104-slides.pdf),
[P3730](bit-permutations-slides.html)

- [Latest](bit-permutations.html)
- [P3104R3](bit-permutations-p3104r3.html)
- [P3104R2](bit-permutations-p3104r2.html)
- [P3104R1](bit-permutations-p3104r1.html)
- [P3104R0](bit-permutations-p3104r0.html)

### P3568: `break label;` and `continue label;`

**Status**: Active<br>
**Audience**: SG22, EWG<br>
**Summary**: [P3628](break-continue-label-tldr.html) (tl; dr version for EWGI at Hagenberg 2025)<br>
**Slides**: [P3630](../slides/p3568-slides.pdf) (Syntax discussion slides for EWG at Hagenberg 2025),
[P3630](break-continue-label-slides.html)

- [Latest](break-continue-label.html)
- [P3568R1](break-continue-label-p3568r1.html)
- [P3568R0](break-continue-label-p3568r0.html)

### P3642: Carry-less product: `std::clmul`

**Status**: Active<br>
**Audience**: SG6, LEWG

- [Latest](clmul.html)
- [P3642R1](clmul-p3642r1.html)
- [P3642R0](clmul-p3642r0.html)

### P3643: `std::to_signed`, `std::to_unsigned`

**Status**: Active<br>
**Audience**: LEWG

- [Latest](to-signed-unsigned.html)
- [P3643R0](to-signed-unsigned.html)

### P3688: ASCII character utilities

**Status**: Active<br>
**Audience**: SG16, LEWG

- [Latest](ascii.html)
- [P3688R0](ascii-p3688r0.html)

### P3695: Deprecate implicit conversions between `char8_t`, `char16_t`, and `char32_t`

**Status**: Active<br>
**Audience**: SG16, EWG

- [Latest](deprecate-unicode-conversion.html)
- [P3695R0](deprecate-unicode-conversion-p3695r0.html)

### P3701: Concepts for integer types, not integral types

**Status**: Active<br>
**Audience**: LEWG, CWG

- [Latest](signed-or-unsigned.html)
- [P3701R0](signed-or-unsigned-p3701r0.html)

### P3702: Stricter requirements for document submissions (SD-7)

**Status**: Active<br>
**Audience**: Admin

- [Latest](sd7-updates.html)
- [P3702R0](sd7-updates-p3702r0.html)

### P3724: Integer division

**Status**: Active<br>
**Audience**: SG6, LEWG

- [Latest](intdiv.html)

### P3733: More named universal character escapes

**Status**: Active<br>
**Audience**: SG16

- [Latest](more-unicode-escapes.html)

### P3735: `partial_sort_n`, `nth_element_n`

**Status**: Active<br>
**Audience**: SG9

- [Latest](n-algorithms.html)

## Inactive

### P3087: Make direct-initialization for enumeration types at least as permissive as direct-list-initialization

**Status**: Rejected<br>
**Audience**: EWG-I, EWG

- [Latest](enum-direct-init.html)
- [P3087R1](enum-direct-init-p3087r1.html)
- [P3087R0](enum-direct-init-p3087r0.html)

### P3105: `constexpr std::uncaught_exceptions()`

**Status**: Superseded by [P3068](https://wg21.link/p3068/github)<br>
**Audience**: LEWG-I, LEWG

- [Latest](constexpr-uncaught-exceptions.html)
- [P3105R2](constexpr-uncaught-exceptions-p3105r2.html)
- [P3105R1](constexpr-uncaught-exceptions-p3105r1.html)
- [P3105R0](constexpr-uncaught-exceptions-p3105r0.html)

### P3176: The Oxford variadic comma

**Status**: C++26<br>
**Audience**: EWG-I, EWG, CWG

- [Latest](oxford-variadic-comma.html)
- [P3176R1](oxford-variadic-comma-p3176r1.html)
- [P3176R0](oxford-variadic-comma-p3176r0.html)

### P3140: `std::int_least128_t`

**Status**: Superseded by [P3666](bitint.html) (`_BitInt`)<br>
**Audience**: LEWG-I, LEWG, EWG-I, EWG, SG22

- [Latest](int-least128.html)
- [P3140R0](int-least128-p3140r0.html)

### P3639: The `_BitInt` Debate

**Status**: Complete, desired feedback obtained<br>
**Audience**: SG6, SG22, EWG, LEWG<br>
**Slides**: [P3721](bitint-debate-slides.html) (Slides for SG6 and SG22, 2025)

- [Latest](bitint-debate.html)
- [P3639](bitint-debate-p3639r0.html)

### P3641: Rename `std::observable` to `std::observable_checkpoint`, and add a feature-test macro

**Status**: C++26<br>
**Audience**: LEWG

- [Latest](observable-checkpoint.html)
- [P3641R0](observable-checkpoint-p3641r0.html)

### P3740: Last chance to fix `std::nontype`

**Status**: Forwarded to LWG for C++26, but too late for plenary<br>
**Audience**: LEWG

- [Latest](nontype.html)
- [P3740R1](nontype-p3740r1.html)
- [P3740R0](nontype-p3740r0.html)

### NP: Define `offsetof` semantics in the C++ standard

**Status**:
Superseded by [P2883](wg21.link/p2883/github) before publication.
That paper was rejected at Hagenberg 2025, but the door is left open for revisiting.
In any case, I am not pursuing this for now.

- [Latest](offsetof.html)

### NP: Better, `constexpr to_string`

**Status**:
Superseded by [P3438](https://wg21.link/p3438/github)
before publication<br>
**Audience**: LEWG-I, LEWG

- [Latest](constexpr-to-string.html)
