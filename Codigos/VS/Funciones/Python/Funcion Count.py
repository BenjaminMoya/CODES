def contar(A,a):
    i=0
    cuenta=0
    while i<len(A):
        if A[i]==a:
            cuenta+=1
        i+=1
    return cuenta