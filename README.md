# Sort Trek: Multi-criteria ranking of hierarchical astronomical records in C

Sort Trek ranks solar systems for exploration using six ordered comparison criteria. A command-line program reads systems, planets, and moons from a hierarchical input file, then sorts system records in place and prints their names in priority order.

## 1. Academic context and scope

- **Institution:** Universidade Federal de Minas Gerais (UFMG)
- **Degree:** Ciência da Computação
- **Course:** Programação e Desenvolvimento de Software I
- **Assignment:** Trabalho Prático 1
- **Semester:** 2023-02

The project connects introductory C programming with a sorting problem whose comparison key depends on nested data. The delivered implementation contains the file parser, dynamically allocated record structures, metric helpers, a comparator, and a recursive partition-based sorting routine.

Systems are prioritized by larger stellar radius, more planets, larger maximum planetary radius, more moons in total, larger maximum lunar radius, and finally earlier discovery time. Each criterion breaks ties left by the preceding criteria.

## 2. How to run

Prerequisite: a C compiler. The repository's entrypoint is [main.c](main.c); run compilation from the repository root:

```sh
gcc -std=c11 -Wall -Wextra -pedantic main.c -o sort-trek
```

The executable reads an input-file path from standard input. It then opens that file to read the astronomical records; the records themselves are not read directly from standard input.

## 3. Usage example

The versioned [first input fixture](entradas/case-1) contains three systems:

```sh
printf '%s\n' entradas/case-1 | ./sort-trek
```

Its [expected-output fixture](saidas/case-1) contains:

```text
UeoFP
CVUdc
w4a52L3
```

The order follows descending stellar radius for this case. This is the stored reference output; it was not regenerated for this README.

## 4. Implementation decisions

- **Nested records:** `Sistema`, `Planeta`, and `Lua` preserve the hierarchy rather than flattening all astronomical objects into one table.
- **Central comparison rule:** `sistcmp` applies the six criteria in one place. Helpers traverse the nested records to compute planetary and lunar metrics during comparisons.
- **In-place partitioning:** `bromerosort` recursively partitions around the last record in an interval through `ritacao`. Swapping system structures moves their pointers without copying each planet or moon allocation.

## 5. Tests and evaluation

The [input fixtures](entradas) and [reference outputs](saidas) provide concrete ranking cases.

## 6. Learning

The work develops the relationship between hierarchical data modeling, pointer ownership, and recursive sorting. Recomputing nested metrics during comparisons also makes the cost of a comparison relevant to overall sorting cost.
