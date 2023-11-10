import instrucciones
import matrizRGB

#Todas las instrucciones no iniciales posibles a realizar
allTokens = instrucciones.re.compile(r"""
        (?P<AvanzarN>Avanzar\ (?P<numA>[1-9]))|
        (?P<Avanzar>Avanzar)|
        (?P<PintarRGB>Pintar\ RGB\((?P<R>\d{1,3}),(?P<G>\d{1,3}),(?P<B>\d{1,3})\))|
        (?P<Pintar>Pintar\ (?P<color>Rojo|Verde|Azul|Negro|Blanco))|
        (?P<Repetir>Repetir\ (?P<nRep>\d+)\ veces\ {)|
        (?P<llave>{)|
        (?P<Izquierda>Izquierda)|
        (?P<Derecha>Derecha)|
        (?P<Cierre>})|
        (?P<Error>[^ \n]+) #Cualquier instruccion que no se encuentre aca es un error
        """,instrucciones.re.X)

#Todas las instrucciones iniciales (2 primeras lineas) posibles a realizar
inicio = instrucciones.re.compile(r"""
    \ *Ancho\ (?P<ancho>\d+)\ *| #Ancho de la matriz
    \ *Color\ de\ fondo\ (?P<color>Rojo|Verde|Azul|Negro|Blanco)\ *| #color de fondo de la matriz
    (?P<RGB>\ *Color\ de\ fondo\ RGB\((?P<R>\d{1,3}),(?P<G>\d{1,3}),(?P<B>\d{1,3})\)\ *) #fondo rgb
    """,instrucciones.re.X)


def analisisSintaxicoInicio(listaErrores):
    '''
    Funcion encargada de realizar un analisis sintaxico del inicio, es decir las primeras 3 lineas del texto.

        Parametros:
            listaErrores (list): Lista en donde se irán añadiendo cada linea en donde se encuentre alguna 
            sintaxis incorrecta

        Retorno:
            (void): No posee retorno
    '''
    for i in range(2):
        linea = ''
        match = instrucciones.re.fullmatch(inicio, instrucciones.informacion.texto[i])
        if match != None:
            if match.group('ancho') == None and i == 0:
                linea = f"{i+1} {instrucciones.informacion.texto[i]}"
            elif match.group('ancho') != None and i == 1: 
                linea = f"{i+1} {instrucciones.informacion.texto[i]}"
        else:
            linea = f"{i+1} {instrucciones.informacion.texto[i]}"
        
        if linea != '':
            listaErrores.append(linea)
        instrucciones.informacion.info.lineaActual+=1

    if(len(instrucciones.informacion.texto) > 2):
        match = instrucciones.re.search(r'\S',instrucciones.informacion.texto[2])
        if match != None:
            linea = f"{3} {instrucciones.informacion.texto[2]}"
            listaErrores.append(linea)

def analisisSintaxico():
    '''
    Funcion encargada de realizar un analisis sintaxico del texto.
    La funcion ira añadiendo cada linea con una sintaxis incorrecto a una lista, esto incluye tambien la funcion repetir
    cuando no cierra correctamente o cuando hay llaves sin un repetir anteriormente.

        Parametros:
            (...): No posee parametros

        Retorno:
            (void): No posee retorno
    '''
    flagError = False #flag que indica si es que hay un error actualmente o no
    listaErrores = []
    linea = ''
    indiceCiclo = -1 #indice que va indicar en que pos se produce el ciclo "mayor"
    analisisSintaxicoInicio(listaErrores)

    for i in range(instrucciones.informacion.info.lineaActual,len(instrucciones.informacion.texto)):
        instrucciones.informacion.info.lineaActual+=1
        for token in instrucciones.re.finditer(allTokens, instrucciones.informacion.texto[i]):
            if token.group('Error') != None: 
                flagError = True
                linea = f"{i+1} {instrucciones.informacion.texto[i]}"

            elif token.group('Repetir') != None:
                if not instrucciones.informacion.info.flag:
                    instrucciones.informacion.info.flag = True
                    indiceCiclo = len(listaErrores)
                    linea = f"{i+1} {instrucciones.informacion.texto[i]}" #mantendra el ciclo como error hasta que se vea que sus llaves son correctas
                instrucciones.informacion.info.llaves +=1
                
            elif token.group('llave') != None: #si hay una llave sola, la añadira como error pero sumara de igual manera como llave
                linea = f"{i+1} {instrucciones.informacion.texto[i]}"
                instrucciones.informacion.info.llaves +=1

            elif token.group('Cierre') != None:
                instrucciones.informacion.info.llaves -=1
                if instrucciones.informacion.info.llaves < 0: #Existe una llave sobrante
                    flagError = True
                    linea = f"{i+1} {instrucciones.informacion.texto[i]}"
                elif instrucciones.informacion.info.llaves == 0 and instrucciones.informacion.info.flag:
                    listaErrores.pop(indiceCiclo) #elimina el ciclo ya que sus llaves son correctas
                    instrucciones.informacion.info.flag = False

            if linea != '' and linea not in listaErrores: #si existen 2 errores sintaxicos en la misma linea, solo marcara 1 vez la linea como error
                listaErrores.append(linea)
                linea = ''

    if flagError or instrucciones.informacion.info.llaves > 0: #si existe un error termina el programa
        #PD: como las llaves son mayores a 0 significa que no se cerraron correctamente por lo tanto el ciclo si es un error
        instrucciones.informacion.errores(listaErrores) #llama a la funcion errores de informacion
        quit()
    else:
        with open("errores.txt",'w') as textError: #si no hay erroes lo escrite en errores.txt
            textError.write('No hay errores')
        instrucciones.informacion.info.lineaActual = 1

    '''
    Funcion encargada de leer instruccion a instruccion, si las instrucciones son de las 2 primeras lineas.
    Realizara su correspondiente funcionamiento, tal como otorgar el ancho a la matriz o el color.
    Si son de la linea 3 en adelante, tomara cada instruccion y llamara a la funcion opciones de instrucciones
    pasandole como parametro el la instruccion.

        Parametros:
            (...): No posee parametros

        Retorno:
            (void): No posee retorno
'''
def tokenize():
    for i in range(2):
        match = instrucciones.re.fullmatch(inicio, instrucciones.informacion.texto[i])
        if match.group('ancho') != None:
            ancho = int(match.group('ancho'))
        elif match.group('color') != None:
            color = instrucciones.colores(match.group('color'))
        elif match.group('RGB') != None:
            R = int(match.group('R'))
            G = int(match.group('G'))
            B = int(match.group('B'))
            instrucciones.validarRGB(R,G,B)
            color = (R,G,B)
        instrucciones.informacion.info.lineaActual +=1
    matrizRGB.data.crearMatriz(ancho,color)

    for i in range(instrucciones.informacion.info.lineaActual,len(instrucciones.informacion.texto)):
        instrucciones.informacion.info.lineaActual+=1
        for token in instrucciones.re.finditer(allTokens, instrucciones.informacion.texto[i]):
            print(token.group(0))
            instrucciones.opciones(token,instrucciones.informacion.info.rep)
        

analisisSintaxico() #primero se realiza el analisis sintaxico
tokenize() #luego se ejecutan las instrucciones
matrizRGB.MatrizAImagen(matrizRGB.data.getMatriz()) #finalmente se crea la imagen de la matriz

