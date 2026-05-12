#include <iostream>

using namespace std;

const int TAM_PILA = 5;

struct Pila {
    int Tope;
    int Elementos[TAM_PILA];
};

struct Pila pila;

//Funciones a crear
//incializar
void Inicializar(){
    pila.Tope = -1;

    for (int i = 0; i < TAM_PILA; i++){
        pila.Elementos[i] = 0;   
    }
}
//Empty
bool Empty(){
    return pila.Tope == -1;
}
//Full
bool Full(){
    return pila.Tope == TAM_PILA - 1;
}
//Push
void Push(int x){
    if (Full()){
        cout << "Pila llena" << endl;
    } else {
        pila.Tope++;
        pila.Elementos[pila.Tope] = x;
    }

}
//Pop
int Pop(){
    if (Empty()){
        cout<<"Pila Vacia"<<endl;
        return -1;
    } else {
        int tmp = pila.Elementos[pila.Tope];
        pila.Elementos[pila.Tope] = 0;
        pila.Tope--;
        return tmp;
    }
}
//Imprimir
void Imprimir(){
    for (int i = 0; i <= pila.Tope; i++){
        cout<<"Pila["<<i<<"]: "<<pila.Elementos[i]<<endl;
    }
}


int main(){
    Inicializar();
    Push(1);
    Push(2);
    Push(3);
    Push(4);
    Push(5);
    
    cout<<Pop()<<endl;
    Pop();

    Imprimir();

    return 0;
}