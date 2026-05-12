#include <iostream>
#include <cstdlib>
#include <exception>

// ? Estructura del Proceso

struct Proceso {
    int id;
    int prioridad;
    int tiempo_restante;

    // Constructor por defecto
    Proceso() : id(-1), prioridad(-1), tiempo_restante(0) {}

    // Constructor con datos
    Proceso(int i, int p, int t) : id(i), prioridad(p), tiempo_restante(t) {}
};

// Sobrecarga para poder mostrar el cout del proceso
std::ostream& operator<<(std::ostream& os, const Proceso& p) {
    os << "[P" << p.id << "|T" << p.tiempo_restante << "]";
    return os;
};


class ColaExcepcion : public std::exception{
    int val;
    public:
    ColaExcepcion(){val=0;}
    ColaExcepcion(int v){val=v;}
    int getError(){return val;}
    const char* what() const noexcept override{
        switch(val){
            case 0: return "Cola vacia";
            case 1: return "Nuevo valor es insuficiente";
            default: return "Error en la lista";
        }
    }
};
//Permite que la cola funcione con distintos tipos de datos
template <typename T> class Cola{
    private:
    
    T* datos; //Puntero actua como arreglo dinamico
    int tama; //Cantidad actual de elementos en la cola
    int tama_arr; //Capacidad maxima del arreglo en memoria
    int pos_inicial; //Index indica donde comienza (frente)
    int pos_final; //Index indica donde termina (atras)
    
    /*
    Utiliza (%) para hacer un efecto de loop. Si el indixe llega al final
    esta funcion hace que vuelva a empezar desde el inicio
    */

    inline int pos(int p) {
        return p%tama_arr;
    }
    
    public:
    Cola(){
        datos = NULL;
        tama = 0;
        tama_arr = 0;
        pos_inicial = 0;
        pos_final = -1;
    }
    
    Cola(int s){
        datos = (T*)malloc(sizeof(T)*s);
        tama = 0;
        tama_arr = s;
        pos_inicial = 0;
        pos_final = -1;
    }
    
    ~Cola(){
        if(datos)
            free(datos);
    }
    
    void encolar(T x){
        if(tama+1>tama_arr)
            resize(tama_arr+10); // +10 para pedir una cantidad de memoria de golpe y no hacerlo cada vez
        
        pos_final = pos(pos_final+1);
        datos[pos_final] = x;
        
        ++tama;
        
    }
    
    void desencolar(){
        if(estaVacia())
            throw(ColaExcepcion(0));
            
        if( (--tama) == 0){
            pos_final = -1;
            pos_inicial = 0;
        }
        else{
            pos_inicial = pos(pos_inicial+1);
        }
        
    }
    
    T frente(){
        if(estaVacia())
            throw(ColaExcepcion(0));
        
        return datos[pos_inicial];
    }
    
    T atras(){
        if(estaVacia())
            throw(ColaExcepcion(0));
        
        return datos[pos_final];
    }
    
    int tamagno(){
        return tama;
    }
    
    int tamagno_arre(){
        return tama_arr;
    }
    
    /*
    Si la cola crece, crea un arreglo auxiliar temporal (aux).  
    Como los datos pueden estar "envueltos" o desordenados físicamente 
    por la naturaleza circular, el bucle for los copia al nuevo arreglo 
    poniéndolos en orden lineal (desde el índice 0 en adelante). 
    Luego libera la memoria vieja y reasigna.
    */

    void resize(int s){
        T *aux;
        int i;
        
        if(s<tama)
            throw(ColaExcepcion(1));
        
        aux = (T*)malloc(sizeof(T)*tama);
        
        for(i=0; i<tama; ++i)
            aux[i] = datos[pos(pos_inicial+i)];
        
        free(datos);
        datos = (T*)realloc(aux, sizeof(T)*s);
        
        tama_arr = s;
        pos_inicial = 0;
        pos_final = tama-1;
    }
    
    bool estaVacia(){
        return tama==0 ? true: false; //"?"" valor ternario
    }
    
    void mostrar(){
        int i;
        
        for(i=0; i<tama; ++i)
            std::cout << datos[pos(pos_inicial+i)] << " ";
        std::cout << "\n";
    }
    
    void mostrarDebug(){
        int i;
        
        if(pos_final < pos_inicial)
            for(i=0; i<tama_arr; ++i){
                if( i >= pos_inicial || i<= pos_final)
                    std::cout << datos[i] << " ";
                else
                    std::cout <<"- ";
            }
        else
            for(i=0; i<tama_arr; ++i){
                if( i >= pos_inicial && i<= pos_final)
                    std::cout << datos[i] << " ";
                else
                    std::cout <<"- ";
            }
        std::cout << "\n";
    }
};


int main(void){
    //TODO Arreglo de 5 Colas, una para cada nivel de prioridad
    // ? Constructor

    Cola<Proceso> colas[5];
    // ? Procesos
    // Formato: Proceso(id, prioridad, tiempo_restante)
    Proceso p0(0, 0, 30);
    Proceso p1(1, 1, 15);
    Proceso p2(2, 2, 5);
    Proceso p3(3, 3, 10);
    Proceso p4(4, 4, 3);

    // Encolar cada proceso en la cola segun su prioridad
    colas[p0.prioridad].encolar(p0);
    colas[p1.prioridad].encolar(p1);
    colas[p2.prioridad].encolar(p2);
    colas[p3.prioridad].encolar(p3);
    colas[p4.prioridad].encolar(p4);

    // Comprobacion de encolado
    std::cout << "--- Estado Inicial de las Colas ---\n";
    for(int i = 0; i < 5; ++i) {
        std::cout << "Prioridad " << i << ": ";
        if(colas[i].estaVacia()) {
            std::cout << "Vacia\n";
        } else {
            colas[i].mostrar();
        }
    }
    std::cout << "----------------------------------\n";

    //TODO Motor de Round Robin (RR)

    std::cout << "Resultado de la simulacion:\n";

    bool hayProcesos = true;
    while (hayProcesos) {
        hayProcesos = false; // Se asume que no hay, hasta encontrar alguno

        // ? Recorremos las 5 colas de prioridad
        for(int i = 0; i < 5; ++i){
            if (!colas[i].estaVacia()) {
                hayProcesos = true; // Se encuentra un proceso

                // Sacamos el proceso que esta enfrente
                Proceso pActual = colas[i].frente();
                colas[i].desencolar();

                // ? Calculo de Quantum (cuantos ciclos le tocan)
                // ? Regla: prioridad 0 -> 5, 1 -> 4...
                int ciclos_otorgados = 5 - i; // i = cola actual

                //TODO Ejecucion del Proceso
                int ciclos_reales = (pActual.tiempo_restante < ciclos_otorgados)
                                    ? pActual.tiempo_restante
                                    : ciclos_otorgados;

                for (int c = 0; c < ciclos_reales; ++c) {
                    std::cout << pActual.id << ",";
                }

                //Resta el tiempo de ejecucion
                pActual.tiempo_restante -= ciclos_reales;

                //Si aun queda tiempo, se vuelve a encolar
                if (pActual.tiempo_restante > 0) {
                    colas[i].encolar(pActual);
                }
                
            }
        }
    }

    std::cout << "Final\n";
    return 0;
}