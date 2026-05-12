// Inserction
#include <iostream>

/* Parametros
? T arr[] -> array a ordenar
? int n -> longitud del arreglo
*/
template <typename T> void insercion(T arr[], int n)
{
    int i,j,k;
    T aux;
    for(i=1;i<n;i++)
    {
        //*aux = posicion actual del arreglo
        aux=arr[i];
        j=i;
        //* J>0 Para evitar intentar leer fuera de rango
        while(j > 0 && (arr[j-1] > aux))
        {
            //*swap de valor entre la posicion derecha a izq 
            arr[j]=arr[j-1];
            j=j-1;
        }
        arr[j]=aux;
    }
}

int main(void)
{
    char abc[26];
    char i;
    char j=0;

    for(i='Z'; i>='A'; --i)
        abc[j++] = i;

    insercion<char>(abc, 26);

    for(j=0; j<26; ++j)
        std::cout << abc[j] << " ";
    std::cout << "\b\n";

    return 0;
}