//Burbuja Sort
#include <iostream>

/* Parametros
? T arr[] -> array a ordenar
? int n -> longitud del arreglo
*/
template <typename T> void burbuja(T arr[], int n)
{
    int aux, i, j, k;
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-1; j++)
        {
            //*Si el elemento j es mayor al elemento a su der 
            if( arr[j]>arr[j+1] )
            {
                //*Guardamos el valor de j en aux
                aux=arr[j];
                //*Hacemos un swap en la posicion de valores
                arr[j]=arr[j+1];
                arr[j+1]=aux;
            }
        }
    }
}

int main(void)
{
    char abc[26];
    char i;
    int j=0;
    //Creacion del Abcedario invertido
    for(i='Z'; i>='A'; --i)
        abc[j++] = i;
    //Mostrar Abcedario
    for(j=0; j<26; ++j)
        std::cout << abc[j] << " ";
    std::cout << "\b\n";
    /* Argumentos
    ? <char> -> tipo char
    ? abc    -> lista a ordenar
    ? 26     -> longitud del arreglo
    */
    burbuja<char>(abc, 26);
    //Mostar la lista ordenada
    for(j=0; j<26; ++j)
        std::cout << abc[j] << " ";
    std::cout << "\b\n";

    return 0;
}