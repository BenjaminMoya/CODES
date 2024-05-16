#def letrarepetida(A):
x="hola"
minus="abcdefghijklmnopqrstuvwxyz"
palabra=x.lower()
i=0
letras=[]
cuenta_letra=[]
while i<len(x):
    if x[i] in minus:
        letras+=x[i]
        j=0
        cuenta=0
        while j<len(x):
            if x[j]==x[i]:
                cuenta+=1
                j+=1
            cuenta_letra.append(cuenta)
    i=+1
    l=0
    lista_aux=cuenta_letra
    cuenta_letra.sort()
print(x)
#return cuenta_letra

#c=letrarepetida(x)
#print(c)
