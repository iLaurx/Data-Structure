// Busqueda lineal
//Librerias
#include <stdio.h>

//TODOFuncion busqueda lineal
/* Parametros
? char a[] -> lista de caracteres
? char c -> caracter a buscar    
? int n -> rango de busqueda
*/
int buslin(char a[], char c, int n){
    int i;
    // Loop de busqueda
    for(i=0; i<n; ++i)
        // Si encontramos c retornamos 1
        if(a[i] == c)
            return i;
    return -1;
}

int main () {
    char abc[26];
    char i;
    int index, j=0;
    //Generacion de Z a A
    for(i='Z'; i>='A'; --i){
        abc[j++] = i;
    }

    index = buslin(abc, 'F', 26);

    if (index != -1 ){
        printf("El indice del elemento %c es %d", abc[index], index);
    } else{ 
        printf("Valor no encontrado");
    }

    return 0;
}