def esdigito(A):
    i=0
    a=False
    num=[1,2,3,4,5,6,7,8,9,0]
    while i<len(A):
        if A[i] in num:
            a=True
        elif A[i] not in num:
            a=False
        i+=1
    return a