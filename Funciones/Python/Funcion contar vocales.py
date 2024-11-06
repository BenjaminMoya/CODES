def contar_consonantes(texto):
    contador = 0
    vocales = "aeiouáéíóúü"
    for caracter in texto:
        if caracter.isalpha() and not\
(caracter.lower() in vocales):
            contador += 1
    return contador
