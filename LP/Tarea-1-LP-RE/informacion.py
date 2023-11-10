#Clase que funciona como un struct
class info:
    lineaActual = 1
    llaves = 0
    posX = 0
    posY = 0
    direccion = 'r'
    rep = []
    flag = False

#se obtiene cada linea del texto
with open("archivo.txt", 'r') as f:
    texto = f.read().splitlines()

def errores(listaErrores):
    '''
    Funcion que mediante una lista, escribe cada elemento de la lista en un archivo errores.txt

        Parametros:
            listaErrores (list): Lista en donde se encuentra cada linea de error del programa

        Retorno:
            (void): No posee retorno
    '''
    with open("errores.txt",'w') as textError:
        for error in listaErrores:
            textError.write(f"{error}\n")




