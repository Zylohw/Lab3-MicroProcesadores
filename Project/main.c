#include "RTE_Components.h"
#include <stdio.h>
#include <string.h>
#include CMSIS_device_header
#include "header.h"

static const char numbers[] = "36,60,48";    
int main() {
    
    char comb[500];
   
    
    // prueba de la función myGCD
    int result = myGCD(numbers);
    printf("tu resultado es: %d \n",result);

    // prueba de la función myCombinations
    myCombinations(2, "A = {rojo, verde, azul}", comb);
    printf("prueba myCombinations: %s\n",comb);

    while(1);
     
}

int myGCD(const char *set) {
    int num = 0;
    int result = 0;

    while (*set != '\0') {
        // si el caracter al que se esta apuntando es un caracter vacio entonces avanza
        while (*set == ' ')
            set++;

        num = 0;

        while (*set >= '0' && *set <= '9') {
            num = num * 10 + (*set - '0'); // opera con el caracter sobre el cual el puntero esta apuntando 
            set++;
        }

        if (result == 0) {
            // si en caso el resultado es igual a 0 entonces eso sera el MCD
            result = num;
        } else {
            // de lo contrario se hara el procedimiento para el MCD empleando el algoritmo de Euclides 
            int a = result;
            int b = num;

            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }

            result = a;
        }
        // si el caracter actaul es igual a una "," entonces el set cambia su referencia para leer el otro digito la comas "," son los separadores o el token que se debe consultar
        if (*set == ',')
            set++;
    }

    return result;
}

void myCombinations(int n, const char *set, char *comb) {
    char elements[5][20];
    int count = 0;
    int i = 0, j = 0, k = 0;
    int first = 1;


    // avanza hasta encontrar el caracter '{'
    while (*set && *set != '{')
        set++;

    // si encaso la encontramos entonces avanzamos al siguiente elemento que es el numero
    if (*set == '{')
        set++;
    // avanza hasta encontrar el caracter '{'
    while (*set && *set != '}') {
        // si se encuentra un espacio o una coma significa que encontramos el elemento
        if (*set == ' ' || *set == ',') {
            // permite verifica si hay caracteres almacenados
            if (j > 0) {
                // agregara un caracter nulo para terminar la cadena del elementos 
                elements[count][j] = '\0';
                // aumenta la cantidad de elementos encontrados
                count++;
                // aumenta el indicie para al siguiente analisis|
                j = 0;
            }
            // seguira avanzando
            set++;
        } else {
            // en caso contrario no encuentre un espacio o una coma entonces agregara el elemento encontado
            elements[count][j++] = *set++;
        }
    }

    // si quedo un elemento pendiente antes del caracter '{'
    if (j > 0) {
        elements[count][j] = '\0';
        count++;
    }

    // se incializa el retorno como una cadena vacia
    comb[0] = '\0';

    // si n es igual entonces 
    if (n == 1) {

        for (i = 0; i < count; i++) {
            // si ya exitse una combinación 
            if (!first)
                // agrega una coma y un espacio antes del elemento siguiente 
                sprintf(comb + strlen(comb), ", ");

            sprintf(comb + strlen(comb), "{%s}", elements[i]);
            first = 0;
        }
    }

    // en caso de que n sea igual a 2 entonces cambia por que ahora generamos combinaciones de dos elementos
    if (n == 2) {
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                if (!first)
                    sprintf(comb + strlen(comb), ", ");

                sprintf(comb + strlen(comb),
                        "{%s, %s}",
                        elements[i],
                        elements[j]);

                first = 0;
            }
        }
    }

    // si n es igual a 3 entonces seran combinaciones de 3 elementos
    if (n == 3) {
        for (i = 0; i < count - 2; i++) {
            for (j = i + 1; j < count - 1; j++) {
                for (k = j + 1; k < count; k++) {
                    if (!first)
                        sprintf(comb + strlen(comb), ", ");

                    sprintf(comb + strlen(comb),
                            "{%s, %s, %s}",
                            elements[i],
                            elements[j],
                            elements[k]);

                    first = 0;
                }
            }
        }
    }
}

