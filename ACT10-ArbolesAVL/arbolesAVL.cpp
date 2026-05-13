#include <iostream>

template <typename T>
struct Nodo {
    T valor;
    Nodo* izq;
    Nodo* der;
    unsigned int alt;

    // Constructor
    Nodo(T v) : valor(v), izq(nullptr), der(nullptr), alt(0) {}
};

//? Clase envolvente para ArbolAVL
template <typename T>
class ArbolAVL {
private:
    Nodo<T>* raiz;

    // Metodos auxiliares
    
    unsigned int alturaNodo(Nodo<T>* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->alt;
    }

    unsigned int actualizarAltura(Nodo<T>* nodo) {
        if (nodo->izq == nullptr && nodo->der == nullptr) return 0;
        unsigned int i = alturaNodo(nodo->izq);
        unsigned int d = alturaNodo(nodo->der);
        return i > d ? i + 1 : d + 1; 
    }

    int balance(Nodo<T>* nodo) {
        if (nodo == nullptr) return 0;
        unsigned int i = (nodo->izq == nullptr) ? 0 : 1 + alturaNodo(nodo->izq);
        unsigned int d = (nodo->der == nullptr) ? 0 : 1 + alturaNodo(nodo->izq);
        return i - d;
    }

    Nodo<T>* rotarIzq(Nodo<T>* nodo) {
        Nodo<T>* n = nodo->der;
        Nodo<T>* aux = n->izq;

        n->izq = nodo;
        nodo->der = aux;

        nodo->alt = actualizarAltura(nodo);
        n->alt = actualizarAltura(n);
        return n;
    }

    Nodo<T>* rotarDer(Nodo<T>* nodo) {
        Nodo<T>* n = nodo->izq;
        Nodo<T>* aux = n->der;

        n->der = nodo;
        nodo->izq = aux;

        nodo->alt = actualizarAltura(nodo);
        n->alt = actualizarAltura(n);
        return n;
    }

    Nodo<T>* insertarAux(Nodo<T>* nodo, T dato) {
        if (nodo == nullptr) return new Nodo<T>(dato);

        if (dato < nodo->valor) {
            nodo->izq = insertarAux(nodo->izq, dato);
        } else if (dato > nodo->valor) {
            nodo->der = insertarAux(nodo->der, dato);
        } else {
            return nodo; // Valores duplicados no permitidos
        }

        nodo->alt = actualizarAltura(nodo);
        int b = balance(nodo);

        // RR
        if (b < -1 && dato > nodo->der->valor) return rotarIzq(nodo);
        // LL
        if (b > 1 && dato < nodo->izq->valor) return rotarDer(nodo);
        // RL
        if (b < -1 && dato < nodo->der->valor) {
            nodo->der = rotarDer(nodo->der);
            return rotarIzq(nodo);
        }
        // LR
        if (b > 1 && dato > nodo->izq->valor) {
            nodo->izq = rotarIzq(nodo->izq);
            return rotarDer(nodo);
        }

        return nodo;
    }

    T menor(Nodo<T>* nodo) {
        if (nodo->izq) return menor(nodo->izq);
        return nodo->valor;
    }

    Nodo<T>* eliminarAux(Nodo<T>* nodo, T dato) {
        if (nodo == nullptr) return nullptr;

        if (dato < nodo->valor) {
            nodo->izq = eliminarAux(nodo->izq, dato);
        } else if (dato > nodo->valor) {
            nodo->der = eliminarAux(nodo->der, dato);
        } else {
            if (nodo->izq == nullptr || nodo->der == nullptr) {
                Nodo<T>* aux = nodo->izq ? nodo->izq : nodo->der;

                if (aux == nullptr) {
                    aux = nodo;
                    nodo = nullptr;
                } else {
                    *nodo = *aux; 
                }
                delete aux;
            } else {
                T m = menor(nodo->der);
                nodo->valor = m;
                nodo->der = eliminarAux(nodo->der, m);
            }
        }

        if (nodo == nullptr) return nullptr;

        nodo->alt = actualizarAltura(nodo);
        int b = balance(nodo);

        if (b > 1 && balance(nodo->izq) >= 0) return rotarDer(nodo);
        if (b > 1 && balance(nodo->izq) < 0) {
            nodo->izq = rotarIzq(nodo->izq);
            return rotarDer(nodo);
        }
        if (b < -1 && balance(nodo->der) <= 0) return rotarIzq(nodo);
        if (b < -1 && balance(nodo->der) > 0) {
            nodo->der = rotarDer(nodo->der);
            return rotarIzq(nodo);
        }

        return nodo;
    }

    void inorderAux(Nodo<T>* nodo) {
        if (nodo) {
            inorderAux(nodo->izq);
            std::cout << nodo->valor << "\n";
            inorderAux(nodo->der);
        }
    }

    void preorder_estructuraAux(Nodo<T>* nodo, int tab) {
        if (nodo) {
            for (int i = 0; i < tab; ++i) std::cout << "->";
            std::cout << nodo->valor << "(" << nodo->alt << ", " << balance(nodo) << ")\n";
            preorder_estructuraAux(nodo->izq, tab + 1);
            preorder_estructuraAux(nodo->der, tab + 1);
        }
    }

    void postorder_free(Nodo<T>* nodo) {
        if (nodo) {
            postorder_free(nodo->izq);
            postorder_free(nodo->der);
            delete nodo;
        }
    }

    Nodo<T>* buscarAux(Nodo<T>* nodo, T dato) {
        if (nodo == nullptr) return nullptr;
        if (dato == nodo->valor) return nodo;
        if (dato < nodo->valor) return buscarAux(nodo->izq, dato);
        return buscarAux(nodo->der, dato);
    }

public:
    // Constructor
    ArbolAVL() : raiz(nullptr) {}

    // Destructor
    ~ArbolAVL() {
        borrar();
    }

    // Métodos públicos
    void insertar(T dato) {
        raiz = insertarAux(raiz, dato);
    }

    void eliminar(T dato) {
        raiz = eliminarAux(raiz, dato);
    }

    bool buscar(T dato) {
        return buscarAux(raiz, dato) != nullptr;
    }

    void borrar() {
        postorder_free(raiz);
        raiz = nullptr;
    }

    void imprimir() {
        if (raiz) {
            inorderAux(raiz);
            std::cout << "\n";
        } else {
            std::cout << "\nVacio\n\n";
        }
    }

    void imprimir_estructura() {
        if (raiz == nullptr) {
            std::cout << "\nVacio\n";
        } else {
            preorder_estructuraAux(raiz, 0);
        }
    }
};

int main() {
    ArbolAVL<int> arbol;

    std::cout << "--- INICIANDO PRUEBAS DEL ARBOL AVL ---\n\n";

    std::cout << "1. Prueba de Insercion y Balanceo\n";
    // Inserciones que provocarán varias rotaciones
    arbol.insertar(30);
    arbol.insertar(20);
    arbol.insertar(10); // Provoca rotación simple a la derecha (LL)
    arbol.insertar(40);
    arbol.insertar(50); // Provoca rotación simple a la izquierda (RR)
    arbol.insertar(25); // Provoca rotación doble (LR) en futuros nodos dependiendo de la inserción
    arbol.insertar(27); 
    
    std::cout << "Recorrido Inorder:\n";
    arbol.imprimir();

    std::cout << "Estructura del arbol -> valor(altura, balance):\n";
    arbol.imprimir_estructura();

    std::cout << "\n---------------------------------------\n";
    std::cout << "2. Prueba de Busqueda\n";
    int buscar_existente = 27;
    int buscar_inexistente = 100;

    std::cout << "Buscando " << buscar_existente << ": " 
              << (arbol.buscar(buscar_existente) ? "Encontrado" : "No encontrado") << "\n";
    std::cout << "Buscando " << buscar_inexistente << ": " 
              << (arbol.buscar(buscar_inexistente) ? "Encontrado" : "No encontrado") << "\n";

    std::cout << "\n---------------------------------------\n";
    std::cout << "3. Prueba de Eliminacion\n";
    
    std::cout << "Eliminando 50 (Nodo hoja)...\n";
    arbol.eliminar(50);
    arbol.imprimir_estructura();

    std::cout << "\nEliminando 20 (Nodo con hijos)...\n";
    arbol.eliminar(20);
    arbol.imprimir_estructura();

    std::cout << "\nEliminando 30 (Raiz actual)...\n";
    arbol.eliminar(30);
    arbol.imprimir_estructura();

    std::cout << "\n---------------------------------------\n";
    std::cout << "4. Prueba de Borrado Completo (Liberacion de memoria)\n";
    arbol.borrar();
    
    std::cout << "Estructura despues de borrar todo:\n";
    arbol.imprimir_estructura();

    std::cout << "\n--- FIN DE LAS PRUEBAS ---\n";

    return 0;
}