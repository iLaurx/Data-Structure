#include <iostream>
#include <stdexcept>



/*
* Clase cola
? Justificacion de la version Utilizada
    Elegi una implementacion basada en una lista lineal y simplemente ligada
    utilizando un punto de encabezado (frente) y un puntero adicional (final)
    1. Simplemente ligada: Una cola opera estricatmente en dos extremos (insercion
    al final, extraccion al inicio). No requiere de navegacion bidireccional y un enlace
    dobleme consumiria memoria adicional (8 bytes extra por nodo en 64 bits) sin aportar 
    ninguna ventaja de complejidad computacional.
    2. Lineal (no circular): Al usar memoria dinamica (nodos instanciados con 'new'), 
    la estructura puede crecer sin limite fisico estricto. Las colas circulares son altamente
     eficientes en implementaciones estaticas (arreglos) para reutilizar espacios
    vacios, pero en una lista enlazada dinamica, conectar el final al inicio agregaria 
    logica adicional innecesaria para una cola estandar
*/

template <typename T> class Cola {
private:
     //Definicion del Nodo
    struct Nodo {
        T dato;
        Nodo* siguiente;
        // Constructor de la estructura
        Nodo(int valor) : dato(valor), siguiente(nullptr) {}
    };
    
    Nodo* frente; // Encabezado: apunta al primer nodo (proximo a salir)
    Nodo* final;  // Apunta al ultimo nodo ingresado

public:
    // Constructor
    Cola(){
        frente = nullptr;
        final = nullptr;
    }

    // Destructor
    ~Cola(){
        while (!estaVacia()) {
            desencolar();
        }
    }

    // Metodo para verificar estado
    bool estaVacia() const {
        return frente == nullptr;
    }

    // Operacion Encolar (Push / Enqueue) - 0(1)
    void encolar(int valor) {
        Nodo* nuevoNodo = new Nodo(valor);

        if(estaVacia()) {
            frente = nuevoNodo;
            final = nuevoNodo;
        } else { 
            final->siguiente = nuevoNodo;
            final = nuevoNodo; // Actualizamos el puntero final
        }
    }

    void desencolar() {
        if (estaVacia()) {
            std::cout << "Error: La cola ya esta vacia." << std::endl;
            return;
        }

        Nodo* nodoABorrar = frente;
        frente = frente->siguiente; // El frente avanza al siguiente en la fila

        // Si al avanzar el frente la cola queda vacia, el final debe ser nulo
        if (frente == nullptr) {
            final = nullptr;
        }

        delete nodoABorrar; // Liberacion de memoria dinamica
    }

    int obtenerFrente() const {
        if (estaVacia()) {
            throw std::runtime_error("La cola esta vacia, no hay elementos.");
        }
        return frente->dato;
    }

    void mostrar() const {
        if (estaVacia()) {
            std::cout << "La cola esta vacia." << std::endl;
            return;
        }

        Nodo* actual = frente;
        std::cout << "Frente [ ";
        while (actual != nullptr) {
            std::cout << actual->dato;
            if (actual->siguiente != nullptr) {
                std::cout << " -> ";
            }
            actual = actual->siguiente;
        }
        std::cout << "] Final" << std::endl;
    }
};

// Ejemplo 
int main() {
    Cola<int> miCola;

    miCola.encolar(10);
    miCola.encolar(20);
    miCola.encolar(30);

    miCola.mostrar();

    std::cout << "Elemento al frente: " << miCola.obtenerFrente() << std::endl;

    miCola.desencolar();
    std::cout << "Se extrajo un elemento. Nuevo frente: " << miCola.obtenerFrente() << std::endl;

    miCola.mostrar();

    miCola.desencolar();
    miCola.desencolar();

    // Intento de extraer una cola vacia
    miCola.desencolar();

    return 0;
}