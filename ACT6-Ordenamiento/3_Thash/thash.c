//TODO Tabla de HASH
// Librerias
#include <stdio.h>

typedef struct Elem
 {
   char exists; // ? existencia/uso
   int value;   // ? valor real
 }Elem;

/* Parametros
? int elem -> elemento a guardar
? int n -> numero de espacios disponibles
*/
int fhash(int elem, int n)
{
    int hash;
    //TODO se crea el hash
    // ? determina la posicion -> index = hash % n 
    hash = ( (elem*'h' + 'a')*'s' + 'h' ) % n;

    return hash;
}

/* Parametros
? int elem -> elemento a guardar
? int n -> numero de espacios disponibles
? int Elem tabla[] -> tabla de trabajo
*/

void insertar(int elem, int n, Elem tabla[])
{
    int hash = fhash(elem, n);
    //* Logica de Colisiones
    // Si ya existe un elemento en donde se iba a guardar
    while(tabla[hash].exists)
        // se añade +1 al hash
        ++hash;
    // se cambia a espacio en uso/existente
    tabla[hash].exists = 1;
    // se guarda el valor
    tabla[hash].value = elem;
}

/* Parametros
? int elem -> elemento a buscar
? int n -> numero de espacios disponibles
? int Elem tabla[] -> tabla de trabajo

*/

int buscar(int elem, int n, Elem tabla[])
{
    int hash;

    hash = fhash(elem, n);
    while(tabla[hash].exists)
    {
        // determina si tiene el mismo valor
        if(tabla[hash].value == elem)
          return hash;
          //* Aumenta hasta encontrarlo por la Logica de Colisones
        ++hash;
    }
    return -1;
}

int main() {
    int i, h;
    Elem tabla[1000];
    // Loop para inicializar todo exist en 0
    for(i=0; i<1000; ++i)
        tabla[i].exists = 0;
    
    // !  Forma manual de ingresar datos
    /*
    // Loop 0 - 9
    for(i=0; i<10; ++i)
    {
        // Introduce del 0 al 9
        h = fhash(i, 1000);
        // Ajusta la existencia del resultado del hash en la tabla
        tabla[h].exists = 1;
        // Introduce el valor del numero (i) en el el resultado del hash
        tabla[h].value = i;
    }
    */

    for(i=0; i<10; ++i)
    {
        insertar(i, 1000, tabla);
    }

    for(i=0; i<1500; ++i)
    {
        h = buscar(i, 1000, tabla);
        if(h>=0)
            printf("El elemento %d esta en la posicion %d\n", i, h);
        //else
            //printf("El elemento %d no esta en la tabla\n", i);
    }

}