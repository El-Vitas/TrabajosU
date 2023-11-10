package Quest;
import java.util.Random;
import java.util.Scanner;

public class NodoEvento extends Nodo{
    private String descripcion;
    private String descripcionPost1; //descripcion agregada solo para decir algo post recompenzas
    private String descripcionPost2; //descripcion agregada solo para decir algo post recompenzas
    private String alternativa1;
    private String alternativa2;
    private Item resultado1;
    private Item resultado2;

    /**
    * Contructor de la clase que inicializa el id llamando al constructor padre, inicializa el tNodo, y crea un evento, mediante eventos ya predefinidos.
    * El evento consiste en una descripcion, en 2 alternativas, 2 descripciones pos alternativas, y 2 resultados.
    *
    * @param id: int que contiene el id del nodo.
    * @param tNodo: String que contiene el tipo de nodo.
    *
    * @return No posee al ser un constructor
    */
    public NodoEvento(int id, String tNodo){
        super(id);
        this.tNodo = tNodo;
        Random rand = new Random();
        int num = rand.nextInt(6);
        switch(num){
            case 0:
                descripcion = ".... Se escucha un grito a lo lejos. Te preguntas que es.\nAparece un hombre, que desertó de un ramo del DFIS. Te pregunta que quien eres.";
                alternativa1 = "Soy alguien que quiere acabar con el DFIS";
                alternativa2 = "Soy un fiel seguidor del DFIS";
                descripcionPost1 = "El hombre te ayuda y te otorga la espada de los caidos.";
                resultado1 = new Item("Espada de los caidos",0,0,0,1,0);
                descripcionPost2 = "El hombre dice que te va a ayudar.\n¡El hombre mintió! te dió una fruta venenosa.\nTe haz hecho 2 de daño";
                resultado2 = new Item("Fruta venenosa",0,-2,0,0,0);
                break;
            case 1:
                descripcion = "Encuentras una piedra de color misterioso. ¿Que deseas hacer?";
                alternativa1 = "Levantar la piedra";
                alternativa2 = "Seguir de largo";
                descripcionPost1 = "Bajo la piedra habia un caramelo. Recuperaste 1 de hp";
                resultado1 = new Item("caramelo",0,1,0,0,0);
                descripcionPost2 = "Sigues de largo cuando aparece un mono el cuál te entrega una poción.\nTe la tomas.\nrecuperaste 10 de hp";
                resultado2 = new Item("Poción",0,10,0,0,0);
                break;
            case 2:
                descripcion = "¡Que suerte, encontraste un tesoro!";
                alternativa1 = "Abrir";
                alternativa2 = alternativa1;
                descripcionPost1 = "En el tesoro se encuentra 1 espada de los primos.\nTomas la espada.";
                resultado1 = new Item("Espada de los primos", 0, 0,0, 2, 0);
                descripcionPost2 = descripcionPost1;
                resultado2 = resultado1;
                break;
            case 3:
                descripcion = "A lo lejos encuentras una flor. ¿Que deseas hacer?";
                alternativa1 = "Revisar";
                alternativa2 = alternativa1;
                descripcionPost1 = "Revisas... pero no tiene nada.";
                resultado1 = new Item("Flor", 0, 0,0, 0, 0);
                descripcionPost2 = descripcionPost1;
                resultado2 = resultado1;
                break;
            case 4:
                descripcion = "Aparece una mujer.\nDice que te conoce.";
                alternativa1 = "No se quien eres. Adios.";
                alternativa2 = "¿De donde me conoces?";
                descripcionPost1 = "La mujer dice que sabe que eres el guerrero que quiere derrocar al DFIS. Te llama insolente y te entrega una energetica antes de irse";
                resultado1 = new Item("Flor", 0, 0,0, 0, 0);
                descripcionPost2 = "La mujer dice que sabe que eres el guerrero que quiere derrocar al DFIS. Dice que te ayudará, te entrega un gorrito USM.\nTe sientes mucho mejor.";
                resultado2 = new Item("Gorrito USM",0, 15,7, 0, 0);
                break;
            default:
                descripcion = "Aparece una persona enmascarada. Te dice que te acerques que no puede ver bien";
                alternativa1 = "Acercarse";
                alternativa2 = "No hacer nada";
                descripcionPost1 = "La persona se quita la mascara. Te deja un objeto... te das cuenta que ¡Es un infiltrado del DFIS!. El objeto era una bomba. Te haces 5 de daño. El infiltrado se va. ";
                resultado1 = new Item("Bomba", 0, -5,0, 0, 0);
                descripcionPost2 = "La persona dice que eres muy inteligente al averiguar su identidad. Se va corriendo.\nTe preguntas que acaba de pasar cuando te encuentras un objeto en el piso.\nLo recojes.";
                resultado2 = new Item("Manual de laboratorio del DFIS",0, 0,0, 0, 1);
                break;
        }
    }

    /**
    * Metodo que hace interactuar al jugador con el nodo. La interaccion consiste en un dialogo y luego dar a elegir al jugador 2 opciones, dependiendo de la opcion se le entrega una recompenza.
    *
    * @param jugador: Jugador que contiene al jugador con el cual se interactuará.
    * @param sc: Scanner creado en el main. Pasado por distintos parametro para poder seguir pidiendo datos al usuario por consola.
    *
    * @return void
    */
    public void interactuar(Jugador jugador, Scanner sc){
        System.out.printf("%s\n",descripcion);
        String sOpcion;
        int opcion;
        while(true){
            try {
                System.out.printf("(1) %s\n",alternativa1);
                System.out.printf("(2) %s\n",alternativa2);
                sOpcion = sc.nextLine();
                opcion = Integer.parseInt(sOpcion);
                if(opcion == 1){
                    System.out.printf("%s\n",descripcionPost1);
                    resultado1.aplicar(jugador);
                    jugador.addItemsAplicados(resultado1);
                    System.out.printf("%s\n",resultado1.getNombre());
                    resultado1.verInfo();
                    break;
                }else if(opcion == 2){
                    System.out.printf("%s\n",descripcionPost2);
                    resultado2.aplicar(jugador);
                    jugador.addItemsAplicados(resultado2);
                    System.out.printf("%s\n",resultado2.getNombre());
                    resultado2.verInfo();
                    break;
                }else{
                    System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
                }
                
            } catch (Exception ex) {
                System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
            }
        }
    }
}
