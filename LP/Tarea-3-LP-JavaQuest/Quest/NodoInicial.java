package Quest;
import java.util.Scanner;

public class NodoInicial extends Nodo{
    /**
    * Contructor de la clase que inicializa el id llamando al constructor padre e inicializa el tNodo.
    *
    * @param id: int que contiene el id del nodo.
    * @param tNodo: String que contiene el tipo de nodo.
    *
    * @return No posee al ser un constructor
    */
    public NodoInicial(int id, String tNodo){
        super(id);
        this.tNodo = tNodo;
    }

    /**
    * Metodo que hace interactuar al jugador con el nodo. La interaccion consiste en la historia del juego y las instrucciones del mismo.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará.
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void
    */
    public void interactuar(Jugador jugador, Scanner sc){
        System.out.println("El mundo se encuentra en una eterna oscuridad debido a la falta de salud mental. Es por esto que debes buscar la raiz del problema y enfrentarlo, para asi poder liberar al mundo de las malvadas garras del DFIS.");
        System.out.println("El mundo está en tus manos, dependemos netamente de ti.");
        System.out.println("-----------------------------------------------");
        System.out.printf("¡Que Tal %s! Te damos la bienvenida a JavaQuest. Para que puedas completar tu misión y salvarnos de las garras del DFIS, te ayudaremos con unos consejos:", jugador.nombre);
        System.out.println("En la pantalla se te mostrarán distintas opciones.");
        System.out.println("(1) Ver el mapa: Se te mostrará el mapa de forma que veas la distinta conexíon entre los nodos.");
        System.out.println("(2) Ver estadisticas: Se te mostrará las estadisticas actuales que posees, daño, hp actual, hp total, defensa y tu dinero.");
        System.out.println("(3) Ver items: Se te mostrará los items que haz consumido durante tu aventura.");
        System.out.println("(4) Azanzar: Se mostrará los nodos a los que puedes dirigirte. Al seleccionar alguno avanzas a ese nodo.");
        System.out.println("¡¡Exito en tu aventura.!!");
        System.out.println("---------------------------------------------");
    }
}
