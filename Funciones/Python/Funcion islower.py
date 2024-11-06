def esminiscula(A):
    i=0
    a=True
    mayus="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    while i<len(A):
        if A[i] in mayus:
            a=False
        i+=1
    return a