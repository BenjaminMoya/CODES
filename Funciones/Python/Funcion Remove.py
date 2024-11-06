def remover(A,a):
    i=0
    while i<len(A):
        if A[i]==a:
            A.pop(i)
            return A
        i+=1