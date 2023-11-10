import numpy as np # pip install numpy
from PIL import Image # pip install Pllow

#Clase contiene distintas funciones para interactuar con la matrizRGB
class MatrizRGB:
    def __init__(self):
        '''
        Constructor de la matriz.

            Parametros:
                self (self@matrizRGB): Parametro asociado al objeto, al resto de metodos y a los argumentos de la clase.

            Retorno:
                (void): No posee retorno
        '''
        self.__data = [] #lista vacia donde luego ira la matriz
        self.__ancho = 0 #ancho de la matriz

    def crearMatriz(self,num,RGB):
        '''
        Metodo que creara una matriz de num x num  que pertenezca al objeto.

            Parametros:
                self (self@matrizRGB): Parametro asociado al objeto, al resto de metodos y a los argumentos de la clase.
                num (int): numero con el cual se creara el tamaño de la matriz: [num][num].
                RGB ((int,int,int)): 3-Tupla la cual correspondera al color inicial de la matriz.

            Retorno:
                (void): No posee retorno
        '''
        self.__ancho = num
        for i in range(num): #se añade num cantidades de tupla en num filas
            self.__data.append([(RGB)]*num)

    def editarMatriz(self,RGB,posX,posY):
        '''
        Funcion que editara una posicion de la matriz asignandole un nuevo color

            Parametros:
                self (self@matrizRGB): Parametro asociado al objeto, al resto de metodos y a los argumentos de la clase.
                RGB ((int,int,int)): 3-Tupla la cual correspondera al color inicial de la matriz.
                posX (int): Posicion que indica en que fila se encuentra actualmente el indice
                posY (int): Posicion que indica en que columna se encuentra actualmente el indice
                
            Retorno:
                (void): No posee retorno
        '''
        self.__data[posX][posY] = RGB

    def getMatriz(self):
        '''
        Funcion que retorna la matriz

            Parametros:
                self (self@matrizRGB): Parametro asociado al objeto, al resto de metodos y a los argumentos de la clase.

            Retorno:
                self.__data (list): atributo privado de la matriz que contiene a una matriz
        '''
        return self.__data

    def getAncho(self):
        '''
        Funcion que retorna el ancho de la matriz

            Parametros:
                self (self@matrizRGB): Parametro asociado al objeto, al resto de metodos y a los argumentos de la clase.

            Retorno:
                self.__ancho (int): atributo privado de la matriz que contiene al ancho de la matriz
        '''
        return self.__ancho

data = MatrizRGB() #se crea un objeto de la MatrizRGB, el cual se utilizará para manejar la matriz

def MatrizAImagen(matriz, filename='pixelart.png', factor=10):
    '''
    Convierte una matriz de valores RGB en una imagen y la guarda como un archivo png.
    Las imagenes son escaladas por un factor ya que con los ejemplos se producirian imagenes muy pequeñas.
        Parametros:
                matriz (lista de lista de tuplas de enteros): Matriz que representa la imagen en rgb.
                filename (str): Nombre del archivo en que se guardara la imagen.
                factor (int): Factor por el cual se escala el tamaño de las imagenes.
    '''
    matriz = np.array(matriz, dtype=np.uint8)
    np.swapaxes(matriz, 0, -1)

    N = np.shape(matriz)[0]

    img = Image.fromarray(matriz, 'RGB')
    img = img.resize((N*10, N*10), Image.Resampling.BOX)
    img.save(filename)