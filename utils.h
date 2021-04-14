/*
   Sistema de una empresa de alquiler de equipos que tiene clientes que pueden alquilar equipos
   para uno o varios proyectos. Permite ingresar/modificar/eliminar clientes, proyectos, equipos,
   los procesos de: conteo, despacho, devolución, generación de facturas, cuenta del cliente y
   cobros al cliente.

   Autor: Naoki Nakao
   Fecha: en curso
*/

#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Directivas de preprocesador */

#define MAXIDCLIENTE 16
#define MAXIDPROP 16
#define MAXID 13
#define LENPRINOMBRE 21
#define LENSEGNOMBRE 16
#define LENPRIAPEL 16
#define LENSEGAPEL 16
#define LENDIR 51
#define LENDESC 51
#define MAXIDPROY 6
#define MAXIDEQUIPO 6
#define MAXIDCONT 6
#define MAXNUMFACT 11
#define MAXTIPOFACT 9
#define MAXIDDEVOLUCION 6

#define IDCLIENTEAUX   "               "
#define IDEQUIPOAUX    "     "

#define FALSE   0
#define TRUE    1

#define ARRIBA      72
#define ABAJO       80
#define IZQUIERDA   75
#define DERECHA     77
#define ENTER       13
#define ESC         27
#define BARRA       32
#define BKSP         8
#define EXIT        -1
#define DOT         46
#define SLASH       47
#define MAXDATE     10
#define DM30        30
#define DM31        31
#define FEB          2
#define MAXLINE     80

#define INFNUM    48
#define SUPNUM    57
#define GUION     45
#define ESPACIO   ' '

#define MAXOPC   30
#define INIX      3
#define INIY      3
#define RANGO     4
#define DELAY    2000

#define AGREGAR     0
#define LEER        1
#define MODIFICAR   2
#define BORRAR      3

#define ARCHCLIENTES   "clientes.dat"
#define ARCHEQUIPOS    "equipos.dat"

/* Estructuras */

typedef struct{
 int dia,mes,agno;
}FECHA;

typedef struct{
   char idcliente[MAXIDCLIENTE];
   char primernomb[LENPRINOMBRE];
   char segnomb[LENSEGNOMBRE];
   char primerapel[LENPRIAPEL];
   char segapel[LENSEGAPEL];
   char docid[MAXID];
   char direccion[LENDIR];
}CLIENTE;

typedef struct{
   char idproyecto[MAXIDPROY];
   char descripcion[LENDESC];
   char idcliente[MAXIDCLIENTE];
}PROYECTO;

typedef struct{
   char idpropcontrato[MAXIDPROP];
   char idproyecto[MAXIDPROY];
   FECHA fechapropcontrato;
   char status;
}PROPCONTRACTO;

typedef struct{
   char idcliente[MAXIDCLIENTE];
   char idproyecto[MAXIDPROY];
   char idconteo[MAXIDCONT];
   char Descripcion[LENDESC];
   float monto;
}CUENTACLIENTE;

typedef struct{
   char idequipo[MAXIDEQUIPO];
   char descripcion[LENDESC];
   int cantinventario;
   int cantprestados;
   float precioprestamo;
   float costoequipo;
}EQUIPO;

typedef struct{
   char idpropcontrato[MAXIDPROP];
   char idequipo[MAXIDEQUIPO];
   int cantidad;
}EQUIPROP;

typedef struct{
   char idpropcontrato[MAXIDPROP];
   char idconteo[MAXIDCONT];
   char idequipo[MAXIDEQUIPO];
   int cantidad;
   int cantdevuelta;
}CONTEO;

typedef struct{
   char numfactura[MAXNUMFACT];
   char tipo[MAXTIPOFACT];
   char idpropcontrato[MAXIDPROP];
   char idconteo[MAXIDCONT];
   FECHA fecha;
   float monto;
}FACTURA;

typedef struct{
   char iddevolucion[MAXIDDEVOLUCION];
   char idpropcontrato[MAXIDPROP];
   FECHA fecha;
}DEVOLUCION;

typedef struct{
   char iddevolucion[MAXIDDEVOLUCION];
   char idpropcontrato[MAXIDPROP];
   char idconteo[MAXIDCONT];
   char idequipo[MAXIDEQUIPO];
   int cantidad;
   FECHA fecha;
}DETALLEDEVOLUCION;

// Estrucutras para las listas doblemente enlazadas

typedef struct nodocliente {
   CLIENTE datos;
   struct nodocliente *siguiente;
   struct nodocliente *anterior;
}NODOCLIENTE;

typedef struct nodoequipo {
   EQUIPO datos;
   struct nodoequipo *siguiente;
   struct nodoequipo *anterior
}NODOEQUIPO;

/* Prototipos de funciones */

// menú
int seleccionarOpcion(char [][MAXOPC], int, int, int, int);
void mostrarMenu(char [][MAXOPC], int, int, int, int);
void setColor(int, int);
void defaultColor();
void randomString(char*, char*, int, int);
long fsize(FILE*);

// datos de clientes
void opcionesCliente(int, char*);
void capturarDatosCliente();
void insertarFrenteCliente(NODOCLIENTE**, CLIENTE);
int listarClientes(NODOCLIENTE*, int, int, int, int);
void mostrarClientes(NODOCLIENTE*, int, int, int, int, int, int);
void modificarDatosCliente(NODOCLIENTE*, int);
void eliminarCliente(NODOCLIENTE**, NODOCLIENTE*);

// información sobre equipos en inventario
void opcionesEquipos(int, char*);
void capturarDatosEquipo(EQUIPO*);
void insertarFrenteEquipo(NODOEQUIPO**, EQUIPO);

// validador de campo
void captureTextField(char*, int, int, int, int, int);
int strEnd(char*);
void captureDateField(char*, int, int, int);
int validDate(char*, int*, int*, int*);
void captureIntegerField(int*, int, int, int);
void captureNumericField(float*, int, int, int, int);
void showField(char*, int, int, int, int);
void clearLine(int, int);

#endif
