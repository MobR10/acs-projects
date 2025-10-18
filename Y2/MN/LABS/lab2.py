import numpy as np

def GPP(A):
    n = A.shape[0]
    p = np.array((n,1))
    for k in range(n):
        ik=np.argmax(abs(A[k:,k]))
        if ik!=k:
            A[[k,ik]] = A[[ik,k]]
        p[k]=ik
        for i in range(k+1,n):
            A[i,k]=A[i,k]/A[k,k]
        for j in range(k+1,n):
            for i in range(k+1,n):
                A[i,j]=A[i,j]-A[i,k]/A[k,k]*A[k,j]
    return A