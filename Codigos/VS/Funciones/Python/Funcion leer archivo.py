def leer_archivo(nombre):
    nombre = nombre + ".txt"
    with open(nombre, 'r') as archivo:
        texto = ''
        for linea in archivo:
            texto = texto + linea
    return texto