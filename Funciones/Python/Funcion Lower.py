def Mayusculas(A):
    min="abcdefghijklmnopqrstvwxyz"
    mayus="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    i=0
    while i<len(A):
        if A[i] in mayus:
            p=mayus.index(A[i])
            A[i]=min[p]
        i+=1
    return A
