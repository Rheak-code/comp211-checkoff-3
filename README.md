# Benchmarking: C vs. Python

This project compares the performance of equivalent C and Python programs using **matrix multiplication**, a triple-nested O(n³) loop that looks almost the same in both languages. It also compares NumPy, loop order (`ijk` vs. `ikj`) and compiler optimization flags (`-O0` vs. `-O3`). All timing is done externally with [hyperfine](https://github.com/sharkdp/hyperfine).

## Requirements

- `gcc`, `python3`, `numpy` (`python3 -m pip install numpy`), `hyperfine`

## Compile

```bash
gcc -O0 matmul.c -o matmul_O0
gcc -O3 matmul.c -o matmul_O3
gcc -O3 dce_demo.c -o dce_bad
gcc -O3 -DUSE_RESULT dce_demo.c -o dce_good
```

## Run

Usage: `./matmul_O3 <N> <ijk|ikj>` and `python3 matmul.py <N> <ijk|ikj|numpy>`

```bash
# Loop order and compiler flags
hyperfine -N --warmup 3 --runs 10 --parameter-list n 50,250,500,750 \
  './matmul_O0 {n} ijk' './matmul_O0 {n} ikj' './matmul_O3 {n} ijk' './matmul_O3 {n} ikj'

# C vs. Python vs. NumPy (N = 500)
hyperfine -N --warmup 1 --runs 3 \
  './matmul_O3 500 ijk' 'python3 matmul.py 500 ijk' 'python3 matmul.py 500 numpy'

# Dead code elimination
hyperfine -N --warmup 3 --runs 20 './dce_bad' './dce_good'
```

## Key discoveries

1. **Python is about 57× slower than C** on the same loop (N = 500: 5.5 s vs. 0.08–0.10 s). Python type-checks and creates objects on every operation; C compiles that overhead away.
2. **NumPy matched C** (about 0.08 s), even though it's Python. It hands the loops to optimized compiled code (BLAS). *The language matters less than who runs the loops.*
3. **Loop order matters:** at `-O3`, swapping to `ikj` made C up to **5.8× faster** (N = 750: 293 ms → 51 ms), with the same Big-O. Reading memory row by row uses the CPU cache efficiently.
4. **Compiler flags matter:** the slowest C version (`-O0 ijk`) and the fastest (`-O3 ikj`) differed by **11×** (561 ms vs. 51 ms). The loop swap barely helps at `-O0`.
5. **Benchmarking is easy to get wrong:** at `-O3`, if a result is never used the compiler can delete the whole calculation (dead code elimination). At small N, startup time dominates the measurement.

**Takeaway:** Big-O alone doesn't predict real speed. Write in Python, run the hot loops in C.
