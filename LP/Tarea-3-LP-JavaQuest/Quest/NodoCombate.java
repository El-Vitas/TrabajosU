package Quest;
import java.util.Random;
import java.util.Scanner;

public class NodoCombate extends Nodo{
    private Personaje enemigo;

    /**
    * Contructor de la clase que inicializa el id llamando al constructor padre, inicializa el tNodo, y crea un enemigo mediante distintos tipos de enemigos predefinidos.
    *
    * @param id: int que contiene el id del nodo
    * @param tNodo: String que contiene el tipo de nodo.
    *
    * @return No posee al ser un constructor
    */
    public NodoCombate(int id, String tNodo){
        super(id);
        this.tNodo = tNodo;
        Random rand = new Random();
        int num = rand.nextInt(5);
        switch (num) {
            case 0:
                enemigo = new Personaje("Ogro", 650, 10,10, 3, 0);
                break;
            case 1:
                enemigo = new Personaje("DMAT", 2000, 15,15, 3, 1);
                break;
            case 2:
                enemigo = new Personaje("DQUI", 1200, 12,12, 3, 1);
                break;
            case 3:
                enemigo = new Personaje("Minion", 220, 5,5, 2, 0);
                break;
            default:
                enemigo = new Personaje("Gigant Minion", 440, 10,10, 2, 0);
                break;
        }
    
    }
    /**
    * Metodo que hace interactuar al jugador con el nodo. La interaccion consiste en un combate, entre el jugador y un enemigo.
    * El combate finaliza cuando la hp de uno de los dos llega a 0
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará.
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void
    */
    public void interactuar(Jugador jugador, Scanner sc){
        Random eleccion = new Random();
        String sNum;
        int num;
        System.out.printf("%s salvaje ha aparecido.\n",enemigo.getNombre());
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
            enemigo.combate(jugador); // parte primero enemigo
        }else{
            jugador.combate(enemigo); // parte primero jugador
        }
        
        if(jugador.getHpActual() != 0){
            System.out.printf("Felicidades derrotaste a %s.\n",enemigo.getNombre());
            System.out.printf("Recibes %d de oro.\n",enemigo.getDinero());
            jugador.setDinero(jugador.getDinero() + enemigo.getDinero());
        }
    }
}
