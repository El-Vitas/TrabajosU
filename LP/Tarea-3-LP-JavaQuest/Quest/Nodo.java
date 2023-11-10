package Quest;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public abstract class Nodo {
    protected int id;
    protected List<Nodo> siguientes_nodos = new ArrayList<Nodo>();
    protected String tNodo = "Sin tipo";

    /**
    * Contructor de la clase que inicializa el id
    *
    * @param id: int que contiene el id del nodo
    *
    * @return No posee al ser un constructor
    */
    public Nodo(int id){
        this.id = id;
    }

    /**
    * Metodo que retorna el id
    *
    * @return id: int que contiene el id del nodo
    */
    public int getId() {
        return id;
    }

    /**
    * Metodo que retorna tNodo
    *
    * @return tNodo: String que contiene el tipo de nodo.
    */
    public String getTNodo(){
        return tNodo;
    }

    /**
    * Metodo abstracto que la implementación depende de las clases hijos.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará.
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void
    */
    public abstract void interactuar(Jugador jugador, Scanner sc);

    /**
    * Metodo que agrega un nodo a lista siguientes_nodo
    *
    * @param nodo: Nodo que desea ser agregado a la lista 
    *
    * @return void
    */
    public void agregarNodo(Nodo nodo){
        siguientes_nodos.add(nodo);
    }
}
