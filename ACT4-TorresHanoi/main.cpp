#include <iostream>

using namespace std;

const int TAM_PILA = 6;

struct Pila {
    int Tope;
    int Elementos[TAM_PILA];
};

struct Pila pilaA;
struct Pila pilaB;
struct Pila pilaC;

//Funciones 
//Reciben la pila por paso por referencia (&)
void Inicializar(Pila &p){
    p.Tope = -1;

    for (int i = 0; i < TAM_PILA; i++){
        p.Elementos[i] = 0;   
    }
}
//Empty
bool Empty(Pila &p){
    return p.Tope == -1;
}
//Full
bool Full(Pila &p){
    return p.Tope == TAM_PILA - 1;
}
//Push
void Push(Pila &p, int x){
    if (Full(p)){
        cout << "Pila llena" << endl;
    } else {
        p.Tope++;
        p.Elementos[p.Tope] = x;
    }
}
//Pop
int Pop(Pila &p){
    if (Empty(p)){
        cout<<"Pila Vacia"<<endl;
        return -1;
    } else {
        int tmp = p.Elementos[p.Tope];
        p.Elementos[p.Tope] = 0;
        p.Tope--;
        return tmp;
    }
}
//Imprimir
void Imprimir(Pila &p){
    for (int i = 0; i <= p.Tope; i++){
        cout<<"Pila["<<i<<"]: "<<p.Elementos[i]<<endl;
    }
}

void Hanoi(int n, Pila &origen, Pila &auxiliar, Pila &destino, char nomOrigen, char nomAuxiliar, char nomDestino){
    if (n == 1){
        Push(destino, Pop(origen));
        cout<<"Mover disco de"<<nomOrigen<<" a "<<nomDestino<<endl;
    } else {
        // 1 Mover n-1 discos al auxiliar 
        Hanoi( n - 1, origen, destino, auxiliar, nomOrigen, nomDestino, nomAuxiliar);

        // 2 Mover el disco restante al destino
        Push(destino, Pop(origen));
        cout<<"Mover disco de"<<nomOrigen<<" a "<<nomDestino<<endl;

        // 3 Mover los n-1 discos del auxiliar al destino
        Hanoi(n - 1, auxiliar, origen, destino, nomAuxiliar, nomOrigen, nomDestino);
    }
}


int main(){
    Inicializar(pilaA);
    Inicializar(pilaB);
    Inicializar(pilaC);
    //Valores de los discos entre mas grande el numero mas peque;o el disco
    Push(pilaA, 6);
    Push(pilaA, 5);
    Push(pilaA, 4);
    Push(pilaA, 3);
    Push(pilaA, 2);
    Push(pilaA, 1);

    int numDiscos = TAM_PILA;

    // Comprueba e imprime las dos pilas Primero A despues la pila C
    cout<<"Pila Inicial A"<< endl;
    Imprimir(pilaA);

    cout << "Movimientos a realizar:" << endl;

    Hanoi(numDiscos, pilaA, pilaB, pilaC, 'A', 'B', 'C');

    cout<<"Pila Final C"<< endl;
    Imprimir(pilaC);

    return 0;
}