from informacion import info
from matrizRGB  import data
import informacion
import re

def avanzar(num):
    '''
    Funcion encargada de avanzar en cierta dirreccion un numero de indices en la matrizRGB.
    En caso de el indice se salga de la matriz el programa lanzara un error.

        Parametros:
            num (int): numero el cual la matriz tendrá que avanzar

        Retorno:
            (void): No posee retorno
    '''
    if info.direccion == 'u':
        info.posX -= num
    elif info.direccion == 'd':
        info.posX += num
    elif info.direccion == 'l':
        info.posY -= num
    elif info.direccion == 'r':
        info.posY += num

    #se valida que el indice esté en la matriz
    if info.posX < 0 or info.posX >= data.getAncho() or info.posY < 0 or info.posY >= data.getAncho():
        print("Error: Indice fuera de rango.")
        print(f"{info.lineaActual} {informacion.texto[info.lineaActual-1]}")
        quit()

def colores(color):
    '''
    Funcion encargada de respecto a un color dado entregar una tupla correspondiente a ese color en forma de RGB

        Parametros:
            color (str): color el cual se buscara para retornar una tupla en formato RGB

        Retorno:
            ((int,int,int)): 3-Tupla de int que corresponde al color pasado por parametro
    '''
    if color == 'Rojo':
        return (255,0,0)
    elif color == 'Verde':
        return (0,255,0)
    elif color == 'Azul':
        return (0,0,255)
    elif color == 'Negro':
        return (0,0,0)
    else: 
        return (255,255,255) #blanco

def pintarRGB(R,G,B): 
    '''
    Funcion encargada de llamar a la funcion editarMatriz para pintar una posicion [x][y] de la matrizRGB.
    En un inicio se llamara a la funcion validarRGB la cual validara si el rango de color es correcto, en
    caso de que sea incorrecto terminará el programa indicando el error.

        Parametros:
            R (int): numero que corresponte a la componente Red (roja) de el color RGB
            G (int): numero que corresponte a la componente Green (verde) de el color RGB
            B (int): numero que corresponte a la componente Blue (azul) de el color RGB

        Retorno:
            (void): No posee retorno
    '''
    validarRGB(R,G,B)
    RGB = (R,G,B)
    data.editarMatriz(RGB,info.posX,info.posY)

def validarRGB(R,G,B):
    '''
    Funcion encargada de validar el rango de colores RGB

        Parametros:
            R (int): numero que corresponte a la componente Red (roja) de el color RGB
            G (int): numero que corresponte a la componente Green (verde) de el color RGB
            B (int): numero que corresponte a la componente Blue (azul) de el color RGB

        Retorno:
            (void): No posee retorno
    '''
    if(R<0 or R>255 or G<0 or G>255 or B<0 or B>255):
        print("Error: Rango de color no permitido.")
        print(f"{info.lineaActual} {informacion.texto[info.lineaActual-1]}")
        quit()

def pintar(color):
    '''
    Funcion encargada de llamar a la funcion editarMatriz para pintar una posicion [x][y] de la matrizRGB.
    Esta funcion inicialmente llama a la funcion colores, para pasarle un color y obtener una tupla RGB 
    correspondiente a dicho color

        Parametros:
            color (str): color el cual se pasará como parametro en la funcion colores para obtener color RGB

        Retorno:
            (void): No posee retorno
    '''
    RGB = colores(color)
    data.editarMatriz(RGB,info.posX,info.posY)


def izquierda(): #u = up, d = down, l = left, r = right
    '''
    Funcion encargada de girar en direccion a la izquierda dependiendo de la direccion actual.
    Esto lo hace intercalando entre las 4 posiciones posibles: arriba, abajo, izquierda, derecha.

        Parametros:
            (...): No posee parametros

        Retorno:
            (void): No posee retorno
    '''
    if info.direccion == 'u':
        info.direccion = 'l'
    elif info.direccion == 'd':
        info.direccion = 'r'
    elif info.direccion == 'l':
        info.direccion = 'd'
    elif info.direccion == 'r':
        info.direccion = 'u'

def derecha(): #u = up, d = down, l = left, r = right
    '''
    Funcion encargada de girar en direccion a la derecha dependiendo de la direccion actual.
    Esto lo hace intercalando entre las 4 posiciones posibles: arriba, abajo, izquierda, derecha.

        Parametros:
            (...): No posee parametros

        Retorno:
            (void): No posee retorno
    '''
    if info.direccion == 'u':
        info.direccion ='r'
    elif info.direccion =='d':
        info.direccion = 'l'
    elif info.direccion == 'l':
        info.direccion = 'u'
    elif info.direccion == 'r':
        info.direccion = 'd'

def repetir(listaToken):
    '''
    Funcion encargada de tomar el numero de veces que se tiene que repetir lo que esta dentro de las llaves
    y mediante una lista anteriormente pasada por parametro va repitiendo cada instruccion un numero de veces.
    Esa instruccion la manda a la funcion opciones para que se realice.

        Parametros:
            listaToken (list): Lista que contiene una tupla con los tokens de instrucciones y con el numero de linea
            en que estaba esa instruccion, el primer elemento de la lista corresponde a la instruccion repetir.

        Retorno:
            (void): No posee retorno
    '''
    # cont = 1 #empieza en 1 para saltarse la instruccion de saltar que esta en el [0]
    ciclo = []
    veces = int(listaToken[0][0].group('nRep'))
    largoLista = len(listaToken)

    for i in range(veces):
        for j in range(1,largoLista):
            token = listaToken[j][0]
            info.lineaActual = listaToken[j][1]
            opciones(token,ciclo)

def cierreRep(ciclo):
    '''
    Funcion encargada de ir restando en 1 a la cantidad de llaves.
    Si las llaves son igual a 0, significa que se cerro completamente la instruccion repetir.
    Como el repetir se cerro completamente manda una lista con instrucciones pasada anteriormente a la funcion repetir.

        Parametros:
            ciclo (list): Lista que contiene una tupla con los tokens de instrucciones y con el numero de linea
            en que estaba esa instruccion, el primer elemento de la lista corresponde a la instruccion repetir
            y el ultimo elemento a un cierre de llaves

        Retorno:
            (void): No posee retorno
    '''
    info.llaves-=1
    if info.llaves == 0:
        info.flag = False
        ciclo.pop(-1) #elimina el ultimo cierre de llaves
        repetir(ciclo)
        ciclo.clear()

def opciones(token,ciclo):
    '''
    Funcion que contiene todas las opciones posibles de instrucciones que se pueden realizar. Dependiendo
    de a que grupo pertenezca el token se realizará una u otra instruccion, llamando a su respectiva funcion.
    Si informacion.info.flag es verdadera eso quiere decir que anteriormente habia un repetir y el cierre de llaves aun no llega a 0,
    por lo tanto en este caso el programa solo irá añadiendo a la lista cada instruccion que esté dentro del repetir

        Parametros:
            token (str): Instruccion a realizar
            ciclo (list): Lista que puede ser vacia, asi como tambien puede contener instrucciones o una tupla
            con instrucciones y la linea de la instruccion.

        Retorno:
            (void): No posee retorno
    '''
    if(informacion.info.flag): #flag que indica que todo lo que viene se encuentra dentro de una rep
        ciclo.append((token,info.lineaActual))
        if(token.group('Repetir') != None):
            informacion.info.llaves+=1
        elif(token.group('Cierre') != None):
            cierreRep(ciclo)
    else:
        if(token.group('AvanzarN') != None):
            avanzar(int(token.group('numA')))
        elif(token.group('Avanzar') != None):
            avanzar(1)
        elif(token.group('PintarRGB') != None):
            R = int(token.group('R'))
            G = int(token.group('G'))
            B = int(token.group('B'))
            pintarRGB(R,G,B)
        elif(token.group('Pintar') != None):
            pintar(token.group('color'))
        elif(token.group('Repetir') != None):
            informacion.info.llaves+=1
            ciclo.append((token,info.lineaActual))
            informacion.info.flag = True #entro en un bucle
        elif(token.group('Izquierda') != None):
            izquierda()
        elif(token.group('Derecha') != None):
            derecha()
        else:
            cierreRep(ciclo) #cierre



