def ordenar(A):
    n=len(A)
    i=1
    while i<=n-1:
        j=1
        while j<=n-1:
            if A[j]>A[j+1]:
                aux=A[j]
                A[j]=A[j+1]
                A[j+1]=aux
            j+=1
        i+=1
    return A

