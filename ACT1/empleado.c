#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fecha
{
    unsigned char dia;
    unsigned char mes;
    unsigned char a;
}Fecha;

typedef union CN
{
    char condicion;
    int ne;
}CN;

typedef struct Empleado
{
    char nombre[30];
    char apellidos[40];
    char status;
    CN cn;
    Fecha nacimiento;
    Fecha contratacion;
    Fecha djm;
    
}Empleado;

//
void validarFecha(Fecha f) {
    //Valida el ano (1900-2026)
    if (f.a > 126) {
        printf("Error: Ano fuera de rango\n");
        exit(1);
    }

    if (f.mes < 1 || f.mes > 12) {
        printf("Error: Mes invalido\n");
        exit(1);
    }
    //Logica de Dias
    //Arreglo de dias, el cero para ajustarlo al indice de mes
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //A;o bisiesto, 
    int anioReal = f.a + 1900;
    // Si el anio es bisiesto, acutalizamos febrero en el arreglo
    if ((anioReal % 4 == 0 && anioReal % 100 != 0) || (anioReal % 400 == 0)) {
        diasPorMes[2] = 29;
    }

    if (f.dia < 1 || f.dia > diasPorMes[f.mes]) {
        printf("Error: Dia fuera de rango para el mes y anio ingresado\n");
        exit(1);

    }
}

void leerCadena(char *destino, int tam) {
    fflush(stdin); // metodo para limpiar el buffer
    if(fgets(destino, tam, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

Fecha capturarFecha() {
    Fecha f;
    int d, m, a;
    if (scanf("%d %d %d", &d, &m, &a) != 3) exit(1);
    f.dia = (unsigned char)d;
    f.mes = (unsigned char)m;
    f.a = (unsigned char)(a - 1900); //Guardamos el desfase
    validarFecha(f);
    return f;
}
/*
void capturarDatosCondicion(Empleado *e) {
    printf("Ingrese condicion (A, J, D, F): ");
    scanf(" %c", &e->cn.condicion) {
        case 'A':
            //NO requiere datos extra
            break;
        case 'J':
        case 'D':
        case 'F':
            //Numero de empleado y fecha djm
            printf("Ingrese numero de empleado: ");
            if (scanf("%d", &e->cn.ne) != 1) exit(1):

            printf("Ingrese fecha DJM (dia mes anio): ");
            validarFecha();
            break;
        default:
            printf("Error: Condicion no valida\n");
            exit(1);

    }
}
*/

int main() {
    Empleado registros[100];
    int i = 0; // Para el primer empleado
    
    printf("--- Registro de Empleado ---\n");

    printf("Nombre: ");
    leerCadena(registros[i].nombre, 30);

    printf("Apellidos: ");
    leerCadena(registros[i].apellidos, 40);

    printf("Status (0: Inactivo, 1: Activo): ");
    int st;
    if (scanf("%d", &st) != 1 || (st != 0 && st != 1)) {
        printf("Error: Status debe ser binario (0 o 1).\n");
        exit(1);
    }
    registros[i].status = (char)st;

    printf("Nacimiento (dia mes año): ");
    registros[i].nacimiento = capturarFecha();

    printf("Contratación (dia mes año): ");
    registros[i].contratacion = capturarFecha();

    printf("Condición (A: Activo, J: Jubilado, D: Despedido, F: Fallecido): ");
    char c;
    scanf(" %c", &c);
    
    // Validar condición antes de meter a la unión
    if (c != 'A' && c != 'J' && c != 'D' && c != 'F') {
        printf("Error: Condición no válida.\n");
        exit(1);
    }

    // Dependiendo de la condición, pedimos NE y Fecha DJM
    if (c == 'J' || c == 'D' || c == 'F') {
        printf("Número de empleado: ");
        if (scanf("%d", &registros[i].cn.ne) != 1) exit(1);
        
        printf("Fecha DJM (dia mes año): ");
        registros[i].djm = capturarFecha();
    } else {
        // Si es 'A', guardamos el carácter en la unión
        registros[i].cn.condicion = c;
        // Inicializamos djm en 0 o valor nulo si es Activo
        registros[i].djm.dia = 0; 
    }

    printf("\n¡Registro completado con éxito!\n");
    
    return 0;
}
