#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "tipo_elemento.h"

struct NodoArbolRep {
    TipoElemento datos;
    struct NodoArbolRep *hi;
    struct NodoArbolRep *hd;
    int FE;   //Factor de Equilibro de Cada nodo para el autobalanceo
};
typedef struct NodoArbolRep *NodoArbol;

// retorna el hijo izquierdo
NodoArbol n_hijoizquierdo(NodoArbol N);

// retorna el hijo derecho
NodoArbol n_hijoderecho(NodoArbol N);

// Crea un Nodo y lo retorna
NodoArbol n_crear(TipoElemento te);

// Crea un Nodo y lo retorna
TipoElemento n_recuperar(NodoArbol N);

#endif // NODO_H_INCLUDED
