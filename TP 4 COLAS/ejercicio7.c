
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "colas.h"

// funcion que elimina los espacios de una cadena de char ingresada
void strtrim(char *cadena) {
    char *comienzoDeCadena = cadena;
    char *finalDeCadena = cadena + strlen(cadena) - 1;
    while (isspace(*comienzoDeCadena)) {
        comienzoDeCadena++;
    }
    while (isspace(*finalDeCadena) && finalDeCadena >= comienzoDeCadena) {
        finalDeCadena--;
    }
    *(finalDeCadena + 1) = '\0';
    memmove(cadena, comienzoDeCadena,   finalDeCadena - comienzoDeCadena + 2);
}

// funcion para leer un entero por teclado (validacion)
int leer_entero() {
    char entrada[100];
    long numero;
    char *finptr;
    int valido = 0;

    while (!valido) {
        printf("Ingrese un numero entero: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        if (entrada[0] == '\0') {
            printf("Entrada invalida. Intentelo de nuevo.\n");
            continue;
        }
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero > 100000 || numero < -100000) {
            printf("Entrada invalida (rango entero de 1 a 100k). Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

// funcion para llenar una cola al azar usando rango de randoms
Cola rellenar_cola_por_teclado() {
    Cola cola = c_crear();
    int longitudCola = 0;
    printf("Ingrese la longitud de la cola (entre 1 a 100.000): \n");
    printf("Tenga en cuenta que si se supera el tamanio maximo de la cola, solo se cargaran hasta que se llene la misma.\n");
    longitudCola = leer_entero();
    while (longitudCola > 100000 || longitudCola <= 0) {
        printf("Entrada invalida. Fuera del rango disponible para la cola. Reingrese el tamanio. ");
        longitudCola = leer_entero();
    }
    int i = 0;
    int pos = 0;
    while (i < longitudCola) {
        if (c_es_llena(cola)) {
            printf("La cola ha alcanzado su capacidad maxima y no puede recibir mas elementos.\n");
            break;
        }
        int ingreso = 0;
        printf("Ingrese el cliente (cant. de minutos) #%d. ", i + 1);
        ingreso = leer_entero();
        while (ingreso <= 0) {
            printf("Entrada invalida, reingrese la cantidad de minutos. ");
            ingreso = leer_entero();
        }
        TipoElemento elemento = te_crear(ingreso);
        char *str_valor = (char*) malloc(sizeof(char) * 10);
        pos = i + 1;
        sprintf(str_valor, "%i", pos);
        elemento->valor = str_valor;
        c_encolar(cola, elemento);
        i++;
    }
    return cola;
}

// funcion que pide una cola y la copia sin alterar su version original
Cola copiarCola(Cola colaOriginal) { // C.A.: O(n)
    Cola colaAux = c_crear();
    Cola colaCopia = c_crear();
    TipoElemento elementoAux;
    while (!c_es_vacia(colaOriginal)) {
        elementoAux = c_desencolar(colaOriginal);
        c_encolar(colaAux, elementoAux);
    }
    while (!c_es_vacia(colaAux)) {
        elementoAux = c_desencolar(colaAux);
        c_encolar(colaCopia, elementoAux);
        c_encolar(colaOriginal, elementoAux);
    }
    return colaCopia;
}

// funcion recursiva que atiende individualmente una cola (cuando Q es sobrante, debe usarse en esa misma cola)
void atenderCola (Cola cola, int Q, int numCola, Cola colaResultado) {
    int diferencia = 0;
    int valor = 0;
    TipoElemento clienteAtendido;
    if (Q > 0) {
        if (!c_es_vacia(cola)) {
            clienteAtendido = c_recuperar(cola); // no se elimina el elemento de la cola, solo se lee
            diferencia = clienteAtendido->clave - Q;
            // CASOS POSIBLES
            if (diferencia < 0) { // el cliente termina de ser atendido con tiempo sobrante
                // entonces, se desencola el cliente y se printea su salida
                c_desencolar(cola);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, numCola);
                if (!c_encolar(colaResultado, te_crear_con_valor(numCola, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                } else {
                    diferencia = abs(diferencia);
                    atenderCola(cola, diferencia, numCola, colaResultado); // caso recursivo
                }
            } else if (diferencia == 0) { // el cliente termina de ser atendido con tiempo justo
                c_desencolar(cola);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, numCola);
                if (!c_encolar(colaResultado, te_crear_con_valor(numCola, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                }
            } else { // sino, el cliente debe volver a ser atendido mas tarde, y se pasa a otra cola
                clienteAtendido->clave -= Q; // se resta el tiempo Q al cliente
            }
        }
    }
}

// funcion que atiende las tres colas ingresadas a partir de un numero Q que representa el tiempo en cada cola
Cola c_ej7_atenderclientes(Cola c1, Cola c2, Cola c3, int tiempoatencion) {
    Cola cResultado = c_crear();
    TipoElemento clienteAtendido;
    int diferencia = 0;
    int valor = 0;
    while (!c_es_vacia(c1) || !c_es_vacia(c2) || !c_es_vacia(c3)) {
        // COLA 1
        if (!c_es_vacia(c1)) {
            clienteAtendido = c_recuperar(c1); // no se elimina el elemento de la cola, solo se lee
            diferencia = clienteAtendido->clave - tiempoatencion;
            // CASOS POSIBLES
            if (diferencia < 0) { // el cliente termina de ser atendido con tiempo sobrante
                // entonces, se desencola el cliente y se printea su salida
                c_desencolar(c1);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, 1);
                if (!c_encolar(cResultado, te_crear_con_valor(1, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                    break;
                }
                diferencia = abs(diferencia);
                atenderCola(c1, diferencia, 1, cResultado);
            } else if (diferencia == 0) { // el cliente termina de ser atendido con tiempo justo
                c_desencolar(c1);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, 1);
                if (!c_encolar(cResultado, te_crear_con_valor(1, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                    break;
                }
            } else { // sino, el cliente debe volver a ser atendido mas tarde, y se pasa a otra cola
                clienteAtendido->clave -= tiempoatencion; // se resta el tiempo Q al cliente
            }
        }
        // COLA 2
        if (!c_es_vacia(c2)) {
            clienteAtendido = c_recuperar(c2); // no se elimina el elemento de la cola, solo se lee
            diferencia = clienteAtendido->clave - tiempoatencion;
            // CASOS POSIBLES
            if (diferencia < 0) { // el cliente termina de ser atendido con tiempo sobrante
                // entonces, se desencola el cliente y se printea su salida
                c_desencolar(c2);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, 2);
                if (!c_encolar(cResultado, te_crear_con_valor(2, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                    break;
                }
                diferencia = abs(diferencia);
                atenderCola(c2, diferencia, 2, cResultado);
            } else if (diferencia == 0) { // el cliente termina de ser atendido con tiempo justo
                c_desencolar(c2);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, 2);
                if (!c_encolar(cResultado, te_crear_con_valor(2, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                    break;
                }
            } else { // sino, el cliente debe volver a ser atendido mas tarde, y se pasa a otra cola
                clienteAtendido->clave -= tiempoatencion; // se resta el tiempo Q al cliente
            }
        }
        // COLA 3
        if (!c_es_vacia(c3)) {
            clienteAtendido = c_recuperar(c3); // no se elimina el elemento de la cola, solo se lee
            diferencia = clienteAtendido->clave - tiempoatencion;
            // CASOS POSIBLES
            if (diferencia < 0) { // el cliente termina de ser atendido con tiempo sobrante
                // entonces, se desencola el cliente y se printea su salida
                c_desencolar(c3);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, 3);
                if (!c_encolar(cResultado, te_crear_con_valor(3, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                    break;
                }
                diferencia = abs(diferencia);
                atenderCola(c3, diferencia, 3, cResultado);
            } else if (diferencia == 0) { // el cliente termina de ser atendido con tiempo justo
                c_desencolar(c3);
                char *str_valor = (char*) malloc(sizeof(char) * 50);
                sprintf(str_valor, "Cliente %s Cola %i", (char*)clienteAtendido->valor, 3);
                if (!c_encolar(cResultado, te_crear_con_valor(3, str_valor))) {
                    printf("Ya no entran mas datos en la cola resultante, por lo que el resultado quedara incompleto.\n");
                    break;
                }
            } else { // sino, el cliente debe volver a ser atendido mas tarde, y se pasa a otra cola
                clienteAtendido->clave -= tiempoatencion; // se resta el tiempo Q al cliente
            }
        }
    }
    return cResultado;
}

void mostrarClientes(Cola cola) {
    TipoElemento elemento;
    while (!c_es_vacia(cola)) {
        elemento = c_desencolar(cola);
        printf("%s\n", (char*)elemento->valor);
    }
}

int main() {
    printf("========== VENTANILLAS ==========\n");
    printf("Aclaracion: en el caso hipotetico de que se intente superar el tamanio maximo de la cola resultante, entonces el resultado quedaria incompleto.\n");
    printf("Ingrese el valor de minutos Q (debe ser positivo y como maximo 100): ");
    int Q = leer_entero();
    while (Q <= 0 || Q > 100) {
        printf("Entrada invalida, reingrese el valor de Q. ");
        Q = leer_entero();
    }
    // INGRESO DE COLAS
    printf("\n");
    printf("=== INGRESO COLAS ===\n");
    printf("[INGRESO COLA 1]\n");
    Cola cola1 = rellenar_cola_por_teclado();
    printf("[INGRESO COLA 2]\n");
    Cola cola2 = rellenar_cola_por_teclado();
    printf("[INGRESO COLA 3]\n");
    Cola cola3 = rellenar_cola_por_teclado();
    Cola copiaCola1 = copiarCola(cola1);
    Cola copiaCola2 = copiarCola(cola2);
    Cola copiaCola3 = copiarCola(cola3);
    // MUESTRO LOS CLIENTES
    printf("[COLA1]\n");
    c_mostrar(copiaCola1);
    printf("[COLA2]\n");
    c_mostrar(copiaCola2);
    printf("[COLA3]\n");
    c_mostrar(copiaCola3);
    printf("-----------------------\n");
    // ATIENDO A LOS CLIENTES
    Cola resultado = c_ej7_atenderclientes(copiaCola1, copiaCola2, copiaCola3, Q);
    mostrarClientes(copiarCola(resultado));
    return 0;
}
