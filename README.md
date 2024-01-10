# Advent of Code 2019

This is a collection of solutions to the
[Advent of Code 2019](https://adventofcode.com/2019) programming problems
implemented in the C programming language. I have done my best to minimize time
complexity and running time. This repository only includes solutions to the
[Intcode](https://esolangs.org/wiki/Intcode) problems.

## Usage

These programs are cross-platform, having been tested on Windows and Linux
operating systems.

**Important:** Use the `MEMORY`, `INPUTS`, and `OUTPUTS` macros to ensure that
the program does not run out of memory and invoke undefined behavior.

## Constraints

I am working within the following constraints to ensure high code quality.

- Adhere to the [project style guide](cstyle.md).
- Final solutions must be implemented in the C programming language following
  the C99 standard.
- Bounds checking is not required for data structures whose capacity is defined
  by a macro.
- The return values of all C standard library functions must be checked, except
  for those returned from the following:
  - `fprintf`
  - `memcpy`
  - `printf`

## Attribution

This repository redistributes
[cbraudo/qdbmp](https://github.com/cbraudo/qdbmp/tree/master) (Quick n\' Dirty
BMP Library) by Chai Braudo. This component is required for Day 11(b) and is distributed under the MIT license.
