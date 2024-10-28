## COMPLEJIDAD SIN TENER EN CUENTA TADS
### EJERCICIO 2
La complejidad de las funciones a_ej2_hojas, a_ej2_interiores y a_ej2_buscarclave es de **O(n)**, debido a que la complejidad en los tres casos depende linealmente de la cantidad de elementos "n" que se tiene. Esto ya que a pesar de que las funciones hacen algo diferente, en todas se debe recorrer el árbol en su totalidad.

### EJERCICIO 9
Sin tener en cuenta las TADs, la función con complejidad más alta es construirAVL, con una complejidad de **O(n)**. Esto ya que se recorre por cada nodo del árbol binario. En este caso se hace obviedad de la TAD y por ende la inserción en el AVL no tiene peso.


## COMPLEJIDAD TENIENDO EN CUENTA TADS
### EJERCICIO 2
- TAD LISTAS ARREGLOS: en este caso, las únicas dos funciones que se utilizan de esta implementación son l_crear y l_agregar. En ambas la complejidad es de O(1), y se ven absorbidas por la complejidad que tiene la función en sí, que es de **O(n)**.

- TAD LISTAS PUNTEROS: en este caso, las únicas dos funciones que se utilizan de esta implementación son l_crear y l_agregar. En la primera la complejidad es de O(1), mientras que en la segunda la complejidad es de O(n). Como igualmente dijimos que las funciones en sí (sin contar las TADs) ya poseen una complejidad de O(n), éstas no se elevarían al cuadrado (quedando O(n^2)) ya que en este caso, las "n" dependen de diferentes cosas. En l_agregar depende de ir hasta el último nodo de la lista, mientras que en las funciones principales ésto depende de la cantidad de nodos a recorrer. Por lo tanto, cada nodo del árbol se visita solo una vez en la recursión, y las complejidades de las funciones se mantienen con complejidad **O(m*n)**, siendo "m" la cantidad de elementos en la lista y "n" la cantidad de nodos a recorrer en el árbol.

- TAD LISTAS CURSORES: en este caso, las únicas dos funciones que se utilizan de esta implementación son l_crear y l_agregar. En ambas la complejidad es de O(n). Como igualmente dijimos que las funciones en sí (sin contar las TADs) ya poseen una complejidad de O(n), éstas no se elevarían al cuadrado (quedando O(n^2)) ya que en este caso, las "n" dependen de diferentes cosas. En l_agregar depende de ir hasta el último nodo de la lista, mientras que en las funciones principales ésto depende de la cantidad de nodos a recorrer. Por lo tanto, cada nodo del árbol se visita solo una vez en la recursión, y las complejidades de las funciones se mantienen con complejidad **O(m*n)**, siendo "m" la cantidad de elementos en la lista y "n" la cantidad de nodos a recorrer en el árbol.

### EJERCICIO 9
- TAD ARBOL BINARIO y ARBOL AVL: si bien la complejidad de la función principal a_ej9_diferenciaalturas tiene una complejidad de O(n), la complejidad más alta es la de la función construirAVL con **O(n log(n))**, ya que por cada nodo que se recorre en el árbol binario (n), se tiene que hacer una inserción en el AVL (log n).
