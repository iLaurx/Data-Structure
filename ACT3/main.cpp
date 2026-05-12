#include <iostream>
#include <exception>
#include <string>

using namespace std;

class ListaExcepcion : public exception {
private:
    string mensaje;
    int tipo;
public:
    ListaExcepcion(const string& m, int t) : mensaje(m), tipo(t) {}
    
    // Sobreescribimos what() para devolver el mensaje
    virtual const char* what() const noexcept override {
        return mensaje.c_str();
    }
    
    int getTipo() const { return tipo; }
};

template <typename T>
class Lista {
private:
    T datos[100];
    int tam;
    int capacidad;

public:
    Lista() : tam(0), capacidad(100) {}

    void insertar(T elemento, int pos = -1) {
        if (pos == -1) pos = tam;
        if (tam < capacidad && pos <= tam) {
            for (int i = tam; i > pos; i--) datos[i] = datos[i-1];
            datos[pos] = elemento;
            tam++;
        }
    }

    // Tipo 1 Sobrecarga para lectura o escritura
    T& operator[](int indice) {
        if (indice < 0 || indice >= tam) {
            throw ListaExcepcion("Error Tipo 1: Indice fuera del rango", 1);
        }
        return datos[indice];
    }

    // Tipo 1 Sobrecarga para solo lectura (cout << l1[44])
    const T& operator[](int indice) const {
        if (indice < 0 || indice >= tam) {
            throw ListaExcepcion("Error Tipo 1: Indice fuera del rango", 1);
        }
        return datos[indice];
    }

    // Tipo 2 Excepción si no se encuentra el elemento
    void eliminar(T elemento) {
        int pos = -1;
        for (int i = 0; i < tam; i++) {
            if (datos[i] == elemento) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            throw ListaExcepcion("Error Tipo 2: No se encontro el elemento para eliminar", 2);
        }

        for (int i = pos; i < tam - 1; i++) {
            datos[i] = datos[i+1];
        }
        tam--;
    }
};

int main(void)
{
    Lista<double> l1;
    
    l1.insertar(0.3);
    l1.insertar(10.2);
    l1.insertar(2.3);
    l1.insertar(9.5);
    l1.insertar(11.0);
    l1.insertar(5.7, 2);
    l1.insertar(8.4, 6);
    
    // Excepción Tipo 1 (Escritura)
    try {
        l1[40] = 1.0;
    } catch(ListaExcepcion &e) {
        cout << e.what() << endl;
    }
    
    // Excepción Tipo 1 (Lectura)
    try {
        cout << l1[44] << endl;
    } catch(ListaExcepcion &e) {
        cout << e.what() << endl;
    }
    
    // Excepción Tipo 2 (Búsqueda)
    try {
        l1.eliminar(2.78);
    } catch(ListaExcepcion &e) {
        cout << e.what() << endl;
    }
    
    return 0;
}