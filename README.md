# Advent of Code 2019

This is a collection of solutions to the
[Advent of Code 2019](https://adventofcode.com/2019) programming problems
implemented in the C programming language. I have done my best to minimize time
complexity and running time. This repository only includes solutions to the
[Intcode](https://esolangs.org/wiki/Intcode) problems.

Some of the more complex problems were implemented in a
[higher-level programming language](ref/) before being converted to C. The
equivalent code is included here as a reference.

## Usage

These programs are cross-platform, having been tested on Windows and Linux
operating systems.

**Important:** Do not use Windows-style line endings (`CR LF`, i.e. `\r\n`).
Only use Unix-style line endings (`LF`, i.e. `\n`).

**Important:** I have tested each program on the example test cases and two
puzzle input files - not a large sample size! I have avoided assumptions about
the input, sometimes even at the cost of performance. However, to avoid memory
allocation, all buffers have fixed sizes. Ensure that all buffers (see `#define`
statements) have sufficient capacity before running. Not doing so could result
in a stack smashing, segmentation fault, or worse.

## Constraints

I am working within the following constraints to ensure high code quality.

- Adhere to the [project style guide](cstyle.md).
- Final solutions must be implemented in the C programming language following
  the C99 standard.
  - Assume signed integer overflow is defined based on two\'s complement.
- All solutions must be standalone files with no external dependencies beyond
  the C standard library (`libc`) and the C mathematics library (`libm`). The
  first and second problems for a given day must be implemented separately.
- Bounds checking is not required for data structures whose capacity is defined
  by a macro.
- The return values of all C standard library functions must be checked, except
  for those returned from the following:
  - `fprintf`
  - `memcpy`
  - `printf`
