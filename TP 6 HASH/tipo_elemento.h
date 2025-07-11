#ifndef TIPO_ELEMENTO_H_INCLUDED
#define TIPO_ELEMENTO_H_INCLUDED

struct TipoElementoRep {
    int clave;
    void* valor;
};
typedef struct TipoElementoRep *TipoElemento;

TipoElemento te_crear(int clave);
TipoElemento te_crear_con_valor(int clave, void* valor);

#endif // TIPO_ELEMENTO_H
