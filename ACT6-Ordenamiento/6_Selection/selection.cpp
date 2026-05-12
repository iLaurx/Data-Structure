// Selection
#include <iostream>
/* Parametros
? T arr[] -> array a ordenar
? int n -> longitud del arreglo
*/
template <typename T> void seleccion(T arr[], int n)
{

    int minimo=0,i,j,k,aux;
    for(i=0 ; i<n-1 ; i++)
    {
        //Para empezar desde el elemento no ordenado
        minimo=i;
        for(j=i+1 ; j<n ; j++)
        {
            if(arr[minimo] > arr[j])
                //Actualiza el valor minimo actual
                minimo=j;
        }
        //swap minimo a i
        aux=arr[minimo]; 
        arr[minimo]=arr[i]; 
        arr[i]=aux; 
    }
}

int main(void)
{
    char abc[26];
    char i;
    int j=0;

    for(i='Z'; i>='A'; --i)
        abc[j++] = i;

    seleccion<char>(abc, 26);

    for(j=0; j<26; ++j)
        std::cout << abc[j] << " ";
    std::cout << "\b\n";

    return 0;
}