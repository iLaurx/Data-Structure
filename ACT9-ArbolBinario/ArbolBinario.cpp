#include <iostream>
using namespace std;

template <typename T>
class Nodo {
public:
    T valor;
    Nodo<T> *izq;
    Nodo<T> *der;

    // Constructor
    Nodo(T val) : valor(val), izq(nullptr), der(nullptr) {}

};

// Clase para el Arbol binario
template <typename T>
class ArbolBinario {
private:
    Nodo<T>* raiz;

    void insertarRec(Nodo<T>*&nodo, T dato) {
        /* Caso base
        Si la posicion esta vacia reserva memoria, 
        asigna el valor y pone sus hijos en NULL.
        */
        if (nodo == nullptr) {
            nodo = new Nodo<T>(dato);
        } 
        /* Caso recursivo
        Si no esta vacia, compara el dato. Si es menor
        se mueve recursivamente a la izq si es >= a der.
        */
        else {
            if (dato < nodo->valor) {
                insertarRec(nodo->izq, dato);
            } else {
                insertarRec(nodo->der, dato);
            }
        }
    }
    // * (Izq - Raiz - Derecha)
    void inorderRec(Nodo<T>* nodo) {
        /*
        Imprime los numeros en orden ascendente
        Recorre primero el subarbol izq, luego procesa
        el nodo actual y finalmente el derecho. 
        */
        if (nodo) {
            inorderRec(nodo->izq);
            cout << nodo->valor << "\n";
            inorderRec(nodo->der);
        }
    }
    // * (Raiz - Izq - Derecha)
    void preorderRec(Nodo<T>* nodo) {
        /*
        Procesa primero la raiz, luego el sub izq y despues
        despues el derecho. Uso para copiar o clonar la 
        estructura del arbol.
        */
        if (nodo) {
            cout << nodo->valor << "\n";
            preorderRec(nodo->izq);
            preorderRec(nodo->der);
        }
    }
    // * (Izq - Derecha - Raiz)
    void postorderRec(Nodo<T>* nodo) {
        /*
        Recorre los sub izq y derecho antes de procesar
        el nodo actual. Es el orden ideal para destruir un arbol de abajo hacia arriba
        */
        if (nodo) {
        postorderRec(nodo->izq);
        postorderRec(nodo->der);
        cout << nodo->valor << "\n";
    }
    }
    // * Libera memoria con postorder
    // asegura que no se pierdan los punteros de los hijos antes de borrar al padre
    void postorderFreeRec(Nodo<T>* nodo) {
        if (nodo) {
            postorderFreeRec(nodo->izq);
            postorderFreeRec(nodo->der);
            delete nodo;
        }
    }

    void preorderEstructuraRec(Nodo<T>* nodo, int tab) {
        /*
        Muestra el arbol de forma visual con flechas tab aumenta
        en cada llamada recursiva para indicar la profundidad
        */
        if (nodo){
            for(int i = 0; i < tab; ++i)
                cout << "->";
            cout << nodo->valor << "\n";
            preorderEstructuraRec(nodo->izq, tab + 1);
            preorderEstructuraRec(nodo->der, tab + 1);

        }
    }

    Nodo<T>* buscarRec(Nodo<T>* nodo, T dato){
        if (nodo == nullptr)
            return nullptr;
        if (dato == nodo->valor)
            return nodo;
        if (dato < nodo->valor)
            return buscarRec(nodo->izq, dato);
        else 
            return buscarRec(nodo->der, dato);
    }
    // * retorna el valor minimo
    T menorRec(Nodo<T>* nodo) {
        if (nodo->izq)
            return menorRec(nodo->izq);
        return nodo->valor;
    }

    Nodo<T>* eliminarRec(Nodo<T>* nodo, T dato){
        /*
        Llama a la función de liberación y luego pone la raíz
        original en NULL para evitar punteros colgados.
        */
        if (nodo == nullptr)
            return nullptr;
        if (dato == nodo->valor) {
            //* Caso 1: Hoja 
            // Se libera el nodo y se retorna null al padre
           if (nodo->izq == nullptr && nodo->der == nullptr) {
            delete nodo;
            return nullptr;
           }
           //* Caso 2: Un solo hijo
           /*Se guarda el puente al hijo único (aux), se libera el 
            nodo actual y se retorna ese hijo para que el padre se 
            conecte con él. */

            if (nodo->izq && nodo->der == nullptr) {
                Nodo<T>* aux = nodo->izq;
                delete nodo;
                return aux;
            }
            if (nodo->der && nodo->izq == nullptr) {
                Nodo<T>* aux = nodo->der;
                return aux;
            }
            //* Caso 3: Dos hijos
            /* Se busca el menor elemento del subárbol derecho (m), 
            se copia su valor en el nodo actual (reemplazándolo) y 
            luego se elimina recursivamente ese nodo menor duplicado 
            en el subárbol derecho. */
            T m = menorRec(nodo->der);
            nodo->valor = m;
            nodo->der = eliminarRec(nodo->der, m);
        } else if (dato < nodo->valor) {
            nodo->izq = eliminarRec(nodo->izq, dato);
        } else {
            nodo->der = eliminarRec(nodo->der, dato);
        }
        return nodo;
    }
    // * Cuenta cuántos nodos hay desde la raíz hasta el elemento
    int nivelRec(Nodo<T>* nodo, T dato) {
        if (nodo == nullptr)
            return -1;
        if (nodo->valor == dato)
            return 1;

        if (dato < nodo->valor) {
            int n = nivelRec(nodo->izq, dato);
            return n > 0 ? 1 + n : -1;
        } else {
            int n = nivelRec(nodo->der, dato);
            return n > 0 ? 1 + n : -1;
        }
    }
    // * Es el nivel del nodo menos 1 (la raíz está a profundidad 0).
    int alturaRec(Nodo<T>* nodo, T dato) {
        if (nodo == nullptr) return -1;
        if (nodo->valor == dato) {
            int alt_izq = nodo->izq ? alturaRec(nodo->izq, nodo->izq->valor) : -1;
            int alt_der = nodo->der ? alturaRec(nodo->der, nodo->der->valor) : -1;
            return (alt_izq > alt_der) ? (alt_izq + 1) : (alt_der + 1);
        }
        if (dato < nodo->valor) return alturaRec(nodo->izq, dato);
        else return alturaRec(nodo->der, dato);
    }

public: 
    //? Metodos Publicos (Interfaz del Usuario)

    ArbolBinario() : raiz(nullptr) {}

    //* Destructor
    ~ArbolBinario() {
        borrar();
    }

    void insertar(T dato) {
        insertarRec(raiz, dato);
    }

    void inorder() {
        inorderRec(raiz);
    }

    void preorder() {
        preorderRec(raiz);
    }
    
    void postorder() {
        postorderRec(raiz);
    }

    void borrar() {
        if (raiz != nullptr) {
            postorderFreeRec(raiz);
            raiz = nullptr;
        }
    }

    void imprimir() {
        if (raiz) {
            inorderRec(raiz);
            cout << "\n";
        } else {
            cout << "\nVacio\n\n";
        }
    }

    void imprimirEstructura() {
        if (raiz == nullptr) {
            cout << "\nVacio\n";
            return;
        }
        else
            preorderEstructuraRec(raiz, 0);
    }

    Nodo<T>* buscar(T dato) {
        return buscarRec(raiz, dato);
    }

    void eliminar(T dato) {
        raiz = eliminarRec(raiz, dato);
    }

    int nivel(T dato) {
        return nivelRec(raiz, dato);
    }

    int profundidad(T dato) {
        int n = nivel(dato);
        return n > 0 ? n - 1 : -1;
    }

    int altura(T dato) {
        return alturaRec(raiz, dato);
    }

};

int main() {
    // Instancia del arbol con tipo de dato int
    ArbolBinario<int> arbol;
    
    cout << "                    ARBOLES BINARIOS            \n";
    cout << "\n\n---------Arbol vacio:---------\n";
    arbol.imprimir();

    arbol.insertar(10);
    arbol.insertar(6);
    arbol.insertar(7);
    arbol.insertar(4);
    arbol.insertar(5);
    arbol.insertar(3);
    arbol.insertar(15);
    arbol.insertar(13);
    arbol.insertar(14);

    cout << "----------Arbol impreso inorder: ---------\n";
    arbol.inorder();
    cout << "----------Arbol impreso preorder: ---------\n";
    arbol.preorder();
    cout << "----------Arbol impreso postorder: ---------\n";
    arbol.postorder();

    cout << "\nBorrar arbol: \n";
    arbol.borrar();
    arbol.imprimir();

    cout << "\nEstructura arbol: \n";
    arbol.imprimirEstructura();

    cout << "\nPrueba de serializacion: \n";
    int datos[] = {10, 6, 4, 3, 5, 7, 15, 13, 14};
    for (int i = 0; i < 9; ++i)
        arbol.insertar(datos[i]);
    
    arbol.imprimirEstructura();

    cout << "\nBuscar elemento: \n";
    Nodo<int>* elem = arbol.buscar(8);
    cout << "Direccion de dato Inexistente: " << elem << "\n";
    
    elem = arbol.buscar(7);
    cout << "Direccion de 7 (valor existente): " << elem << "\n";
    if (elem) cout << elem->valor << "\n";

    cout << "\nFuncion eliminar dato: \n";
    arbol.imprimirEstructura();

    cout << "\nborrar 8 (no existe)\n";
    arbol.eliminar(8);
    arbol.imprimirEstructura();

    cout << "\nBorrar 3: \n";
    arbol.eliminar(3);
    arbol.imprimirEstructura();

    cout << "\nBorrar 15 (hijo derecho): \n";
    arbol.eliminar(15);
    arbol.imprimirEstructura();

    cout << "\nBorrar 13 (hijo izquierdo): \n";
    arbol.eliminar(13);
    arbol.imprimirEstructura();

    cout << "\nBorrar 10 raiz (2 hijos): \n";
    arbol.eliminar(10);
    arbol.imprimirEstructura();

    cout << "\nNivel de 10: " << arbol.nivel(10) << "\n";

    return 0;
}