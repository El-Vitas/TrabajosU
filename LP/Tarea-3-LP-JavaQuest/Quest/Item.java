package Quest;
public class Item {
    private String nombre;
    private int precio;
    private int recuperar_hp;
    private int aumentar_hp_total;
    private int aumentar_danio;
    private int aumentar_defensa;
    
    /**
    * Constructor de la clase Item, encargado de inicializar los campos o variables de clase.
    *
    * @param nombre: String que contiene el nombre del item.
    * @param precio: int que contiene el precio del item.
    * @param recuperar_hp: int que contiene la hp que se puede recuperar con el item.
    * @param aumentar_hp_total: int que contiene la hp que se puede aumentar con el item.
    * @param aumentar_danio: int que contiene el daño que se puede aumentar con el item.
    * @param aumentar_defensa: int que contiene la defensa que se puede aumentar con el item.
    *
    * @return No posee al ser un constructor
    */
    public Item(String nombre, int precio, int recuperar_hp, int aumentar_hp_total, int aumentar_danio, int aumentar_defensa){
        this.nombre = nombre;
        this.precio = precio;
        this.recuperar_hp = recuperar_hp;
        this.aumentar_hp_total = aumentar_hp_total;
        this.aumentar_danio = aumentar_danio;
        this.aumentar_defensa = aumentar_defensa;
    }

    /**
    * Metodo que le aplica un item al jugador, aplicandole las estadisticas del item y restando el dinero del item al jugador.
    *
    * @param jugador: Jugador que contiene el jugador al que se le desea aplicar el item.
    *
    * @return void
    */
    public void aplicar(Jugador jugador){
        jugador.setHpTotal(jugador.getHpTotal() + aumentar_hp_total); // primero se aumenta el hp antes de recuperarle
        int hp = jugador.getHpActual() + recuperar_hp;
        if(hp > jugador.getHpTotal()){
            hp = jugador.getHpTotal();
        }
        jugador.setHpActual(hp);
        jugador.setDinero(jugador.getDinero() - precio); 
        jugador.setDanio(jugador.getDanio() + aumentar_danio);
        jugador.setDefensa(jugador.getDefensa() + aumentar_defensa);
    }

    /**
    * Metodo que retorna el campo nombre de la clase.
    *
    * @return nombre: campo nombre de la clase.
    */
    public String getNombre(){
        return nombre;
    }

    /**
    * Metodo que retorna el campo precio de la clase.
    *
    * @return precio: campo precio de la clase.
    */
    public int getPrecio(){
        return precio;
    }

    /**
    * Metodo que muestra por consola información acerca del item.
    *
    * @return void
    */
    public void verInfo(){
        System.out.printf("Precio: %d\n", precio);
        System.out.printf("Restaura %d de HP\n", recuperar_hp);
        System.out.printf("Aumenta %d del HP total\n", aumentar_hp_total);
        System.out.printf("Aumenta %d de daño\n", aumentar_danio);
        System.out.printf("Aumenta %d de defensa\n", aumentar_defensa);
    }
}
