# Minimal pure-Python implementations to avoid external numpy dependency

def UTRIS(U, b):
    """
    Solve U x = b for upper-triangular U (list of lists) and b (list).
    Returns solution vector x.
    """
    n = len(U)
    if len(b) != n:
        raise ValueError("Dimension mismatch between U and b")
    x = [0.0] * n
    for i in range(n - 1, -1, -1):
        diag = U[i][i]
        if diag == 0:
            raise ZeroDivisionError(f"Zero diagonal element at row {i}")
        s = 0.0
        for j in range(i + 1, n):
            s += U[i][j] * x[j]
        x[i] = (b[i] - s) / diag
    print("Solution x =", x)
    return x

def GPP(A):
    """
    Gaussian elimination with partial pivoting (in-place).
    A is a list of lists (square). Returns (LU, p) where LU stores L (below diag, with 1s implied on diag)
    and U (on and above diag), and p is the permutation vector.
    """
    n = len(A)
    if any(len(row) != n for row in A):
        raise ValueError("Matrix A must be square")
    p = list(range(n))
    for k in range(n):
        # pivot selection (index of max abs in column k starting at row k)
        ik = max(range(k, n), key=lambda i: abs(A[i][k]))
        if abs(A[ik][k]) == 0:
            raise ValueError("Matrix is singular or nearly singular")
        if ik != k:
            A[k], A[ik] = A[ik], A[k]
            p[k], p[ik] = p[ik], p[k]
        for i in range(k + 1, n):
            A[i][k] = A[i][k] / A[k][k]
            for j in range(k + 1, n):
                A[i][j] = A[i][j] - A[i][k] * A[k][j]
    return A, p

print("Sal")
# Example usage: solve a simple upper-triangular system U x = b
U = [
    [2.0, 1.0],
    [0.0, 3.0]
]
b = [5.0, 6.0]
UTRIS(U, b)