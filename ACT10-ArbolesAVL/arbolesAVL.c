//TODO ARBOLES AUTOBALANCEADOS AVL

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int valor;
    struct Nodo *izq;
    struct Nodo *der;
    unsigned int alt; //altura para el balance del arbol AVL
} Nodo;

unsigned int alturaNodo(Nodo *nodo) //nueva funcion para la altura
{
    if(nodo == NULL)
        return 0;
    return nodo->alt;
}

unsigned int actualizarAltura(Nodo *nodo)
{
    if (nodo->izq == NULL && nodo->der == NULL)
        return 0;
    unsigned int i = alturaNodo(nodo->izq);
    unsigned int d = alturaNodo(nodo->der);

    return i > d ? i + 1 : d + 1 ; 
}

int balance(Nodo *nodo) //nueva funcion para encontrar el balance del arbol
{
    unsigned int i;
    unsigned int d;

    if (nodo->izq == NULL)
        i = 0;
    else
        i = 1 + alturaNodo(nodo->izq);

    if (nodo->der == NULL)
        d = 0;
    else
        d = 1 + alturaNodo(nodo->der);

    return i - d;
}

Nodo* rotarIzq(Nodo *nodo)
{
    //nodos auxiliares
    Nodo *n = nodo->der; //nodo a girar
    Nodo *aux = n->izq; //nodo auxiliar

    //realizar giro
    n->izq = nodo;
    nodo->der = aux;

    //actualizar alturas
    nodo->alt = actualizarAltura(nodo);
    n->alt = actualizarAltura(n);
    return n; //nueva raiz
}

Nodo* rotarDer(Nodo *nodo) //misma logica que rotar izquierda
{
    //nodos auxiliares
    Nodo *n = nodo->izq; //nodo a girar
    Nodo *aux = n->der; //nodo auxiliar

    //realizar giro
    n->der = nodo;
    nodo->izq = aux;

    //actualizar alturas (misma funcion)
    nodo->alt = actualizarAltura(nodo);
    n->alt = actualizarAltura(n);
    return n; //nueva raiz
}

void insertar(Nodo** nodo, int dato)
{
    if (*nodo == NULL)
    {
        *nodo = malloc(sizeof(Nodo));
        (*nodo)->valor = dato;
        (*nodo)->izq = NULL;
        (*nodo)->der = NULL;
        (*nodo)->alt = 0; //inicializa la altura en 0
        return;
    }
    
    if (dato < (*nodo)->valor)
    {
        insertar(&((*nodo)->izq), dato);
    }
    else if (dato > (*nodo)->valor)
    {
        insertar(&((*nodo)->der), dato);
    }
    else 
    {
        return; // Valores duplicados no permitidos
    }

    (*nodo)->alt = actualizarAltura(*nodo); //actualiza altura

    int b = balance(*nodo); //revisar balance

    // rotacion simple a la izquierda (RR)
    if (b < -1 && dato > (*nodo)->der->valor) 
    {
        *nodo = rotarIzq(*nodo);
    }
    // rotacion simple a la derecha (LL)
    else if (b > 1 && dato < (*nodo)->izq->valor) 
    {
        *nodo = rotarDer(*nodo);
    }
    // rotacion doble derecha izquierda (RL)
    else if (b < -1 && dato < (*nodo)->der->valor) 
    {
        (*nodo)->der = rotarDer((*nodo)->der);
        *nodo = rotarIzq(*nodo);
    }
    // rotacion doble izquierda derecha (LR)
    else if (b > 1 && dato > (*nodo)->izq->valor) 
    {
        (*nodo)->izq = rotarIzq((*nodo)->izq);
        *nodo = rotarDer(*nodo);
    }
} 

void inorder(Nodo *nodo)
{
    if (nodo)
    {
        inorder(nodo->izq);
        printf("%i\n", nodo->valor);
        inorder(nodo->der);
    }
}

void preorder(Nodo *nodo)
{
    if (nodo)
    {
        printf("%i\n", nodo->valor);
        preorder(nodo->izq);
        preorder(nodo->der);
    }
}

void postorder(Nodo *nodo)
{
    if (nodo)
    {
        postorder(nodo->izq);
        postorder(nodo->der);
        printf("%i\n", nodo->valor);
    }
}

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

void borrar(Nodo **raiz)
{
    if (*raiz == NULL)
        return;
    postorder_free(*raiz);
    *raiz = NULL;
}

void imprimir(Nodo *raiz)
{
    if (raiz)
    {
        inorder(raiz);
        printf("\n");
    }
    else
        printf("\nVacio\n\n");
}

void preorder_estructura(Nodo *nodo, int tab)
{
    int i;
    if (nodo)
    {
        for (i = 0; i < tab; ++i)
            printf("->");
        printf("%i(%i, %i)\n", nodo->valor, nodo->alt, balance(nodo));
        preorder_estructura(nodo->izq, tab + 1);
        preorder_estructura(nodo->der, tab + 1);
    }
}

void imprimir_estructura(Nodo *raiz)
{
    if (raiz == NULL)
        printf("\nVacio\n");
    else
    {
        preorder_estructura(raiz, 0);
    }
}

Nodo* buscar(Nodo *nodo, int dato)
{
    if (nodo == NULL)
        return NULL;
    if (dato == nodo->valor)
        return nodo;
    if (dato < nodo->valor)
        return buscar(nodo->izq, dato);
    else
        return buscar(nodo->der, dato);
}

int menor(Nodo *nodo)
{
    if (nodo->izq)
        return menor(nodo->izq);
    return nodo->valor;
}

//funcion eliminar corregida para balanceo AVL
Nodo* eliminar(Nodo *nodo, int dato)
{
    Nodo *aux;
    int m;

    if (nodo == NULL)
        return NULL;

    if (dato < nodo->valor)
    {
        nodo->izq = eliminar(nodo->izq, dato);
    }
    else if (dato > nodo->valor)
    {
        nodo->der = eliminar(nodo->der, dato);
    }
    else
    {
        //NODO HOJA O CON UN SOLO HIJO
        if (nodo->izq == NULL || nodo->der == NULL)
        {
            aux = nodo->izq ? nodo->izq : nodo->der;

            if (aux == NULL) // Nodo hoja
            {
                aux = nodo;
                nodo = NULL;
            }
            else // Un solo hijo
            {
                *nodo = *aux; // Copia el contenido del hijo
            }
            free(aux);
        }
        else
        {
            //TIENE DOS HIJOS
            m = menor(nodo->der);
            nodo->valor = m;
            nodo->der = eliminar(nodo->der, m);
        }
    }

    if (nodo == NULL)
        return NULL;

    // ACTUALIZAR ALTURA Y BALANCEAR
    nodo->alt = actualizarAltura(nodo);
    int b = balance(nodo);

    // Casos de rotación tras eliminación
    if (b > 1 && balance(nodo->izq) >= 0)
        return rotarDer(nodo);

    if (b > 1 && balance(nodo->izq) < 0)
    {
        nodo->izq = rotarIzq(nodo->izq);
        return rotarDer(nodo);
    }

    if (b < -1 && balance(nodo->der) <= 0)
        return rotarIzq(nodo);

    if (b < -1 && balance(nodo->der) > 0)
    {
        nodo->der = rotarDer(nodo->der);
        return rotarIzq(nodo);
    }

    return nodo;
}

int nivel(Nodo *nodo, int dato)
{
    int n;
    if(nodo == NULL) return -1;
    if(nodo->valor == dato)
        return 1;

    if(dato < nodo->valor)
    {
        n = nivel(nodo->izq, dato);
        return n > 0 ? 1 + n : -1;
    }
    else
    {
        n = nivel(nodo->der, dato);
        return n > 0 ? 1 + n : -1;
    }
}

int profundidad(Nodo *nodo, int dato)
{
    int n = nivel(nodo, dato);
    return n > 0 ? n - 1 : -1;
}

int altura(Nodo *nodo, int dato)
{
    Nodo* objetivo = buscar(nodo, dato);
    if (objetivo == NULL)
        return -1;
    return objetivo->alt;
}

int main(void)
{
    Nodo *raiz = NULL;

    printf("                      ARBOLES BINARIOS AUTOBALANCEADOS            \n");

    insertar(&raiz, 1);
    insertar(&raiz, 2);
    insertar(&raiz, 3);
    
    printf("\nArbol\n");
    imprimir(raiz);
    
    printf("\nEstructura del arbol nodo (altura, balance)\n");
    imprimir_estructura(raiz);
    
    return 0;
}