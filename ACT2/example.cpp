#include <iostream>
#include <string>

using namespace std;

class Empleado {
private:
    string nombre;
    double sueldo;

public:
    
    Empleado(string n, double s) : nombre(n), sueldo(s) {}

    //Sobrecarga del operador +

    Empleado operator +(const Empleado& otro){ //se pasa por referencia
        double nuevoSueldo = sueldo + otro.sueldo;

        return Empleado("Nuevo Empleado", nuevoSueldo);
    }
    void mostrar() const {
        cout << "Empleado: " << nombre << ", Sueldo: " << sueldo << "$\n"; 
    }

};

int main() {

    Empleado emp1("Ana", 2000);
    Empleado emp2("Luis", 1800);

    Empleado nuevo=emp1+emp2;

    nuevo.mostrar();
}