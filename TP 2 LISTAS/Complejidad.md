.4) Complejidad algoritmica = O(n). Siendo n la cantidad de elementos. La complejidad algoritmica de esta solucion
, al ser implementada en un bucle while, depende de la cantidad de elementos en los cuales se itera. 
Se recorren ambas listas al mismo tiempo. Esta complejidad se encuentra en la funcion "comparar()".

.6) La complejidad algoritmica más alta es la de la funcion "es_sublista()", y es O(m * n), 
donde n es el tamaño de la lista secundaria y m es el tamaño de la lista principal. 
Esto se debe a que la función recorre cada elemento de la lista secundaria en un bucle externo, 
y luego busca ese elemento en la lista principal en un bucle interno. En el peor caso, 
cuando cada elemento de la lista secundaria no se encuentra en la lista principal, 
el bucle interno se ejecutará m veces para cada uno de los n elementos de la lista secundaria.

Debido a que los puntos 4) y 6) tienen una complejidad algorítmica de O(n) o más, 
y que la complejidad de las TADs de listas es de máximo O(n), entonces esta complejidad de las TADs se ve absorbida por los ejercicios.
