def esminiscula(A):
    i=0
    a=True
    min="abcdefghijklmopqrstuvwxyz"
    while i<len(A):
        if A[i] in min:
            a=False
        i+=1
    return a