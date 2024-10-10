## COMPLEJIDAD SIN TENER EN CUENTA TADS

### EJERICIO 3
La funcion principal c_ej3_iguales() tiene una complejidad de O(n), siendo "n" la cantidad de elementos de la cola.
Sin embargo, rellenar_cola_por_teclado() tiene la complejidad mas alta con una complejidad de O(m * n). Esto debido a que
por la longitud de la cola, en cada iteracion de esa longitud "n" se llama a leer_entero(), que a su vez llama a strtrim(),
con complejidad O(m), donde "m" es la cantidad de caracteres ingresados por teclado.
Por esta razon, las complejidades se acumulan y da como resultado **O(m * n)**.

### EJERCICIO 4
La funcion principal y con mas complejidad del ejercicio es la de c_ej4_colanorepetidos() con **O(n^2)**, donde "n"
es la cantidad de elementos en la cola.

### EJERCICIO 5
La funcion principal c_ej5_divisortotal() tiene una complejidad de O(n^2). Sin embargo, la complejidad
mas alta del ejercicio esta en rellenar_colas_por_teclado_sin_repetidos(), con una complejidad de **O(n^2 * m)**, donde
"m" es la cantidad de caracteres que tiene el ingreso, y "n" es la longitud de la cola. 

### EJERCICIO 6
La funcion que tiene la complejidad mas alta es la de c_ej6_comunesapilaycola(), que tiene una complejidad de **O(m * n)**,
donde "m" es la cantidad de elementos que tiene la cola y "n" es la cantidad de elementos que tiene la pila.



## COMPLEJIDAD TENIENDO EN CUENTA TADS

### EJERICIO 3
- TAD Cola Punteros: la funcion c_ej3_iguales() cambia y ahora tiene la complejidad mas alta con **O(n^2)**. Esto ya que se usa un while que recorre una cola y dentro se usa el c_encolar(), en donde se utiliza la funcion interna longitud() para recorrer la cola y decir si esta llena (verifica antes de encolar).

- TAD Cola Arreglos Circulares: la complejidad de la funciones con complejidad mas alta se mantiene igual ya que las funciones que se usan de esta TAD en el ejercicio son de complejidad menor -> O(1). Por ende, esta complejidad se ve absorbida por complejidades mayores.

- TAD Cola Arreglos: la funcion c_ej3_iguales() cambia y ahora tiene la complejidad mas alta con **O(n^2)**. Esto ya que se usa un while que recorre una cola y dentro se usa el c_desencolar(), que a su vez recorre toda la cola para desplazar sus valores cuando un elemento se desencola.

### EJERICIO 4
- TAD Cola Punteros: la complejidad de las funciones con complejidad mas alta se mantienen igual ya que las funciones que se usan de esta TAD en el ejercicio son de complejidad menor -> O(1). Por ende, esta complejidad se ve absorbida por complejidades mayores.

- TAD Cola Arreglos Circular: la complejidad de las funciones con complejidad mas alta se mantienen igual ya que las funciones que se usan de esta TAD en el ejercicio son de complejidad menor -> O(1). Por ende, esta complejidad se ve absorbida por complejidades mayores.

- TAD Cola Arreglos: la funcion c_ej3_iguales() cambia y ahora tiene la complejidad mas alta con **O(n^3)**. Esto ya que se usa un while que recorre una cola y dentro se usa el c_desencolar(), que a su vez recorre toda la cola para desplazar sus valores cuando un elemento se desencola.

### EJERCICIO 5
- TAD Cola Punteros: la funcion rellenar_colas_por_teclado_sin_repetidos() cambia y ahora tiene la complejidad mas alta con **O(n^3 * m)**. Esto ya que al recorrer la cola O(n), tambien verifica dentro de este recorrido si cada elemento que se intenta encolar ya esta en la cola O(n^2), y ademas dentro de este se lee un entero que tiene como complejidad O(m), donde se usa strtrim() para recorrer el array de chars ingresado por consola (m seria la cantidad de caracteres). Entonces, resumiendo se multiplica la complejidad O(n) * O(n^2) * O(m), quedando O(n^3 * m).

- TAD Cola Arreglos Circular: la complejidad de las funciones con complejidad mas alta se mantienen igual ya que las funciones que se usan de esta TAD en el ejercicio son de complejidad menor -> O(1). Por ende, esta complejidad se ve absorbida por complejidades mayores.

- TAD Cola Arreglos: la funcion c_ej5_divisortotal() cambia y ahora tiene la complejidad mas alta con **O(n^3)**. Esto ya que se usa un while que recorre una cola y dentro se usa el c_desencolar(), que a su vez recorre toda la cola para desplazar sus valores cuando un elemento se desencola. La otra funcion con complejidad alta, que es rellenar_colas_por_teclado_sin_repetidos() no cambia y tiene la misma complejidad que si no tuvieramos en cuenta las TADs, esto debido a que solo c_desencolar() acumula una complejidad mayor a O(1) y esta funcion no se usa en la funcion previamente dicha, por lo que no varia.

### EJERCICIO 6
- TAD Pila Arreglos: el uso de estga TAD no afecta a la complejidad previamente calculada ya que la unica complejidad mayor a O(1) es la funcion p_mostrar(), que no se usa en las funciones.

- TAD Pila Punteros: el uso de esta TAD solo afecta a las funciones que utilizan la funcion p_apilar(), que tiene una complejidad de O(n) en esta TAD. Este cambio afecta a la funcion copiar_pila(), cambiando su complejidad de O(n) a **O(n^2)**. Fuera de esto, lo previamente calculado sin tener en cuenta las TADs se mantiene igual.

- TAD Lista Arreglos: las complejidades se esta TAD no afectan a la complejidad de ejercicio ya que casi todas las funciones de esta TAD tienen complejidad O(1), y son las que se usan en el ejercicio. Las que no se usan, sí tienen una complejidad mayor que podria afectar a la complejidad total del ejercicio, pero estas no se usan. En conclusion, la complejidad no se afecta por parte de esta TAD.

- TAD Lista Cursores: la unica funcion cuya complejidad dentro de la TAD afecta al ejercicio, es la de l_agregar(), ya que en la misma se tiene complejidad O(n), que se usa dentro de dos whiles anidados que dependen de la pila y la cola O(n * m), y a esto se le sumaria el uso de l_agregar() adentro del while interno, transformando la complejidad de la funcion c_ej6_comunesapilaycola() en **O(n * m * l)**.

- TAD Lista Punteros: la unica funcion cuya complejidad dentro de la TAD afecta al ejercicio, es la de l_agregar(), ya que en la misma se tiene complejidad O(n), que se usa dentro de dos whiles anidados que dependen de la pila y la cola O(n * m), y a esto se le sumaria el uso de l_agregar() adentro del while interno, transformando la complejidad de la funcion c_ej6_comunesapilaycola() en **O(n * m * l)**

- TAD Cola Punteros: la funcion principal c_ej6_comunesapilaycola() no se ve afectada por el cambio de complejidad utilizado en esta TAD. Sin embargo, la funcion llenar_cola_al_azar() tendra una nueva complejidad de **O(n^2)** ya que se usa c_encolar() y en este caso cuando se encola, primero se debe verificar que haya espacio en la cola, y para eso se recorre toda la cola.

- TAD Cola Arreglos Circular: la complejidad de las funciones con complejidad mas alta se mantienen igual ya que las funciones que se usan de esta TAD en el ejercicio son de complejidad menor -> O(1). Por ende, esta complejidad se ve absorbida por complejidades mayores.

- TAD Colas Arreglos: la complejidad de la funcion principal c_ej6_comunesapilaycola() se ve alterada por esta TAD, y ahora la complejidad pasa a ser de O(m * n) a O(m * n^2). Esto sucede debido a que c_desencolar() recorre la cola y por eso tieen complejidad O(n). Ahora, dentro de la funcion c_ej6_comunesapilaycola() se tienen dos ciclos anidados, uno dependiendo de la pila (m), y uno dependiendo de la cola (n). Si agregamos el uso de c_desencolar() a la ecuacion, nos queda que esta se usa dentro del ciclo interno y esto lo hace O(n^2), mas el recorrido de la pila, **O(m * n^2)**.
