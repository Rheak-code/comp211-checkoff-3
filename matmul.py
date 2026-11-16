import sys


def make_inputs(n):
    # Same deterministic values as matmul.c. Each row is a separate list object,
    # and every number is a separate heap object the list points to.
    A = [[((i * n + j) % 7) * 0.5 for j in range(n)] for i in range(n)]
    B = [[((i * n + j) % 5) * 0.25 for j in range(n)] for i in range(n)]
    return A, B


def matmul_ijk(n, A, B):
    C = [[0.0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            s = 0.0
            for k in range(n):
                s += A[i][k] * B[k][j]
            C[i][j] = s
    return C


def matmul_ikj(n, A, B):
    C = [[0.0] * n for _ in range(n)]
    for i in range(n):
        Ci = C[i]
        for k in range(n):
            a = A[i][k]
            Bk = B[k]
            for j in range(n):
                Ci[j] += a * Bk[j]
    return C


def main():
    if len(sys.argv) < 3:
        print("usage: python3 matmul.py N ijk|ikj|numpy", file=sys.stderr)
        sys.exit(1)
    n = int(sys.argv[1])
    order = sys.argv[2]

    A, B = make_inputs(n)

    if order == "numpy":
        import numpy as np
        C = np.array(A) @ np.array(B)
        checksum = float(C.sum())
    else:
        f = matmul_ikj if order == "ikj" else matmul_ijk
        C = f(n, A, B)
        checksum = sum(sum(row) for row in C)

    print(f"checksum = {checksum:.1f}")


if __name__ == "__main__":
    main()