// Busquedda Binaria
//librerias
#include <stdio.h>

//TODO Funcion Busqueda Binaria
/* Parametros
? char a[] -> lista de caracteres
? char c -> caracter a encontrar 
? int n -> rango de busqueda
*/
int busbin(char a[], char c, int n){
    int i, izq = 0, der = n;
    int aux=-1;

    i = n/2; //Divisor de la lista

    while(1){
        printf("%i ", i); // debug muestra el inidce qeu estamos revisando

        if(i==aux)
            return -1;
        // Si encontramos la letra c en la posicion i retornamos 1
        if(a[i] == c)
            return i;
        // Guardamos el indice actual para compararlo en la siguiente ronda
        aux = i;
        // Si c es menor que el indice 
        if(c<a[i]){
            // nos movemos hacia el lado izq
            der = i;
            i = (izq+i)/2;  // dividimos
        } else{
            // nos movemos hacia el lado der
            izq = i;
            i = (der+i)/2; // dividimos
        }
    }
    return -1;
}

int main(){

    char abc[26];
    char i;
    int index, j=0;
    char funciona = 1; //1 lista en orden, 0 en orden inverso, con el 0 falla la busqueda
    int n = 25;

    if(funciona)
        for(i='A'; i<='Z'; ++i)
            if(i=='E')
                continue;
            else
                abc[j++] = i;
    else
        for(i='Z'; i>='A'; --i)
            if(i=='E')
                continue;
            else
                abc[j++] = i;
    
    for(i=0; i<n; ++i)
        printf("%c ", abc[i]);
    printf("\n");

    for(i=0; i<n; ++i){
        index = busbin(abc, abc[i], n);
        if(index >= 0)
            printf("\nEl indice del elemento %c es %d\n ", abc[index], index);
        else
            printf("\nEl elemento %c no existe\n ", abc[i]);
    }

    i = '+';
    index  = busbin(abc, i, n);
    if(index >= 0)
      printf("\nEl indice del elemento %c es %d\n ==", i, index);
    else
      printf("\nEl elemento %c no existe\n", i);

    i = 'Z'+1;
    index  = busbin(abc, i, n);
    if(index >= 0)
      printf("\nEl indice del elemento %c es %d\n", i, index);
    else
      printf("\nEl elemento %c no existe\n ", i);

    i = 'E';
    index  = busbin(abc, i, n);
    if(index >= 0)
      printf("\nEl indice del elemento %c es %d\n", i, index);
    else
      printf("\nEl elemento %c no existe\n", i);

    return 0;
}
