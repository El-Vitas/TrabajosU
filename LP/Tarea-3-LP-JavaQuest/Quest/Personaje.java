package Quest;
public class Personaje {
    protected String nombre;
    protected int dinero;
    protected int hp_actual;
    protected int hp_total;
    protected int danio;
    protected int defensa;

    /**
    * Constructor de la clase encargada de inicializar los campos de la clase
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
    public Personaje(String nombre, int dinero,int hp_actual,int hp_total,int danio,int defensa){
        this.nombre = nombre;
        this.dinero = dinero;
        this.hp_actual = hp_actual;
        this.hp_total = hp_total;
        this.danio = danio;
        this.defensa = defensa;
    }
    /**
    * Metodo encargado de realizar y mostrar por pantalla el combate entre el personaje de la clase y un personaje pasado por parametro.
    * Consiste en un loop que acabará unicamente cuando el hp de uno de los dos llegue a 0.
    * 
    * @param personaje: Personaje con el cual combatirá el personaje de la clase

    * @return void
    */
    public void combate(Personaje personaje){
        int danioRealizado;
        int nuevaHp;
        while(true){
            danioRealizado = danio - personaje.getDefensa();
            if(danioRealizado < 0){
                danioRealizado = 0;  
            }
            nuevaHp = personaje.getHpActual()-danioRealizado;
            if(nuevaHp < 0){
                nuevaHp = 0;
            }
            personaje.setHpActual(nuevaHp);
            System.out.printf("%s Ha realizado %d de daño en contra de %s\n",nombre,danioRealizado,personaje.getNombre());
            System.out.printf("HP actual de %s: (%d/%d)\n",personaje.getNombre(),personaje.getHpActual(),personaje.hp_total);
            if(personaje.getHpActual() == 0){
                System.out.printf("%s Se ha debilitado.\n",personaje.getNombre());
                break;
            }
            
            danioRealizado = personaje.getDanio() - defensa;
            if(danioRealizado < 0){
                danioRealizado = 0;  
            }
            nuevaHp = hp_actual - danioRealizado;
            if(nuevaHp < 0){
                nuevaHp = 0;
            }
            hp_actual = nuevaHp;
            System.out.printf("%s Ha realizado %d de daño en contra de %s\n",personaje.getNombre(),danioRealizado,nombre);
            System.out.printf("HP actual de %s: (%d/%d)\n",nombre,hp_actual,hp_total);
            if(hp_actual == 0){
                System.out.printf("%s Se ha debilitado.\n",nombre);
                break;
            }
        }
    }

    /**
    * Metodo que retorna el nombre del personaje
    *
    * @return nombre: String que contiene el nombre del personaje.
    */
    public String getNombre(){
        return nombre;
    }
    /**
    * Metodo que retorna el dinero del personaje
    *
    * @return dinero: int que contiene el dinero del personaje.
    */
    public int getDinero(){
        return dinero;
    }
    /**
    * Metodo que retorna la hp actual del personaje
    *
    * @return hp_actual: int que contiene la hp actual del personaje.
    */
    public int getHpActual(){
        return hp_actual;
    }
    /**
    * Metodo que retorna el hp total del personaje
    *
    * @return hp_total: int que contiene el hp total del personaje.
    */
    public int getHpTotal(){
        return hp_total;
    }
    /**
    * Metodo que retorna el daño del personaje
    *
    * @return danio: int que contiene el daño del personaje.
    */
    public int getDanio(){
        return danio;
    }
    /**
    * Metodo que retorna la defensa del personaje
    *
    * @return defensa: int que contiene la defensa del personaje.
    */
    public int getDefensa(){
        return defensa;
    }

    /**
    * Metodo que establece el hp actual del personaje
    *
    * @param hp_actual: int que contiene la nueva hp actual del personaje
    *
    * @return void
    */
    public void setHpActual(int hp_actual){
        this.hp_actual = hp_actual;
    }
    /**
    * Metodo que establece el dinero del personaje
    *
    * @param dinero: int que contiene el nuevo dinero del personaje
    *
    * @return void
    */
    public void setDinero(int dinero){
        this.dinero = dinero;
    }
    /**
    * Metodo que establece la hp total del personaje
    *
    * @param hp_total: int que contiene la nueva hp_total del personaje
    *
    * @return void
    */
    public void setHpTotal(int hp_total){
        this.hp_total = hp_total;
    }
    /**
    * Metodo que establece el daño del personaje
    *
    * @param danio: int que contiene el nuevo daño del personaje
    *
    * @return void
    */
    public void setDanio(int danio){
        this.danio = danio;
    }
    /**
    * Metodo que establece la defensa del personaje
    *
    * @param defensa: int que contiene la nueva defensa del personaje
    *
    * @return void
    */
    public void setDefensa(int defensa){
        this.defensa = defensa;
    }

}
