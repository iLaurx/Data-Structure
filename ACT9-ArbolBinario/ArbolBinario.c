#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int valor;
    struct Nodo *izq;
    struct Nodo *der;

} Nodo;

/* Parametros
? Nodo** nodo: Para poder modificar directamnte la 
? direccion que apunta al puntero original
? int dato: Dato a insertar
*/

void insertar(Nodo** nodo, int dato)
{
    /* Caso base
    Si la posicion esta vacia reserva memoria, 
    asigna el valor y pone sus hijos en NULL.
    */
    if (*nodo == NULL) 
    {
        *nodo = malloc(sizeof(Nodo));
        (*nodo)->valor = dato;
        (*nodo)->izq = NULL;
        (*nodo)->der = NULL;
    }
    /* Caso recursivo
    Si no esta vacia, compara el dato. Si es menor
    se mueve recursivamente a la izq si es >= a der.
    */
    else
    {
        if (dato < (*nodo)->valor)
        {
            insertar (&((*nodo)->izq),dato);
        }
        else
        {
            insertar (&((*nodo)->der),dato);
        }
    }
}


/* Parametros
? Nodo *nodo: Nodo actual
* (Izq - Raiz - Derecha)
*/
void inorder(Nodo *nodo)
{
    /*
    Imprime los numeros en orden ascendente
    Recorre primero el subarbol izq, luego procesa
    el nodo actual y finalmente el derecho. 
    */
    if (nodo)
    {
        inorder(nodo->izq);
        printf("%i\n", nodo->valor);
        inorder(nodo->der);
    }

}

/* Parametros
? Nodo *nodo: Nodo actual
* (Raiz - Izq - Derecha)
*/
void preorder(Nodo *nodo)
{
    /*
    Procesa primero la raiz, luego el sub izq y despues
    despues el derecho. Uso para copiar o clonar la 
    estructura del arbol.
    */
    if (nodo)
    {
        printf("%i\n", nodo->valor);
        preorder(nodo->izq);
        preorder(nodo->der);
    }

}

/* Parametros
? Nodo *nodo: Nodo actual
* (Izq - Derecha - Raiz)
*/
void postorder(Nodo *nodo)
{
    /*
    Recorre los sub izq y derecho antes de procesar
    el nodo actual. Es el orden ideal para destruir un arbol de abajo hacia arriba
    */
    if (nodo)
    {
        postorder(nodo->izq);
        postorder(nodo->der);
        printf("%i\n", nodo->valor);
    }

}

/* Parametros
? Nodo *nodo: Nodo actual
* Libera memoria con postorder
asegura que no se pierdan los punteros de los hijos antes de borrar al padre
*/
void postorder_free(Nodo *nodo)
{
    if (nodo)
    {
        postorder_free(nodo->izq);
        postorder_free(nodo->der);
        printf("%i\n", nodo->valor);
        free(nodo);
    }

}

/* Parametros
? Nodo **raiz: Nodo raiz
*/
void borrar(Nodo **raiz)
{
    /*
    Llama a la función de liberación y luego pone la raíz
    original en NULL para evitar punteros colgados.
    */
    if (*raiz == NULL) 
    {
        return;
        postorder_free(*raiz);
        *raiz= NULL;
    }
}

void imprimir (Nodo *raiz)
{
    if (raiz)
    {
        inorder(raiz);
        printf("\n");
    }
    else
        printf("\nVacio\n\n");
}

/* Parametros
? Nodo *nodo: Nodo actual
? tab: indica la profundiad del nodo 
*/
void preorder_estructura(Nodo *nodo, int tab)
{
    /*
    Muestra el arbol de forma visual con flechas tab aumenta
    en cada llamada recursiva para indicar la profundidad
    */
    int i;
    if (nodo)
    {
        for (i=0; i<tab; ++i)
            printf("->");
        printf("%i\n", nodo->valor);
        preorder_estructura(nodo->izq, tab+1);
        preorder_estructura(nodo->der, tab+1);
    }

}

void imprimir_estructura (Nodo *raiz)
{
    if (raiz == NULL)
        printf("\nVacio\n");
    else
    {
        preorder_estructura(raiz,0);
    }
}

/* Parametros
? Nodo *nodo: Nodo actual
? int dato: valor a buscar
*/
Nodo* buscar(Nodo *nodo, int dato)
{
    if (nodo==NULL)
        return NULL;
    if ( dato == nodo->valor)
        return nodo;
    if (dato < nodo->valor)
        return buscar( nodo->izq, dato);
    else
        return buscar(nodo->der,dato);

}

/* Parametros
? Nodo *nodo: Nodo actual
* retorna el valor minimo
*/
int menor (Nodo *nodo)
{
    if (nodo->izq )
        return menor(nodo->izq);
    return nodo->valor;
}

/* Parametros
? Nodo *nodo: Nodo actual
? int dato: dato a eliminar
*/
Nodo *eliminar (Nodo *nodo, int dato)
{
    Nodo *aux, *auxi;
    int m;
    if (nodo == NULL)
        return NULL;
    if (dato == nodo->valor)
    {
        // *Nodo Hoja (sin hijos)
        /*
        ? CASO 1
        Se libera el nodo y se retorna NULL al padre. 
        */
        if (nodo->izq == NULL && nodo->der == NULL)
        {
            free(nodo);
            return NULL;
        }

        //*Si tiene un solo hijo
        /*
        ? CASO 2
        Se guarda el puente al hijo único (aux), se libera el 
        nodo actual y se retorna ese hijo para que el padre se 
        conecte con él. 
        */
        // *Caso izq
        if(nodo->izq && nodo->der == NULL)
        {
            aux = nodo->izq;
            free(nodo);
            return aux;
        }
        // *Caso der
        if(nodo->izq ==NULL&& nodo->der )
        {
            aux = nodo->der;
            free(nodo);
            return aux;
        }

        //* Si tiene ambos hijos
        /*
        ? CASO 3
        Se busca el menor elemento del subárbol derecho (m), 
        se copia su valor en el nodo actual (reemplazándolo) y 
        luego se elimina recursivamente ese nodo menor duplicado 
        en el subárbol derecho. 
        */
        m = menor(nodo->der);
        nodo->valor = m;
        nodo->der = eliminar(nodo->der, m);

    }

    if (dato < nodo->valor)
    {
        nodo->izq = eliminar(nodo->izq, dato);
        return nodo;
    }
    else { 
        nodo->der = eliminar(nodo->der, dato);
        return nodo;
    }
}

/* Parametros
? Nodo *nodo: Nodo actual
? int dato: dato para encontar el nivel 
* Cuenta cuántos nodos hay desde la raíz hasta el elemento
*/
int nivel(Nodo *nodo, int dato)
{

    int n;
    if (nodo == NULL) // Validacion si el dato no existe
        return -1;

    if(nodo->valor == dato)
        return 1;
    if(dato < nodo->valor)
    {
        n= nivel(nodo->izq, dato);
        return n > 0 ? 1 + n : -1;
    }
    else
        return nivel(nodo->der, dato);
        return n > 0 ? 1 + n : -1;
}


/* Parametros
? Nodo *nodo: Nodo actual
? int dato: dato para encontar el nivel de profundidad
* Es el nivel del nodo menos 1 (la raíz está a profundidad 0).
*/
int profundidad(Nodo *nodo, int dato)
{
    int n = nivel(nodo, dato);
    return n > 0 ? n - 1 : -1;
}

/* Parametros
? Nodo *nodo: Nodo actual
? int dato: dato para encontar la altura
* Mide la distancia más larga desde el nodo hasta una hoja.
*/
int altura (Nodo *nodo, int dato)
{
    // Caso base: Nodo vacio
    if (nodo == NULL)
        return -1;

    // Si se encuentra el nodo con el dato buscado
    if (nodo->valor == dato)
    {
        // Medimos la altura real de sus subárboles (pasándole sus propios valores para que calculen a ciegas)
        int alt_izq = nodo->izq ? altura(nodo->izq, nodo->izq->valor) : -1;
        int alt_der = nodo->der ? altura(nodo->der, nodo->der->valor) : -1;
        
        return (alt_izq > alt_der) ? (alt_izq + 1) : (alt_der + 1);
    }

    // Si aún no encontramos el dato, seguimos buscando en el árbol
    if (dato < nodo->valor)
    {
        return altura(nodo->izq, dato);
    }
    else
    {
        return altura(nodo->der, dato);
    }
}

int main (void)
{
    Nodo *raiz=NULL;
    Nodo *elem;
    printf("                      ARBOLES BINARIOS            ");

    printf("\n\n---------Arbol vacio:---------\n");
    imprimir(raiz);
    insertar(&raiz, 10);
    insertar(&raiz, 6);
    insertar(&raiz, 7);
    insertar(&raiz, 4);
    insertar(&raiz, 5);
    insertar(&raiz,3);
    insertar(&raiz,15);
    insertar(&raiz,13);
    insertar(&raiz,14);
    printf("----------Arbol impreso inorder: ---------\n");
    inorder(raiz);
    printf("----------Arbol impreso preorder: ---------\n");
    preorder(raiz);
     printf("----------Arbol impreso postorder: ---------\n");
    postorder(raiz);
    printf("\nBorrar arbol: \n");
    borrar(&raiz);
    imprimir(raiz);
    printf("\nEstructura arbol: \n");
    imprimir_estructura(raiz);
    printf("\nPrueba de serializacion: \n");
    int datos[] = {10,6,4,3,5,7,15,13,14};
    int i;

    for (i=0; i<9; ++i)
        insertar(&raiz, datos[i]);
    imprimir_estructura(raiz);
    printf("\nBuscar elemento: \n");
    elem = buscar(raiz, 8);
    printf("Direccion de dato Inexistente: %p\n", elem);
    elem = buscar(raiz, 7);
    printf("Direccion de 7 (valor existente): %p\n", elem);
    printf("%i\n", elem->valor);
    printf("\nFuncion eliminar dato: \n");
    imprimir_estructura(raiz);
    printf("\nborrar 8 (no existe)\n");
    raiz = eliminar(raiz, 8);
    imprimir_estructura(raiz);
    printf("\nBorrar 3: \n");
    raiz = eliminar(raiz, 3);
    imprimir_estructura(raiz);
    printf("\n");
    printf("\nBorrar 15 (hijo derecho): \n");
    raiz = eliminar(raiz, 15);
    imprimir_estructura(raiz);
    printf("\n");
    printf("\nBorrar 13 (hijo izquierdo): \n");
    raiz = eliminar(raiz, 13);
    imprimir_estructura(raiz);
    printf("\n");
    printf("\nBorrar 10 raiz (2 hijos): \n");
    raiz = eliminar(raiz, 10);
    imprimir_estructura(raiz);
    printf("\nNivel de %d: %d\n", 10, nivel(raiz, 10));

    return 0;
}
