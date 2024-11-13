#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include "tipo_elemento.h"
#include <stdbool.h>

struct TablaHashRep;
typedef struct TablaHashRep *TablaHash;

/**
 * Crea una nueva tabla hash con un tama�o inicial y una funci�n hash especificada.
 *
 * @param tamano - un valor entero que indica el tama�o inicial de la tabla hash.
 * @param hash_function - un puntero a una funci�n que se utilizar� para calcular el hash de las claves.
 * @return TablaHash - una nueva instancia de TablaHash con el tama�o y funci�n hash especificados.
 */
TablaHash th_crear(int tamano, int (*hash_function)(int));

/**
 * Inserta un TipoElemento en la tabla hash especificada.
 *
 * @param th - la tabla hash donde se insertar� el elemento.
 * @param te - un TipoElemento que se insertar� en la tabla hash.
 */
bool th_insertar(TablaHash th, TipoElemento te);

/**
 * Elimina un TipoElemento de la tabla hash especificada.
 *
 * @param th - la tabla hash de donde se eliminar� el elemento.
 * @param clave - un valor entero que se utilizar� como clave del elemento que se eliminar�.
 */
bool th_eliminar(TablaHash th, int clave);

/**
 * Recupera el TipoElemento con la clave especificada de la tabla hash.
 *
 * @param th - la tabla hash donde se buscar� el elemento.
 * @param clave - un valor entero que se utilizar� como clave del elemento que se buscar�.
 * @return TipoElemento - un puntero al TipoElemento con la clave especificada o NULL si no se encuentra.
 */
TipoElemento th_recuperar(TablaHash th, int clave);

/**
 * Muestra todos los elementos de la tabla hash, incluyendo los espacios vac�os.
 *
 * @param th - la tabla hash que se mostrar�.
 */
void th_mostrar(TablaHash th);

/**
 * Muestra solo los elementos ocupados de la tabla hash, es decir, aquellos con un TipoElemento asociado.
 *
 * @param th - la tabla hash que se mostrar�.
 */
void th_mostrar_solo_ocupados(TablaHash th);

#endif //TABLA_HASH_H
