import numpy as np


def LTRIS(L,b):
    n = L.shape[0]
    x = np.zeros_like(b,dtype=float)
    
    for i in range(n):
        if L[i,i] == 0:
            print(f"LTRIS i={i}: boi, there is a zero on the diagonal")
        else:
            x[i] = b[i]
            for j in range(i):
                x[i] = x[i] - L[i,j] * x[j]
            x[i] = x[i] / L[i,i]
    
    return x  

    
def UTRIS(U,b):
    n = U.shape[0]
    x = np.zeros_like(b,dtype=float)
    for i in range(n-1, -1, -1):
        if U[i,i] == 0:
           print(f"UTRIS i={i}: boi, there is a zero on the diagonal")
        else:
            x[i] = b[i]
            for j in range(i+1,n):
                x[i] = x[i] - U[i,j] * x[j]
            x[i] = x[i] / U[i,i]
    return x

def CROUT(A):
    n = A.shape[0]
    L = np.zeros_like(A,dtype=float)
    U = np.eye(n,dtype=float)
    for k in range(n):
        for i in range(k,n):
            L [i,k] = A[i,k]
            for s in range(k):
                L[i,k] = L[i,k] - L[i,s]* U[s,k]
        for j in range(k+1,n):
            U[k,j] = A[k,j]
            for s in range(k):
                U[k,j] = U[k,j] - L[k,s] * U[s,j]
            U[k,j] = U[k,j] / L[k,k]
    
    return L, U

    
# A = np.random.randint(1, 9, size=(3, 3))
A = np.array([[1,2,3],[4,5,6],[7,8,9]])
print("A:\n",A)
# L = np.tril(np.random.randint(1, 9, size=(3, 3)))
# U = np.triu(np.random.randint(1, 9, size=(3, 3)))
[L,U] = CROUT(A)

print("L:\n",L,"\nU:\n",U)

b = np.random.randint(10, 20, size=(3, 1))
print("\nb:\n",b)

print("\nLTRIS:\n")
print(LTRIS(L,b))

print("\nUTRIS:\n")
print(UTRIS(U,b))

print("\nL*U:\n",L@U)
