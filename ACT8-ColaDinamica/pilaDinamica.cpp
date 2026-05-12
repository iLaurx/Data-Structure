#include <iostream>
#include <stdexcept>


/*
* Clase pila
? Justificacion de la version Utilizada
    Elegi la implementacion dinamica basada en una lista lineal y
    simplemente ligada
    1. Simplemente ligada: Una pila opera bajo el principio LIFO 
    donde las insercciones y las extracciones ocurren en un solo lado
    en el final o tope por lo tanto no requieren una navegacion bidireccional
    entonces no se necesita una lista doblemente ligada solo consumiria 
    memoria extra.
    2. Lineal: Al emplear la memoria dinamica con nodos independientes
    la pila puede crecer indefinidamente. Una estructura circular no tiene utilidad en una pila ya que el tope nunca necesita reconectarse a la base, el flujo de datos es
    vertical y descendente.
*/

template <typename T> class Pila {
private:

    //Definicion del Nodo
    struct Nodo {
        int dato;
        Nodo* siguiente;
        //Constructor de la estructura
        Nodo(int valor) : dato(valor), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* final;

    int tam_pila;

public:
    //Constructor
    Pila() {
        frente = nullptr;
        final = nullptr;
        tam_pila = 0;
    }

    ~Pila() {
        while (!estaVacia()) {
            desapilar();
        }
    }

    bool estaVacia() const {
        return final == nullptr;
    }

    void apilar(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = final;
        final = nuevo;
        ++tam_pila;
    }

    void desapilar() {
        if (estaVacia()) {
            std::cout << "Error: La cola ya esta vacia." << std::endl;
            return;
        }

        Nodo* temp = final;
        final = final->siguiente;
        delete temp;
        --tam_pila;
    }

    int tope() const {
        if (estaVacia()) {
            throw std::runtime_error("La pila esta vacia.");
        }
        return final->dato; 
    }

    void mostrar() const {
        if (estaVacia()) {
            std::cout << "La Pila esta vacia." << std::endl;
            return;
        }

        Nodo* actual = final;
        std::cout << "Incio [ ";
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

int main() {

    Pila<int> miPila;

    miPila.apilar(1);
    miPila.apilar(2);
    miPila.apilar(3);

    std::cout << "Pila inicial" << std::endl;
    miPila.mostrar();

    std::cout << "Elemento al frente: " << miPila.tope() << std::endl;

    miPila.desapilar();

    std::cout << "Elemento al frente: " << miPila.tope() << std::endl;
    miPila.desapilar();
    
    std::cout << "Pila final" << std::endl;
    miPila.mostrar();


}