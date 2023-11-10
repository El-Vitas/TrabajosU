# Instrucciones
## 1.	Certamen
Tras exitosamente superar tus certámenes con la ayuda de la herramienta que programaste en la tarea anterior, te encuentras finalmente con algo de tiempo libre en tus manos, y decides utilizarlo para continuar con uno de tus hobbies, ¡hacer videojuegos!
## 2.	Java Quest
Para esta tarea deberán crear el juego Java Quest utilizando programación orientada a objetos en Java. En este juego los jugadores deben seleccionar un camino para avanzar por una serie de encuentros de distintos tipos con el objetivo de derrotar al jefe final.

<image src="img/Imagen2.jpg" alt="Descripción de la imagen">
Figura 1: Ejemplo de un mapa de encuentros en un juego similar (Slay the Spire).
  
## 3. Definición
Para crear Java Quest deberán implementar (y utilizar) las siguientes clases: Personajes, Jugador, Items, Mapa, y los distintos tipos de nodos que puede haber en un mapa. A continuación, se presenta un diagrama de clases que describe que debe contener cada una de estas.
<image src="img/Imagen.jpg" alt="Descripción de la imagen">  
  
*Figura 2: Clases a implementar*
  
### 3.1. Personaje
* **nombre**: Nombre del personaje.
* **dinero**: Cuanto dinero tiene el personaje. En el caso del jugador representa cuanto puede gastar, en el caso de un enemigo corresponde a la cantidad de dinero que le otorga al jugador al ser derrotado.
* **hp_actual**: Cantidad de vida que tiene actualmente el personaje, no puede exceder el **hp_total**.
* **hp_total**: Cantidad de vida máxima que puede tener el personaje.
* **danio**: Cantidad de vida que le resta a su oponente al combatir (antes de aplicar **defensa**).
* **defensa**: Cantidad de daño evitado por golpe al combatir.
* **combate**: Realiza el combate entre dos personajes. Durante un combate se selecciona un personaje aleatoriamente para comenzar y posteriormente se alternan al atacar. Durante un ataque, el personaje defensor pierde vida equivalente al daño de su oponente menos la **defensa** del defensor. El combate termina una vez el **hp_actual** de uno de los personajes sea menor o igual a 0.
  
### 3.2. Jugador
Extiende la clase Personaje.
* **items_aplicados**: Una lista con los items que el personaje ha adquirido durante su aventura.
* **verEstado**: Muestra al usuario los atributos actuales del jugador (**nombre**, **dinero**, **hp_actual**, **hp_total**, **danio** y **defensa**).
* **verItems**: Muestra al usuario los items que ha adquirido.
  
### 3.3. Item
* **precio**: Corresponde a cuánto **dinero** cuesta adquirir un **item** desde la tienda.
* **recuperar_hp**: Cantidad de hp que recupera al jugador.
* **aumentar_hp_total**: Cantidad de hp  total que aumenta al jugador. Un aumento de **hp_total** no afecta al **hp_actual**.
* **aumentar_danio**: Cantidad de daño que aumenta al jugador.
* **aumentar_defensa**: Cantidad de **defensa** que aumenta al jugador.
* **aplicar**: Agrega el **item** a la lista de items aplicados del jugador y aplica sus estadísticas.
Si lo desean los atributos que no son el precio pueden incluir valores negativos. En caso de que ocurra que **hp_total** es menor que **hp_actual**, se debe dejar **hp_actual** igual a **hp_total** (lo que puede finalizar el juego si hp  actual es menor o igual a 0).
  
### 3.4. Mapa
* **profundidad**: Cantidad de ”pisos“ que tiene el mapa (no incluye el nodo inicial ni el nodo del jefe final).
* **nodo_inicial**: Nodo inicial del mapa.
* **nodo actual**: Nodo en el que se encuentra el jugador.
* **verMapa**: Permite al usuario ver el mapa completo (queda a su criterio si se muestra el mapa completo, se muestra nivel a nivel o de otra forma).
* **avanzar**: Le muestra al usuario los nodos a los que puede avanzar, le pide seleccionar uno y hace al jugador interactuar con ese nodo.
  
### 3.5. Nodo
* **id**: Identificador, opcional, pero puede ser útil para generar el mapa.
* **siguientes_nodos**: Lista de nodos a los cuales se puede avanzar desde el actual.
* **agregarNodo**: Agrega un nodo a la lista de **siguientes_nodos**.
  
### 3.6. NodoInicial
* **interactuar**:  Le muestra al usuario una introducción al juego (Instrucciones y pueden incluir una historia).
  
### 3.7. NodoEvento
* **descripción**: Pequeña historia que describe un encuentro del jugador en su aventura.
* **alternativas**: Dos opciones que puede tomar en el encuentro descrito.
* **recompensas**: Que le sucede al jugador tras tomar una de las **alternativas**.
* **interactuar**: Le muestra al usuario la descripción del evento y las **alternativas** que puede seleccionar (No se muestran explícitamente las recompensas asociadas a cada alternativa). Cuando el usuario selecciona una alternativa se le aplica la recompensa correspondiente.
  
### 3.8. NodoTienda
* **inventario**: Lista de items disponibles para **comprar**.
* **comprar**: Le aplica el item en la posición indicada al jugador.
* **interactuar**: Le muestra los items en el inventario de la tienda al usuario y cuánto dinero tiene a su disposición. Le permite comprar tantos items como quiera.
  
### 3.9. NodoCombate o NodoJefeFinal
Se implementan de la misma forma, pero JefeFinal se inicia con un enemigo más poderoso.
* **enemigo/jefe**: Enemigo al cual se debe enfrentar el jugador.
* **interactuar**: Realiza el combate informando al usuario los resultados de cada ataque realizado y determina al ganador.
  
### 3.10.	Otros métodos y atributos
Todos los métodos y atributos mencionados deben estar implementados en la tarea, pero además deberán incluir constructores para todas las clases que los necesiten, getters y setters donde estimen necesario (no deben acceder a los atributos directamente desde fuera de una clase, estos deben ser obligatoriamente privados) y métodos o atributos adicionales si así lo desean.
  
## 4. Inicialización del juego
Cuando se inicia el juego se le solicita al usuario ingresar un nombre para su personaje, y se inician sus estadísticas con:
* **dinero** = 500
* **hp_actual** = 20
* **hp_total** = 20
* **danio** = 5
* **defensa** = 1
Posterior a esto se genera un mapa de forma aleatoria.
Los tipos de nodos intermedios también son determinados aleatoriamente. Cada nodo tiene intermedio tiene una probabilidad dada de ser de uno de los tipos:
* **NodoEvento**: 30%
* **NodoTienda**: 10%
* **NodoCombate**: 60%
  
En los nodos de tipo Evento se inicializan con un set de descripción, alternativas y recompensas al azar. Las posibles descripciones, alternativas y estadísticas de items son arbitrarias y quedan a su criterio o creatividad.
En los nodos de tipo Tienda se deben inicializar con una cantidad aleatoria el inventario con entre 5 y 8 items, estos items pueden ser creados con estadísticas al azar (intentando que tenga valores razonables para poder progresar en el juego) o con estadísticas seleccionadas aleatoriamente de una lista de items ya creados.
Para los nodos de Combate y JefeFinal, se debe crear un enemigo aleatorio siguiendo el mismo criterio que para los items de la tienda (estadísticas aleatorias pero que permitan jugar o seleccionar aleatoriamente uno de varios personajes ya creados).
Una vez generado todo, al jugador se le muestra una introducción al juego.
  
## 5. El juego
Una vez iniciado el jugador y el mapa, el resto del juego es simple. En cada momento el jugador puede tomar una de las siguientes acciones: ver el mapa, ver sus estadísticas, ver sus items o avanzar. El juego termina una vez el jugador no puede seguir luchando (hp  actual menor o igual a 0) o el jugador derrota al jefe final y se le muestra un mensaje felicitando.

## 6. Programa
  
Programa encargado de realizar un juego llamado JavaQuest. El juego consiste en ir avanzando por nodos, pudiendo acceder al mapa, a las estadisticas, ver los items aplicados, y avanzar. Los nodos intermedios pueden ser de 3 tipos, nodos evento, nodos combate y nodos tienda.
En los nodos evento ocurre un evento en particular donde el jugador puede seleccionar 2 opciones, dependiendo de la opcion se le entrega una recompenza. 
En los nodos combate el jugador se enfrenta a un enemigo, el combate termina cuando el hp de uno de los 2 llegue a cero. Si el jugador pierde termina el juego, si el jugador gana obtiene dinero.
En los nodos tienda el jugador puede comprar items de un inventario el cual será mostrado por consola.
Al llegar al final te enfrentas a un jefe. Si ganas el juego acaba y completas tu aventura.

### Sobre el codigo

La representación del mapa, será mediante el codigo entregado, pero agregandole los tipos de nodos y el nodo actual.
Se recomienda responder mediante las alternativas que se les indiquen y no con otras alternativas, aunque de igual forma se crearon validadores en caso de que el usuario ingrese por error otro valor que no corresponda al solicitado.

**El programa cuenta 1 carpeta llamada Quest que contiene 11 archivos .java**

### makefile:
Fuera de la carpeta Quest se encuentra un makefile para poder compilar y ejecutar el programa. Se recomienda tener la carpeta y el makefile dentro del mismo directorio, (¡el makefile fuera de la carpeta Quest, pero la carpeta y el makefile en el mismo directorio!). Los comandos que puede realizar son los siguientes:
* make : Compilará el programa.
* make run : Ejecutará el programa.
* make clean : Eliminará los archivos creados al compilarse el programa.
