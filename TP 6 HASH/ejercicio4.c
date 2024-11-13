#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listas.h"
#include "tabla_hash.h"
#include "tipo_elemento.h"

#define CAPACIDAD 2000
#define PRIMO 1999
#define MAXIMAEJ4 20

typedef struct ralumnos {
    int legajo;
    int estado;
    char apellido[20];
    char nombre[20];
    char domicilio[20];
    int TE;
    int indice;
} ralumnos;

void crear_alta(char nombre[], char modo[], TablaHash th, int legajo, int * indice);
void alta(char nombre[], char modo[], TablaHash th, int legajo, int indice);
bool conversionEntero(char *string, int *nro, int len);
void pedirDatos(int *nro, int tamanio);
void rango(int *nro, int rango);
void strtrim(char *cadena);
void leer_palabra(char * c);
bool conversionCharPunto4(char *string);
void pedirChar(char *string);
void mostrarMenu(TablaHash th, int *indice);
void crearArchivoBinario(char nombre[], char modo[]);
void baja(char nombre[], char modo[],TablaHash th, int legajo, int indice);
void modificacion(char nombre[], char modo[], TablaHash th, int legajo, int indice, int respuesta);
void mostrarBinario(char nombre[], char modo[]);
void mostrarDatosAlumno(char nombre[], char modo[], int indice);
int hashingMod(int clave);
void agregar_archivos_al_hash(char nombre[], char modo[], TablaHash th, int *indiceMain);

// ====================================================

void crear_alta(char nombre[], char modo[], TablaHash th, int legajo, int * indice){
    FILE*fp=fopen(nombre,modo);
    ralumnos alumno;
    char apellido2Aux[MAXIMAEJ4]={};
    char nombreAux[MAXIMAEJ4]={};
    char domicilioAux[MAXIMAEJ4]={};
    int telefono;
    //Doy el alta con el indice de la posicion en el archivo
    printf("\t\t/// Ingrese Apellido del alumno: ");
    pedirChar(apellido2Aux);

    printf("\t\t/// Ingrese Nombre del alumno: ");
    pedirChar(nombreAux);
    printf("\t\t/// Ingrese domicilio (localidad) del alumno: ");
    pedirChar(domicilioAux);

    printf("\t\t/// Ingrese telefono del alumno(sin prefijo): ");
    pedirDatos(&telefono,11);
    while(((telefono)<=0) || (telefono>=9999999999999)){
        printf("\t\t/// Numero invalido o demasiado grande.\n");
        printf("\t\t/// Ingrese nuevamente: ");
        pedirDatos(&telefono,11);
    }

    //Pongo todos los datos escritos en el registro para hacer el write
    alumno.legajo=legajo;
    strcpy(alumno.apellido,apellido2Aux);
    strcpy(alumno.nombre,nombreAux);
    strcpy(alumno.domicilio,domicilioAux);
    alumno.TE=telefono;
    alumno.estado=1; //1 activo, 2 borrado
    alumno.indice=(*indice);

    //Pongo los datos del registro en el hash
    ralumnos *indiceAlumno=(ralumnos*)malloc(sizeof(ralumnos));
    (*indiceAlumno)=alumno;
    TipoElemento te=te_crear_con_valor(alumno.legajo, indiceAlumno);
    th_insertar(th, te);

    //Escribo en el archivo y cierro el archivo
    fwrite(&alumno, sizeof(ralumnos),1,fp);
    fclose(fp);
}

void alta(char nombre[], char modo[], TablaHash th, int legajo, int indice){
    FILE*fp=fopen(nombre,modo);
    ralumnos alumno;
    TipoElemento te=th_recuperar(th, legajo);
    ralumnos *alumnoTh=(ralumnos*)te->valor;
    fseek(fp, sizeof(ralumnos)*indice,SEEK_SET);
    fread(&alumno,sizeof(ralumnos),1,fp);
    alumno.estado=1; //alta logica
    (*alumnoTh).estado=1;
    fseek(fp,-(long int)sizeof(ralumnos),SEEK_CUR);
    fwrite(&alumno, sizeof(ralumnos),1,fp);
    fclose(fp);
}

bool conversionEntero(char *string, int *nro, int len) {
    int i = 0;
    // Contar la cantidad de espacios.
    while(isspace(string[i]))
        i++;
    // Controlar cadena vacia.
    if (len == i) return false;

    char * buffer = malloc(sizeof(char)*len);
    int indiceEntero = 0;

    // Controlar si es un numero negativo.
    if (string[i] == '-'){
        buffer[indiceEntero] = '-';
        indiceEntero++;
        i++;

        if (!isdigit(string[i])) return false;
    }

    // Leer los digitos.
    while (i < len && !isspace(string[i])){
        if (!isdigit(string[i])) return false;
        buffer[indiceEntero] = string[i];
        indiceEntero++;
        i++;
    }

    // Agregar el caracter nulo al final del string.
    buffer[indiceEntero] = '\0';

    // Termino de recorrer el string.
    while (isspace(string[i]))
        i++;

    // Si hay mas para recorrer y no son blancos, el string contiene otros caracteres.
    if (string[i] != '\0') return false;

    // Convierto el string a un entero.
    *nro = atoi(buffer);

    return true;
}

void pedirDatos(int *nro, int tamanio) {
    bool conversionCorrecta = true;
    do{
        char * bufferNro = malloc(sizeof(char) * tamanio);
        fgets(bufferNro, tamanio, stdin);
        conversionCorrecta = conversionEntero(bufferNro, nro, tamanio);
        if (!conversionCorrecta){
            printf("El numero es invalido, revisa los requerimientos\n");
            printf("Ingrese otro numero: ");
            fflush(stdin);
        }
    } while (!conversionCorrecta);
}

void rango(int *nro, int rango) {
    while (abs(*nro) > rango){
        printf("El numero ingresado debe estar comprendido en [-9999;9999], intente nuevamente.\n");
        pedirDatos(nro, 11);
    }
}

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

void leer_palabra(char * c) {
    char entrada[30];
    int EsValido = false;

    while (!EsValido){
        int contadorDeEspacios = 0;
        EsValido = true;
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        for (int i=0;i<strlen(entrada);i++){
            if (i != 0 && i != strlen(entrada) && entrada[i] == ' '){
                contadorDeEspacios++;
            } else if (!isalpha(entrada[i]) || contadorDeEspacios > 2){
                EsValido = false;
            }
        }
        if (!EsValido)
            printf("Entrada invalida, Ingrese Nuevamente: ");
    }
    strcpy(c, entrada);
}

bool conversionCharPunto4(char *string) {
    int tamanio=strlen(string)-1;   //consigo el tamanio del array para usarlo en el for y saber si está vacia o no
    if(tamanio>=MAXIMAEJ4-1){
        printf("\t\t///Dato demasiado grande.\n");
        return false;
    }
    int i=0;

    string[tamanio]='\0'; //quito el \n puesto por el fgets en la ultima linea
    if(strlen(string)==0){
        printf("\t\t/// Cadena vacia no es valida.\n"); //Compruebo que no sea una cadena vacia antes de seguir
        return false;
    }

    for(i; i<tamanio; i++){
        while(!((string[i]>=65) && (string[i]<=90)) && !((string[i]>=97) && (string[i]<=122))){ //Si no esta entre los digitos ascii de 0 a 9 tira mensaje de error
            return false;
            }
    }
    return true;
}

void pedirChar(char *string){
    bool conversionCorrecta = true;
    do{
        fgets(string, MAXIMAEJ4+1, stdin);
        conversionCorrecta = conversionCharPunto4(string);
        fflush(stdin);
        if (!conversionCorrecta){
            printf("\t\t/// Dato invalido, intente nuevamente.\n");
            printf("\t\t/// Ingrese nuevamente: ");
        }
    } while (!conversionCorrecta);
}

void mostrarMenu(TablaHash th, int *indice){
    int respuesta;
    int legajoAlta;
    int legajoBaja;
    int legajoMod;
    int respuestaMod;
    int opcionMod;
    bool estaActivo;
    TipoElemento te;
    ralumnos *alumnos=(ralumnos*)malloc(sizeof(ralumnos));
    do {
        printf("\t\t/////////////////////////////////////////////////////////\n");
        printf("\t\t///                       Menu                        ///\n");
        printf("\t\t/// 1 Dar altas de alumnos (con legajo)               ///\n");
        printf("\t\t/// 2 Dar baja de alumnos (con legajo)                ///\n");
        printf("\t\t/// 3 Modificar datos alumno (con legajo)             ///\n");
        printf("\t\t/// 4 Mostrar archivo alumnos                         ///\n");
        printf("\t\t/// 5 Mostrar Tabla Hash de alumnos                   ///\n");
        printf("\t\t/// 0 Salir                                           ///\n");
        printf("\t\t/////////////////////////////////////////////////////////\n");

        printf("\t\tIngrese una opcion [0-5]: ");
        pedirDatos(&respuesta, 11);

        /////////    ALTAS    /////////
        if(respuesta==1){
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
            printf("\t\t/////////////////////////////////////////////////////////\n");
            printf("\t\t/// Has ingresado a la seccion de altas de alumnos. \n");
            printf("\t\t/// Por favor, ingrese el legajo del alumno a \n\t\t/// dar de alta: ");
            pedirDatos(&legajoAlta, 11);
            while(((legajoAlta)<=0) || (legajoAlta>999999)){
                printf("\t\t/// Legajo invalido.\n");
                printf("\t\t/// Ingrese nuevamente: ");
                pedirDatos(&legajoAlta,11);
            }
            te=th_recuperar(th, legajoAlta);
            if(te){
                alumnos=(ralumnos*)te->valor;
                if((*alumnos).estado==2){
                    printf("\t\t/// Realizando alta del alumno con legajo %d...\n", legajoBaja);
                    alta("alumnos.dat","r+b", th, legajoAlta, (*alumnos).indice);
                    printf("\t\t/// alta del alumno %d realizada correctamente. \n", legajoBaja);
                }else if((*alumnos).estado==1){
                    printf("\t\t/// El alumno con legajo %d ya esta activo.\n", legajoAlta);
                    printf("\t\t/////////////////////////////////////////////////////////\n");
                }
            }else{
                printf("\t\t/// Realizando alta del alumno con legajo %d...\n",legajoAlta);
                crear_alta("alumnos.dat","ab", th, legajoAlta, indice);
                printf("\t\t/// Alta del alumno %d realizada correctamente.\n",legajoAlta);
                printf("\t\t/////////////////////////////////////////////////////////\n");
                (*indice)+=1;
            }
            printf("\t\tPresione enter para volver al menu.");
            fflush(stdin);
            getchar();
            printf("\033[2J\033[H");
            // system("cls");
        }
        /////////////////////////////

        /////////    BAJAS    /////////
        else if(respuesta==2){
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
            printf("\t\t/////////////////////////////////////////////////////////\n");
            printf("\t\t/// Has ingresado a la seccion de bajas de alumnos. \n");
            printf("\t\t/// Por favor, ingrese el legajo del alumno a \n\t\t/// dar de baja: ");
            pedirDatos(&legajoBaja,11);
            te=th_recuperar(th, legajoBaja);
            if(te){
                alumnos=(ralumnos*)(te->valor);
                if((*alumnos).estado==2){
                    printf("\t\t/// El alumno con legajo %d ya se encuentra dado de baja.\n", legajoBaja);
                    printf("\t\t/////////////////////////////////////////////////////////\n");
                }else if((*alumnos).estado==1){
                    printf("\t\t/// Realizando baja del alumno con legajo %d...\n",legajoBaja);
                    baja("alumnos.dat","r+b",th, legajoBaja,(*alumnos).indice);
                    printf("\t\t/// Baja del alumno %d realizada correctamente.\n",legajoBaja);
                    printf("\t\t/////////////////////////////////////////////////////////\n");
                }
            }else{
                printf("\t\t/// El alumno con legajo %d no existe en \n\t\t/// el archivo para poder darlo de baja.\n", legajoBaja);
                printf("\t\t/////////////////////////////////////////////////////////\n");
            }
            printf("\t\tPresione enter para volver al menu.");
            fflush(stdin);
            getchar();
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
        }
        /////////////////////////////////////

        /////////    MODIFICACIONES    /////////
        else if(respuesta==3){
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
            printf("\t\t/////////////////////////////////////////////////////////\n");
            printf("\t\t/// Has ingresado a la seccion de modificaciones\n\t\t/// de alumnos. \n");
            printf("\t\t/// Por favor, ingrese el legajo del alumno a \n\t\t/// modificar: ");
            pedirDatos(&legajoMod,11);
            te=th_recuperar(th, legajoMod);
            if(te){
                alumnos=(ralumnos*)(te->valor);
                if((*alumnos).estado==2){
                    printf("\t\t/// El alumno con legajo %d se encuentra dado de baja\n\t\t/// por lo tanto no se puede modificar.\n", legajoMod);
                    printf("\t\t/////////////////////////////////////////////////////////\n");
                }else if((*alumnos).estado==1){
                    do{
                        printf("\t\t/// Datos actuales del alumnno con legajo %d:\n", legajoMod);
                        mostrarDatosAlumno("alumnos.dat","rb",(*alumnos).indice);
                        printf("\t\t///\n");
                        printf("\t\t/// Que modificacion desea relizar?\n");
                        printf("\t\t/// 1. Apellido.\n");
                        printf("\t\t/// 2. Nombre.\n");
                        printf("\t\t/// 3. Domicilio.\n");
                        printf("\t\t/// 4. Telefono.\n");
                        printf("\t\t/// 0. Salir.\n");
                        printf("\t\t/////////////////////////////////////////////////////////\n");
                        printf("\t\tIngrese una opcion [0-4]: ");
                        pedirDatos(&respuestaMod, 11);
                        if((respuestaMod<0) || (respuestaMod>4)){
                            printf("\t\tDato invalido, revisa las opciones.\n");
                            printf("\t\tPresione enter para volver al menu de modificaciones.");
                            fflush(stdin);
                            getchar();
                            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
                        }else{
                            modificacion("alumnos.dat","r+b",th, legajoMod, (*alumnos).indice, respuestaMod);
                        }
                    }while(respuestaMod!=0);
                }
            }else{
                printf("\t\t/// El alumno con legajo %d no existe en \n\t\t/// el archivo para poder modificar datos.\n", legajoMod);
                printf("\t\t/////////////////////////////////////////////////////////\n");
            }
            printf("\t\tPresione enter para volver al menu.");
            fflush(stdin);
            getchar();
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
        }
        /////////////////////////////////////

        /////////    MOSTRAR ARCHIVO BIN    /////////
        else if(respuesta==4){
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
            printf("\t\t/////////////////////////////////////////////////////////\n");
            printf("\t\t/// Mostrando archivo alumnos...\n");
            mostrarBinario("alumnos.dat","rb");
            printf("\t\t/// Archivo alumnos mostrado correctamente.\n");
            printf("\t\t/////////////////////////////////////////////////////////\n");
            printf("\t\tPresione enter para volver al menu.");
            fflush(stdin);
            getchar();
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
        }
        //////////////////////////////////////////

        /////////    MOSTRAR HASH    /////////
        else if(respuesta==5){
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
            printf("///////////////////////////////////////////////////\n");
            printf("Mostrando Tabla Hash...\n");
            // th_mostrar(th);
            th_mostrar_solo_ocupados(th);
            printf(" Tabla Hash mostrada correctamente.\n");
            printf("///////////////////////////////////////////////////\n");
            printf("Presione enter para volver al menu.");
            fflush(stdin);
            getchar();
            printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
            // system("cls");
        }
        ////////////////////////////////////////

        /////////    DATO INCORRECTO    /////////
        else{
            if(respuesta!=0){
                printf("\t\tDato incorrecto, intente nuevamente.\n");
                printf("\t\tPresione enter para volver al menu.");
                fflush(stdin);
                getchar();
                printf("\033[2J\033[H"); // se limpia la pantalla, un reemplazo de cls para que ande en la terminal de visual
                // system("cls");
            }
        }
        /////////////////////////////
    } while (respuesta!=0);
    printf("\t\tSaliendo del programa...\n");
}

void crearArchivoBinario(char nombre[], char modo[]){
    FILE*fp=fopen(nombre, modo);
    fclose(fp);
}

void baja(char nombre[], char modo[],TablaHash th, int legajo, int indice){
    FILE*fp=fopen(nombre,modo);
    ralumnos alumno;
    TipoElemento te=th_recuperar(th, legajo);
    ralumnos *alumnoTh=(ralumnos*)te->valor;
    fseek(fp, sizeof(ralumnos)*indice,SEEK_SET);
    fread(&alumno,sizeof(ralumnos),1,fp);
    alumno.estado=2; //baja logica
    (*alumnoTh).estado=2;
    fseek(fp,-(long int)sizeof(ralumnos),SEEK_CUR);
    fwrite(&alumno, sizeof(ralumnos),1,fp);
    fclose(fp);
}

void modificacion(char nombre[], char modo[], TablaHash th, int legajo, int indice, int respuesta){
    FILE*fp=fopen(nombre,modo);
    ralumnos alumno;
    TipoElemento te=th_recuperar(th, legajo);
    ralumnos *alumnoTh=(ralumnos*)te->valor;
    char apellido2Aux[MAXIMAEJ4]={};
    char nombreAux[MAXIMAEJ4]={};
    char domicilioAux[MAXIMAEJ4]={};
    int telefono;

    fseek(fp, sizeof(ralumnos)*indice,SEEK_SET);
    fread(&alumno,sizeof(ralumnos),1,fp);

    if(respuesta==1){
        printf("\t\t/// Ingrese el nuevo apellido: ");
        pedirChar(apellido2Aux);
        strcpy(alumno.apellido,apellido2Aux);
    }else if(respuesta==2){
        printf("\t\t/// Ingrese el nuevo nombre: ");
        pedirChar(nombreAux);
        strcpy(alumno.nombre,nombreAux);
    }else if(respuesta==3){
        printf("\t\t/// Ingrese el nuevo domicilio: ");
        pedirChar(domicilioAux);
        strcpy(alumno.domicilio,domicilioAux);
    }else if(respuesta==4){
        printf("\t\t/// Ingrese el nuevo telefono: ");
        pedirDatos(&telefono,11);
        alumno.TE=telefono;
    }
    (*alumnoTh)=alumno;
    fseek(fp,-(long int)sizeof(ralumnos),SEEK_CUR);
    fwrite(&alumno, sizeof(ralumnos),1,fp);
    fclose(fp);
}

void mostrarBinario(char nombre[], char modo[]){
    FILE*fp=fopen(nombre,modo);
    ralumnos alumno;
    while(fread(&alumno, sizeof(ralumnos),1,fp)){
        if(alumno.estado==1){
            printf("\t\t/// Legajo del alumno: %d, Indice en el archivo: %d.\n",alumno.legajo, alumno.indice);
            printf("\t\t/// Apellido: %s.\n", alumno.apellido);
            printf("\t\t/// Nombre: %s.\n",alumno.nombre);
            printf("\t\t/// Domicilio: %s.\n",alumno.domicilio);
            printf("\t\t/// Telefono: %d.\n", alumno.TE);
        }
        printf("\t\t/// \n");
    }
    fclose(fp);
}

void mostrarDatosAlumno(char nombre[], char modo[], int indice){
    FILE*fp=fopen(nombre,modo);
    ralumnos alumno;
    fseek(fp, sizeof(ralumnos)*indice,SEEK_SET);
    fread(&alumno, sizeof(ralumnos),1,fp);
    printf("\t\t/// Apellido: %s.\n", alumno.apellido);
    printf("\t\t/// Nombre: %s.\n",alumno.nombre);
    printf("\t\t/// Domicilio: %s.\n",alumno.domicilio);
    printf("\t\t/// Telefono: %d.\n", alumno.TE);
    fclose(fp);
}

int hashingMod(int clave){
    return clave%PRIMO;
}

void agregar_archivos_al_hash(char nombre[], char modo[], TablaHash th, int *indiceMain){
    FILE*fp=fopen(nombre,modo);
    TipoElemento te;
    ralumnos alumno;
    ralumnos *alumnoTh;
    int cantidadLecturas=0;
    while(fread(&alumno, sizeof(ralumnos),1,fp)){
        alumnoTh=(ralumnos*)malloc(sizeof(ralumnos));
        (*alumnoTh)=alumno;
        te=te_crear_con_valor(alumno.legajo, alumnoTh);
        th_insertar(th, te);
        cantidadLecturas+=1;
    }
    if(cantidadLecturas>=1){
        *indiceMain=cantidadLecturas+1; //Esto permite recuperar el indice si hubo lecutras
    }
    fclose(fp);
}

int main() {
    int indice = 0;
    TablaHash th = th_crear(CAPACIDAD, &hashingMod);
    agregar_archivos_al_hash("alumnos.dat","rb", th, &indice);
    mostrarMenu(th, &indice);

    free(th);
    return 0;
}
