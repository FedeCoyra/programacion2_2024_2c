#ifndef TP1_RECURSIVIDAD_H_INCLUDED
#define TP1_RECURSIVIDAD_H_INCLUDED

#include <stdbool.h>

// Ejercicio 1
/*1.	Construir una funci�n recursiva que retorne verdadero si una cadena de caracteres pasada
como par�metro es un pal�ndromo.  Ej. �neuquen� ya que se lee igual de atr�s hacia adelante.
No usar acentos ni caracteres especiales.*/
bool palindormo (char * cadena);


// Ejercicio 2
/*2.	Dados dos n�meros enteros m y n, construir una funci�n recursiva que devuelva
el producto de ambos, calculando el mismo como sumas sucesivas. Esto es: m*n=m+m+...+m, n veces.
Contemplar los negativos. */

int producto (int m, int n);


//Ejercicio 3
/*3.	Generar un algoritmo recursivo que calcule el k-�simo n�mero de la serie de Fibonacci.
Acotarlo a un valor de 45 como m�ximo. */

int terminoSerieFibonacci(int k);


//Ejercicio 4
/*4.	Dados los n�meros enteros m y n, construir una funci�n recursiva que devuelva el
cociente de ambos, calculando el mismo mediante restas sucesivas. Se deber� tener en cuenta que en el caso
de que la divisi�n no sea exacta, se devolver�n hasta 6 cifras decimales (si es necesario).
Contemplar los negativos. */

float division(int m, int n);


//Ejercicio 5
/*5.	Generar un algoritmo recursivo que le ponga los �.� de los miles a un String de n�meros enteros.
Contemplar los negativos.*/

char * agregarSeparadorMiles(char numero[]);


//Ejercicio 6
/*6.	Se conoce que la mafia china es muy organizada y protege mucho a sus miembros, cuando deciden asistir
a una reuni�n se dispone de una cantidad de chinos que asisten, y ellos se ubican de forma que al mirarlos
frontalmente generan cierto respeto y temor. A continuaci�n, se tiene una serie de posibles reuniones y su
nivel y la apariencia que se tiene del grupo que va a la reuni�n vistos frontalmente:

Nivel reuni�n	Vista frontal de la delegaci�n
		1 	        (-.-)
		2 		 (-.(-.-).-)
		3 	  (-.(-.(-.-).-).-)
		4  (-.(-.(-.(-.-).-).-).-)

Considerando esta descripci�n, dise�ar los procesos recursivos que permitan mostrar
la apariencia del grupo de chinos que asisten a una reuni�n de nivel n. Acotar el �n� a
un valor m�ximo de 50. */

char * reunionMafia(int nivel);


//ejercicio 7
/*8.	Se tiene una cadena que representa una onda digital de se�ales L (Low) y H (High). Se pide mostrar
la onda que representa utilizando �_�,  �|� y "�". La �L� o la �H� se pueden ingresar tanto en may�sculas
como en min�sculas.

Ejemplo: Si se tiene la cadena HHHHLLLLHHHHHLLHHLL, su onda digital se puede ver algo as�:
_ _ _ _            _ _ _ _ _      _ _
        | _ _ _ _ |         |_ _ |   | _ _

*/

char * ondaDigital(char seniales[]);


//Ejercicio 8
/*8.	Definir una funci�n recursiva que dado un conjunto devuelva una lista con los subconjuntos del mismo
tales que la suma de los elementos de cada subconjunto sumen una cantidad dada.
Por ejemplo:   Dado el conjunto A = {10, 3, 1, 7, 4, 2}. La lista de los conjuntos que sumen 7 ser�a:
R = [{3, 4}, {1, 4, 2}, {7}]*/

int ** subconjuntosQueSumanN(int conjunto[], int n, int objetivo, int *numSubconjuntos);


//Ejercicio 9
/*9. Escribir una funci�n recursiva que implemente el m�todo que se describe para saber si
un n�mero es divisible por 7. Se separa la primera cifra de la derecha, se la multiplica
por 2, y se resta este producto de lo que queda a la izquierda y as� sucesivamente,
hasta que el resultado obtenido sea un n�mero menor a 70. El n�mero original ser�
m�ltiplo de 7 si el resultado da cero o m�ltiplo de 7.
Ejemplos:
32291 -> 1x2=2.
3229 - 2 =
3227 -> 7x2=14.
322 - 14 =
308 -> 8x2=16
30 - 16 =
14 -> M�ltiplo de 7
divisiblePor7 (32291) => verdadero

110 -> 0 x 2 = 0
11 � 0 =
11 -> No m�ltiplo de 7
divisiblePor7 (110) => falso
*/

bool divisiblePor7(int n);

//Ejercicio 10
/*
10.  Se dice que N es un n�mero explosivo cuando �ste explota en varios fragmentos m�s
chicos que �l, dada una bomba B. Si se tiene que N es el n�mero y B la bomba, tales
que N es mayor que B, se puede hacer que N explote en dos n�meros N1 = N / B
(divisi�n entera) y N2 = N - (N / B).
Pero B es una bomba que produce una reacci�n en cadena, si N1 o N2 son mayores que
B, estos tambi�n explotan con la regla anterior, hasta que se encuentre que el n�mero
no es mayor que B; entonces se dice que ya no se puede explotar el n�mero.
Escribe una funci�n recursiva que retorne una lista con los pedazos del n�mero N,
dado que se tiene la bomba B.

Ejemplos:
N�mero: 10
Bomba: 3
explosion(10, 3) => [3 2 1 1 3]
N�mero: 20
Bomba: 5
explosion(20, 5) => [4 3 2 2 1 1 1 1 5]
*/

int* explosion (int n, int b);

#endif // TP1_RECURSIVIDAD_H_INCLUDED
