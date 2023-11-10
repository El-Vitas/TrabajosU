package Quest;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class NodoTienda extends Nodo{
    private List<Item> inventario = new ArrayList<Item>();

    /**
    * Contructor de la clase que inicializa el id llamando al constructor padre, inicializa la lista de inventario agregando items predefinidos.
    *
    * @param id: int que contiene el id del nodo.
    * @param tNodo: String que contiene el tipo de nodo.
    *
    * @return No posee al ser un constructor
    */
    public NodoTienda(int id, String tNodo){
        super(id);
        this.tNodo = tNodo;
        Random rand = new Random();
        inventario.add(new Item("Dulce Prestigio", 300, 15,2, 0, 0));
        inventario.add(new Item("Semana receso", 750, 999,0, 0, 2));
        inventario.add(new Item("Armadura de los primos", 1000, 0,0, 0, 2));
        inventario.add(new Item("Espada de los primos", 550, 0,0, 2, 0));
        inventario.add(new Item("Bebida energetica", 700, 0,6, 0, 0));
        inventario.add(new Item("Cotona de los primos", 500, 0,0, 0, 1));
        int num = rand.nextInt(2);
        if(num == 1){ // 50% de que aparezca en la tienda
            inventario.add(new Item("Respuestas Certamen", 2600, 14,5, 12, 2));
        }
        
    }
    /**
    * Metodo que hace interactuar al jugador con el nodo. La interaccion consiste en mostrar los items del inventario, y permitirle al jugador ver la informacion del item o comprarlo.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará.
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void
    */
    public void interactuar(Jugador jugador, Scanner sc){
        int size = inventario.size();
        String sOpcion;
        int opcion, opcion2;
        boolean flag = true;
        System.out.println("Felicidades encontraste una tienda.");
        System.out.println("El DI te da la bienvenida. ¿Qué deseas comprar?");
        while(flag){
            try {
                System.out.printf("Dinero actual: %s\n",jugador.getDinero());
                System.out.println("Escribe la opción para ver más información:");
                System.out.println("(0) Terminar compra");
                for(int i = 0; i<size; i++){
                    System.out.printf("(%d) %s\n",i+1,inventario.get(i).getNombre());
                }
                sOpcion = sc.nextLine();
                opcion = Integer.parseInt(sOpcion);
                switch (opcion) {
                    case 0:
                        flag = false;
                        System.out.println("¡Hasta luego, vuelva pronto!");
                        break;
                
                    default:
                        if((opcion-1) < 0 || (opcion-1) >= inventario.size()){
                            System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
                        }else{
                            // item = inventario.get(opcion-1);
                            while(true){
                                try {
                                    inventario.get(opcion-1).verInfo();
                                    System.out.println("(0) Volver atrás");
                                    System.out.println("(1) Comprar");
                                    sOpcion = sc.nextLine();
                                    opcion2 = Integer.parseInt(sOpcion);
                                    if(opcion2 == 0){
                                        break;
                                    }else if(opcion2 == 1){
                                        if(jugador.getDinero() - inventario.get(opcion-1).getPrecio() < 0){
                                            System.out.println("No posees suficiente dinero.");
                                        }else{
                                            comprar(jugador,opcion-1);
                                            System.out.println("Gracias por tu compra.");
                                            break;
                                        }
                                        
                                    }else{
                                        System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
                                    }
                                } catch (Exception e) {
                                    System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
                                }
                            }
                        }
                        
                        break;
                }
                
            } catch (Exception ex) {
                System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
            }
        }
    }
    /**
    * Metodo que al comprar el item le aplica el item al jugador y se lo añade a sus items aplicados.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará.
    * @param pos: Integer que contiene la posicion donde se encuentra el item en el inventario
    *
    * @return void
    */
    public void comprar(Jugador jugador,Integer pos){
        inventario.get(pos).aplicar(jugador);
        jugador.addItemsAplicados(inventario.get(pos));
    }
}
