#ifndef CONJUNTOS_H_INCLUDED
#define CONJUNTOS_H_INCLUDED

#include <stdbool.h>
#include "tipo_elemento.h"

struct ConjuntoRep;
typedef struct ConjuntoRep *Conjunto;

/**
 * Crea un conjunto vac�o.
 *
 * @return Conjunto - una nueva instancia de conjunto.
 */
Conjunto cto_crear();

/**
 * Indica si el conjunto est� vac�o.
 *
 * @param conjunto una instancia de tipo conjunto.
 * @return bool - true si el conjunto est� vac�o, false en caso contrario.
 */
bool cto_es_vacio(Conjunto conjunto);

/**
 * Indica si el conjunto est� lleno.
 *
 * @param conjunto una instancia de tipo conjunto.
 * @return bool - true si el conjunto est� lleno, false en caso contrario.
 */
bool cto_es_lleno(Conjunto conjunto);

/**
 * Devuelve la cantidad de elementos en el conjunto.
 *
 * @param conjunto una instancia de tipo conjunto.
 * @return la cantidad de elementos en el conjunto.
 */
int cto_cantidad_elementos(Conjunto conjunto);

/**
 * Agrega un elemento al conjunto.
 *
 * @param conjunto una instancia de tipo conjunto.
 * @param elemento el elemento a agregar al conjunto.
 */
bool cto_agregar(Conjunto conjunto, TipoElemento elemento);

/**
 * Borra un elemento del conjunto.
 *
 * @param conjunto una instancia de tipo conjunto.
 * @param clave la clave del elemento a borrar.
 */
bool cto_borrar(Conjunto conjunto, int clave);

/**
 * Indica si un elemento est� en el conjunto.
 *
 * @param conjunto una instancia de tipo conjunto.
 * @param clave la clave del elemento a buscar.
 * @return bool - true si el elemento est� en el conjunto, false en caso contrario.
 */
bool cto_pertenece(Conjunto conjunto, int clave);

/**
 * Devuelve la uni�n de dos conjuntos.
 *
 * @param conjunto_a el primer conjunto.
 * @param conjunto_b el segundo conjunto.
 * @return una nueva instancia de tipo conjunto que es la uni�n de los dos conjuntos pasados por par�metro.
 */
Conjunto cto_union(Conjunto conjunto_a, Conjunto conjunto_b);

/**
 * Devuelve la intersecci�n de dos conjuntos.
 *
 * @param conjunto_a el primer conjunto.
 * @param conjunto_b el segundo conjunto.
 * @return una nueva instancia de tipo conjunto que es la intersecci�n de los dos conjuntos pasados por par�metro.
 */
Conjunto cto_interseccion(Conjunto conjunto_a, Conjunto conjunto_b);

/**
 * Devuelve la diferencia entre dos conjuntos.
 *
 * @param conjunto_a el primer conjunto.
 * @param conjunto_b el segundo conjunto.
 * @return una nueva instancia de tipo conjunto que es la diferencia entre los dos conjuntos pasados por par�metro.
 */
Conjunto cto_diferencia(Conjunto conjunto_a, Conjunto conjunto_b);

/**
 * Devuelve el tipo elemento de una posicion logica.
 *
 * @param conjunto el primer conjunto.
 * @param posicion_ordinal la posicion ordinal para recuperar un item del conjunto.
 * @return un tipo elemento de esa posicion o NULL si la posicion no es valida.
 */
TipoElemento cto_recuperar(Conjunto conjunto, int posicion_ordinal);

/**
 * Muestra el conjunto. Solo las claves.
 *
 * @param conjunto el primer conjunto.
 */
void cto_mostrar(Conjunto conjunto);

#endif // CONJUNTOS_H_INCLUDED
