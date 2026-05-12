//HeapSort
#include <iostream>
/* Heap
* Ordered binary tree
* max heap: parent > child
* build max heap: creates max heap from unsorted array
* heapify: similar to build max heap, but assumes part of array is already sorted
*/

template <typename T> void heapify(T arr[], int n, int i)
{
    int max = i;        // Inicializa el nodo mas grande como la raiz (i)
    int izq = 2*i+1;    // Indice del hijo izq
    int der = 2*i+2;    // Indice del hijo der
    T aux;

    // Si el hijo izq existe y es mayor que la raiz acutal
    if(izq < n && arr[izq] > arr[max])
        max = izq;
    // Si el hijo der existe y es mayor que la raiz actual
    if(der < n && arr[der] > arr[max])
        max = der;
    // Si el maximo no es la raiz, significa que un hijo es mayor
    if(max!=i)
    {   
        //Swap para mover el valor mayor hacia arriba
        aux = arr[i];
        arr[i] = arr[max];
        arr[max] = aux;
        // Llamada recursiva para asegurar que el subarbol afectado sida siendo un Heap
        heapify(arr, n, max);
    }
}

template <typename T> void heapsort(T arr[], int n)
{
    int i;
    T aux;

    // Se construye el max-heap (reorganizar el arreglo)
    // Se empieza desde el ultimo nodo que tiene hijos (n/2 - 1) hasta la raiz
    for (i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    // Se extraen los elementos uno por uno del monticulo
    for(i=n-1; i>0; --i)
    {
        // El elemento mas grande siempre esta en arr[0]
        // Lo movemos al final del arreglo (su posicion ordenada definitiva)
        aux = arr[i];
        arr[i] = arr[0];
        arr[0] = aux;
        // Llamamos a heapify en el monton reducido para encontrar el nuevo macimo
        heapify(arr, i, 0);
    }
}

int main(void)
{
    char abc[26];
    char i;
    int j=0;

    for(i='Z'; i>='A'; --i)
        abc[j++] = i;

    heapsort<char>(abc, 26);

    for(j=0; j<26; ++j)
        std::cout << abc[j] << " ";
    std::cout << "\b\n";

    return 0;
}