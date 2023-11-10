package Quest;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.SortedSet;
import java.util.TreeSet;

public class Mapa {
    private int profundidad;
    private NodoInicial Nodo_Inicial;
    private Nodo nodo_actual;
    private List<Nodo> nodos;
    private SortedSet<Edge> edges;
    
    /**
    * Constructor de la clase, encargada de crear un mapa de profundidad entre 3 y 7 niveles, sin contar el nodo inicial y final.
    * Se crean los nodos necesarios y se establecen las distintas conexiones entre ellos, para luego desde el nodo inicial poder avanzar.
    * Al final interactua con el nodo inicial.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará con el nodo inicial
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return No posee al ser un constructor.
    */
    public Mapa(Jugador jugador, Scanner sc){
        Random rand = new Random();
        int randomN;
        int xActual;
        profundidad = rand.nextInt(4) + 4;
        edges = GraphGenerator.Generar(profundidad);
        xActual = edges.first().x;
        Nodo_Inicial = new NodoInicial(xActual,"Nodo inicial");
        nodo_actual = Nodo_Inicial;
        Nodo nodoCreado;
        nodos = new ArrayList<Nodo>();
        nodos.add(Nodo_Inicial); //agrega nodo incial
        int pos = 0;
        for(Edge e: edges){ //Crea los nodos y los agrega a una lista
            if(xActual != e.x){
                xActual = e.x;
                randomN = rand.nextInt(10);// 0-2 = Evento, 3 = Tienda, 4 - 9 = Combate
                if(randomN >= 4){ //Combate
                    nodoCreado = new NodoCombate(xActual,"Nodo combate");
                }else if (randomN <= 2){ //evento
                    nodoCreado = new NodoEvento(xActual, "Nodo evento");
                }else{ //Tienda
                    nodoCreado = new NodoTienda(xActual,"Nodo tienda");
                }
                nodos.add(nodoCreado);
                pos++;
            }
        }
        pos++;
        nodos.add(new NodoJefeFinal(pos,"Nodo jefe final")); //agrega nodo final

        for(Edge e: edges){ // va estableciendo la conexion entre los nodos
            nodos.get(e.x).agregarNodo(nodos.get(e.y));
        }

        Nodo_Inicial.interactuar(jugador, sc); //interactua con el nodo inicial
    }

    /**
    * Metodo que va mostrando el id de los nodos, junto con el tipo de nodo, y a que otro nodo puede ir, junto con el tipo de nodo.
    * Además muestra en que nodo te encuentras actualmente.
    *
    * @return void.
    */
    public void verMapa(){
        for (Edge e : edges) {
            if(e.x == nodo_actual.getId()){
                System.out.printf("(Nodo Actual: %d - %s) -> (%d - %s)\n", e.x,nodos.get(e.x).getTNodo(),e.y,nodos.get(e.y).getTNodo());
            }else{
                System.out.printf("(%d - %s) -> (%d - %s)\n", e.x,nodos.get(e.x).getTNodo(),e.y,nodos.get(e.y).getTNodo());
            }
        }
    }

    /**
    * Metodo encargado de dar al jugador opciones a elegir para avanzar. Luego de eso avanza al nodo indicado.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará con el nodo siguiente al actual
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void
    */
    public void avanzar(Jugador jugador, Scanner sc){
        int nSiguientes = nodo_actual.siguientes_nodos.size();
        boolean flag = true;
        int num;
        String sNum;

        while (flag){
            try {
                System.out.println("¿A que nodo deseas ir?");
                System.out.println("(0) Volver atrás.");
                for(int i = 0; i< nSiguientes; i++){
                    System.out.printf("Nodo numero ( %d ) \n", nodo_actual.siguientes_nodos.get(i).getId());
                }
                sNum = sc.nextLine();
                num = Integer.parseInt(sNum);
                if(num == 0){
                    flag = false;
                } else{
                    for( int i = 0; i < nSiguientes; i++){
                        if(num == nodo_actual.siguientes_nodos.get(i).getId()){
                            nodo_actual = nodo_actual.siguientes_nodos.get(i);
                            flag = false;
                            nodo_actual.interactuar(jugador, sc);
                            break;
                        }
                    }
                    if(flag){
                        System.out.println("El nodo ingresado no es alcanzable. Ingreselo nuevamente.");
                    }
                }
            } catch (NumberFormatException ex) {
                System.out.println("El nodo ingresado debe ser un numero valido. Ingreselo nuevamente.");
            }
        }
    }

    /**
    * Metodo que retorna el nodo_actual
    *
    * @return nodo_actual: nodo_actual en el que se encuentra el jugador.
    */
    public Nodo getNodoActual(){
        return nodo_actual;
    }
}


class Edge implements Comparable<Edge>{
    public final Integer x; //nodo actual
    public final Integer y; //nodo siguiente

    /**
    * Constructor de la clase encargado de inicializar un arco, siendo x el nodo que va hacia y
    *
    * @param x: Integer que contiene id del nodo que desea avanzar
    * @param y: Integer que contiene id del nodo destino
    *
    * @return No posee al ser un constructor.
    */
    public Edge(Integer x, Integer y) {
        this.x = x;
        this.y = y;
    }

    /**
    * Metodo para comparar un arco entregado con el arco actual.
    *
    * @param e: Edge al que se quiere comparar con el actual
    *
    * @return Si first es != 0 retorna first, correspondiente al valor de la comparacion. En caso contrarió retorna second.
    */
    public int compareTo(Edge e) {
        int first = this.x.compareTo(e.x);
        int second = this.y.compareTo(e.y);
        return first != 0 ? first : second;
    }
}

class GraphGenerator {
    /**
    * Metodo encargado de generar un conjunto ordenado de Edge, el cual contiene información sobre de que manera estan conectados los nodos.
    *
    * @param N: Integer que contiene la profundidad del mapa
    * @param seed: Integer que contiene la semilla para generar el valor random
    *
    * @return SortedSet<Edge>: conjunto ordenado de Edge
    */
    public static SortedSet<Edge> Generar(Integer N, Integer seed) {
        Random rand = new Random(seed);

        Integer[][] grid = new Integer[N][4];
        Integer id = 1;
        for (int row = 0; row < N; row++) {
            Integer curr = 0;
            while (curr < 4) {
                Integer blockSize = 1 + rand.nextInt(3);
                for (int col = curr; col < (curr + blockSize) && col < 4; col++) {
                    grid[row][col] = id;
                }
                curr += blockSize;
                id++;
            }
        }

        SortedSet<Edge> edges = new TreeSet<Edge>();
        for (int row = 0; row < N - 1; row++) {
            for (int col = 0; col < 4; col++) {
                Edge edge = new Edge(grid[row][col], grid[row + 1][col]);
                edges.add(edge);
            }
        }
        for (int col = 0; col < 4; col++) {
            Edge edge = new Edge(grid[N - 1][col], id);
            edges.add(edge);
            edge = new Edge(0, grid[0][col]);
            edges.add(edge);
        }

        return edges;
    }

    /**
    * Sobrecarga del metodo generar encargado de llamar al metodo generar dandole de parametro una seed especifica.
    *
    * @param N: Integer que contiene la profundidad del mapa
    *
    * @return SortedSet<Edge>: conjunto ordenado de Edge
    */
    public static SortedSet<Edge> Generar(Integer N) {
        return GraphGenerator.Generar(N, 42);
    }
}
