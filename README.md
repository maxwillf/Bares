# Introduction

Basic ARithmetic Expression Evaluator based on Stacks for addition, subtraction,
multiplication, division, modular division and exponentiation operations.

This programming project implements a simple parser for an EBNF (_Extended Backus-Naur Form_) grammar.

It also uses my own vector implementation found [here](https://github.com/maxwillf/tad-vector).

The objective Information on **EBNF grammar** may be found [here](https://en.wikipedia.org/wiki/Extended_Backus–Naur_Form).

Information on **recursive descendent parsing** may be found [here](https://en.wikipedia.org/wiki/Recursive_descent_parser).

# The Grammar

The gramar we want to parse represents arithmetic expressions with addition and subtraction of integers.

    <expr>            := <term>,{ ("+"|"-"),<term> };
    <term>            := "(",<expr>,")" | <integer>;
    <integer>         := 0 | ["-"],<natural_number>;
    <natural_number>  := <digit_excl_zero>,{<digit>};
    <digit_excl_zero> := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
    <digit>           := "0"| <digit_excl_zero>;

This grammar _accepts_ expressions like:

* "23 + 43 - 0   + -124 - 21"
* " 21"
* "-21 +     -18"
* " -54"
* "-21 - 23 + 1234"
* (2+3) * 8
* 5 % 2 ^4
* (5 % 3) ^4

And _rejects_ expressions like:

* 2+
* 3 * d
* 2 = 3
* 2.3 + 4
* "01 + 3"
* " - 3 + 4"
* "2 +"
* "  "
* "+2 + 5"
* "-02 + 4"
* )2 - 4
* ((2%3) * 8
* 3/(1-1)

# Usage

You will need at least g++ C11 compiler and GNU makefile

to build it simply run:
```
make
```

For running Bares execute it like this:
```
./bares input_file [output_file]

