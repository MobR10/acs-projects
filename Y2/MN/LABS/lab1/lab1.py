import numpy as np
from numpy import linalg as la

def frobenius(matrice):
    norm = 0
    dimensions = matrice.shape
    for i in range(dimensions[0]):
        for j in range(dimensions[1]):
            norm += abs(matrice[i,j])**2
    return np.sqrt(norm)

def dot(A,B):
    dim1 = A.shape
    dim2 = B.shape
    if dim1[1]==dim2[0]:
        result = np.zeros((dim1[0],dim2[1]))
        for i in range(dim1[0]):
            for j in range(dim2[1]):
                for k in range(dim1[1]):
                    result[i,j] += A[i,k]*B[k,j]
        return result
    else:
        print("Matrices don't have the right dimensions for dot.")
        return None
    
def LUDOT(L,U):
    if L.shape == U.shape:
        A=np.zeros(U.shape)
        for i in range(L.shape[0]):
            for j in range(i+1):
                for k in range(j+1):
                    A[i,j]+= L[i][k]*U[k][j]
            for j in range(i+1,U.shape[1]):
                for k in range(i+1):
                    A[i,j]+= L[i][k]*U[k][j]

        return A
    else:
        print("L and U dimensions do not coincide. Cannot multiply for A=LU")
        return None

# main runs here
rng = np.random.default_rng(0) #Initializarea unui generator

a = rng.integers(1,10,size=(3,3)) # generam un vector cu 3 elemente

b = rng.integers(1,10,size=(3,2))

print("Matrice A:\n",a,'\n')
print("Matrice B:\n",b,"\n")
#EX 1
print("EX 1:\nNumpy Frobenius(A):\n",la.norm(a,ord='fro'),
        '\nMy Frobenius(A):\n',frobenius(a),'\n')

#EX 2
print("EX2\nNumpy dot(A*B):\n",np.dot(a,b),
      '\nMy dot(A*B):\n',dot(a,b),'\n')

#EX 3
L = np.tril(rng.integers(1,10,size=(3,3)))
U = np.triu(rng.integers(1,10,size=(3,3)))

print("EX3\n L =\n",L,'\nU=\n',U,'\n')
print('NUMPY DOT(L,U):\n',np.dot(L,U),'\n')
print('MY DOT(L,U):\n',LUDOT(L,U))