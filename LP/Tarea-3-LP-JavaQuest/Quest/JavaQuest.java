package Quest;
import java.util.Scanner;

public class JavaQuest{
    /**
    * Metodo main que ejecuta el programa. Se encarga de iniciar el programa, creando un jugador y un mapa, y luego realiza el juego.
    * Mediante un loop seguirá ejecutando el programa hasta que termine el juego.
    * El juego puede acabar solo en 2 casos: cuando la vida del jugador es 0 o cuando la vida del jefe final es cero.
    *
    * @param args: Datos que puede recibir el programa en el momento de ejecutar nuesta aplicación.
    *
    * @return void.
    */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String nombre;
        String sOpcion;
        int opcion;
        
        System.out.println("Ingresa un nombre para tu personaje:");
        while(true){
            try {
                nombre = sc.nextLine();
                break;
            } catch (Exception e) {
                System.out.println("Porfavor ingresa un nombre valido");
            } 
        }
        
        Jugador jugador = new Jugador(nombre,500,20,20,5,1);
        Mapa map =  new Mapa(jugador,sc);  
        boolean flag = true;
        while(flag){
            if(jugador.getHpActual() > 0){ //esto para verificar que no muera 
                if(!map.getNodoActual().siguientes_nodos.isEmpty()){
                    try {
                        System.out.println();
                        System.out.println("¿Que deseas hacer?");
                        System.out.println("(1) Ver el mapa.");
                        System.out.println("(2) Ver estadisticas.");
                        System.out.println("(3) Ver items.");
                        System.out.println("(4) Azanzar.");
                        
                        sOpcion = sc.nextLine();
                        opcion = Integer.parseInt(sOpcion);
                    
                        switch (opcion) {
                            case 1:
                                map.verMapa();
                                break;
                            case 2:
                                jugador.verEstado();
                                break;
                            case 3:
                                jugador.verItems(sc);
                                break;
                            case 4:
                                map.avanzar(jugador,sc);
                                break;
            
                            default:
                                System.out.println("Ingrese numero en el rango 1-4. Intentelo nuevamente.");
                                break;
                        }
                    
                    } catch (NumberFormatException ex) {
                        System.out.println("La opcion ingresada debe ser un numero valido. Ingreselo nuevamente.");
                    }
                }else{ // llego al jefe final y ganó
                    flag = false;
                }
            }else{
                System.out.println("Haz perdido.");
                System.out.println("Fin del juego.");
                flag = false;
            }
        }
        sc.close();
    }
}

