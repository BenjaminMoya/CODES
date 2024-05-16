import pandas as pd
datos=[["Maria",18,"Economia","maria@gmail.com"],["Luis",22,"Medicina","luis@yahoo.es"]]
columnas=["Nombre","Edad","Grado","Correo"]
tabla_personas=pd.DataFrame(datos,columns=columnas)
print(tabla_personas)