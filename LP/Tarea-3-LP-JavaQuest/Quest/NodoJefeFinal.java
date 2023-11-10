package Quest;
import java.util.Random;
import java.util.Scanner;

public class NodoJefeFinal extends Nodo{
    Personaje jefe;

    /**
    * Contructor de la clase que inicializa el id llamando al constructor padre, inicializa el tNodo e inicializa el jefe con parametros definidos.
    *
    * @param id: int que contiene el id del nodo.
    * @param tNodo: String que contiene el tipo de nodo.
    *
    * @return No posee al ser un constructor
    */
    public NodoJefeFinal(int id, String tNodo){
        super(id);
        jefe = new Personaje("DFIS", 99999, 18, 18, 4, 2);
        this.tNodo = tNodo;
    }

    /**
    * Metodo que hace interactuar al jugador con el nodo. La interaccion consiste en un combate contra el jefe final.
    * El combate acaba cuando el hp de uno de los dos llega a cero.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará.
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void
    */
    public void interactuar(Jugador jugador, Scanner sc){
        String sNum;
        int num;
        Random eleccion = new Random();
        System.out.printf("%s A aparecido.\n",jefe.getNombre());
        System.out.printf("%s: Asi que ¿quieres derrocarme?. Intentalo si es que puedes.\n",jefe.getNombre());
        System.out.println("Presiona (1) para luchar.");
        while(true){
            try {
                sNum = sc.nextLine();
                num = Integer.parseInt(sNum); 
                if(num == 1){
                    break;
                }else{
                    System.out.println("Presionaste otra tecla. Presiona (1) para luchar.");
                }
            } catch (Exception e) {
                System.out.println("Presionaste otra tecla. Presiona (1) para luchar.");
            }
        }

        num = eleccion.nextInt(2);
        if( num == 0){ // se decide aleatoriamente quien parte primero
            jefe.combate(jugador); // parte primero jefe
        }else{
            jugador.combate(jefe); // parte primero jugador
        }

        if(jugador.getHpActual() != 0){
            System.out.printf("Felicidades derrotaste a %s.\n",jefe.getNombre());
            System.out.println("Lograste derrocar al DFIS. El pueblo celebra y realizan una fiesta en tu nombre.\n");
            System.out.printf("Completaste la aventura de JavaQuest. Felicidades %s\n",jugador.getNombre());
        }
    }
}
