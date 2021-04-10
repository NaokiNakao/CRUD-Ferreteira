/*
   Sistema de una empresa de alquiler de equipos que tiene clientes que pueden alquilar equipos
   para uno o varios proyectos. Permite ingresar/modificar/eliminar clientes, proyectos, equipos,
   los procesos de: conteo, despacho, devolución, generación de facturas, cuenta del cliente y
   cobros al cliente.

   Autor: Naoki Nakao
   Fecha: en curso
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.c>
#include <time.h>

// Directivas de preprocesador

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

// Estructuras

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

// Prototipos de funciones

/*
   Función   :
   Argumentos:
   Objetivo  :
   Retorno   :
*/

int main()
{

   return 0;
}
