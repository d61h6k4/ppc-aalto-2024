### PPC Aalto 2024

> ppc - stands for Programming Parallel Computers.

The repository contains solutions for the exercises of the Aalto University course on programming parallel computers for 2024.

[Link](https://ppc-exercises.cs.aalto.fi/course/aalto2024) to the page with exercises.

#### Usage

Run tests for exercises (e.g. pre0)

```bash
bazel test //exercises/pre0:pre0_test --test_output=all
```

Run benchmarks for exercises (e.g. pre0)

```bash
bazel test //exercises/pre0:pre0_benchmark --test_output=all
```
