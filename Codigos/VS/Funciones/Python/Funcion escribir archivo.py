def escribir_archivo(nombre, numero):
    nombre = nombre + ".txt"
    with open(nombre, 'a') as archivo:
        archivo.write("\n\n")
        archivo.write("El numero de consonantes es: ")
        archivo.write(str(numero))
    return True