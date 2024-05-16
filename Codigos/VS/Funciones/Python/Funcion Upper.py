def Mayusculas(A):
    min="abcdefghijklmnopqrstvwxyz"
    mayus="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    i=0
    while i<len(A):
        if A[i] in min:
            p=min.index(A[i])
            A[i]=mayus[p]
        i+=1
    return A
