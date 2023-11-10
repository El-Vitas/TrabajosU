package Quest;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Jugador extends Personaje{
    private List<Item> items_aplicados = new ArrayList<Item>();

    /**
    * Constructor de la clase, encargada de llamar al constructor de la clase padre.
    *
    * @param nombre: String que contiene el nombre del personaje.
    * @param dinero: int que contiene el dinero del personaje.
    * @param hp_actual: int que contiene la hp actual del personaje.
    * @param hp_total: int que contiene la hp total del personaje.
    * @param danio: int que contiene el daño del personaje.
    * @param defensa: int que contiene la defensa del personaje.
    *
    * @return No posee al ser un constructor
    */
    public Jugador(String nombre, int dinero,int hp_actual,int hp_total,int danio,int defensa){
        super(nombre, dinero, hp_actual,hp_total,danio, defensa);
    }
    
    /**
    * Metodo que muestra por consola el nombre y las estadisticas del personaje
    *
    * @return void.
    */
    public void verEstado(){
        System.out.printf("Nombre: %s\n", nombre);
        System.out.printf("Dinero: %d\n", dinero);
        System.out.printf("Hp actual: %d\n", hp_actual);
        System.out.printf("Hp total: %d\n", hp_total);
        System.out.printf("daño: %d\n", danio);
        System.out.printf("defensa: %d\n", defensa);
    }

    /**
    * Metodo que muestra por consola los items que el jugador se ha aplicado durante su aventura.
    *
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void.
    */
    public void verItems(Scanner sc){
        int size = items_aplicados.size();
        Item item;
        boolean flag = true;
        int opcion;
        String sOpcion;
        while(flag){
            try {
                System.out.println("Escribe la opción para ver más información:");
                System.out.println("(0) Volver atrás");
                if(size == 0){
                    System.out.println("No posees item aplicados");
                }else{
                    for(int i = 0; i<size; i++){
                        item = items_aplicados.get(i);
                        System.out.printf("(%d) %s\n",i+1,item.getNombre());
                    }
                }
                sOpcion = sc.nextLine();
                opcion = Integer.parseInt(sOpcion);
                switch (opcion) {
                    case 0:
                        flag = false;
                        break;
                
                    default:
                        item = items_aplicados.get(opcion-1);
                        item.verInfo();
                        System.out.println();
                        break;
                }
                
            } catch (Exception ex) {
                System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
            }

        }
        
    }
    /**
    * Metodo que añade el item a la lista de items_aplicados.
    *
    * @return void.
    */
    public void addItemsAplicados(Item item){
        items_aplicados.add(item);
    }
}
