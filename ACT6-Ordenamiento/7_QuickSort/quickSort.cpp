// QuickSort  
#include <iostream>
/* //TODO QuickSort  
*  Item to the left that is larger than pivot
*  Item to the right that is smaller than pivot
*/

/* Parametros
? T arr[] -> arreglo a ordenar
? int inf -> limite inferior del arreglo
? int sup -> limite superior del arreglo
*/
template <typename T> void qs(T arr[], int inf, int sup)
{
    int izq, k, der;
    T med, x;
    izq=inf;
    der=sup;
    //Obtener mitad/pivote
    med=arr[(izq+der)/2];
    do
    {
        //* Dezplaza el indice izq mientras los elementos sean menores al pivote
        while (arr[izq] < med && izq < sup )
            ++izq;
        //* Dezplaza el indice der mientras los elementos sean mayores al pivote
        while (med < arr[der] && der > inf )
            der--;
        // Si los índices no se han cruzado, intercambia los elementos fuera de lugar
        if (izq <= der)
        {
            x = arr[izq];
            arr[izq]=arr[der];
            arr[der]=x;
            //Avanza los indices para continuar buscando
            izq++; der--;
        }
    //* Sub-lista izquierda: Si quedan elementos a la izquierda del cruce, ordena esa parte
    }while (izq <= der);
    if (inf < der)
        qs(arr,inf,der);
    //* Sub-lista derecha: Si quedan elementos a la derecha del cruce, ordena esa parte
    if (izq < sup)
        qs(arr,izq,sup);
}

/* Parametros
? T arr[] -> array a ordenar
? int n -> longitud del arreglo
*/
template <typename T> void quicksort(T arr[], int n)
{
    qs(arr, 0, n-1);
}

int main(void)
{
    char abc[26];
    char i;
    int j=0;

    for(i='Z'; i>='A'; --i)
        abc[j++] = i;

    quicksort<char>(abc, 26);

    for(j=0; j<26; ++j)
        std::cout << abc[j] << " ";
    std::cout << "\b\n";

    return 0;
}