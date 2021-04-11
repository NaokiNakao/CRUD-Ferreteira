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

#define FALSE   0
#define TRUE    1

#define ARRIBA   72
#define ABAJO    80
#define ENTER    13
#define ESC      27
#define EXIT     -1

#define MAXOPC   30
#define INIX      3
#define INIY      3

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

int seleccionarOpcion(char [][MAXOPC], int, int, int, int);
void mostrarMenu(char [][MAXOPC], int, int, int, int);
void setColor(int, int);
void defaultColor();

/*
   Función   :
   Argumentos:
   Objetivo  :
   Retorno   :
*/

int main()
{
   char menuinicio[][MAXOPC] = {"Datos de clientes       ",
                                "Proyectos               ",
                                "Cuentas de clientes     ",
                                "Propuestas de contrato  ",
                                "Despacho                ",
                                "Conteo                  ",
                                "Equipos en inventario   ",
                                "Devolucion de equipos   ",
                                "Equipo perdido          ",
                                "Facturas de continuacion",
                                "Facturas de venta       "};

   char crud[][MAXOPC] = {"Agregar  ",
                          "Mostrar  ",
                          "Modificar",
                          "Borrar   "};

   int opcionini, opcioncrud;

   while (TRUE)
   {
      gotoxy(INIX, INIY);
      printf("CRM-Ferreter%ca", 161);

      opcionini = seleccionarOpcion(menuinicio, 11, INIX, INIY+2, 0);
      opcioncrud = seleccionarOpcion(crud, 4, INIX+26, INIY+opcionini+2, 0);
      system("cls");
   }

   return 0;
}

/*
   Función   : seleccionarOpcion
   Argumentos: char menu[][MAXOPC]: contiene las opciones del menú
               int n: cantidad de opciones del menú
               int px: posición a desplegar en x
               int py: posición a desplegar en y
               int pos: posición inicial
   Objetivo  : controlar el movimiento del cursor al mostrar el menú
   Retorno   : (int) pos: opción que se seleccionó al presionar [ENTER]
*/
int seleccionarOpcion(char menu[][MAXOPC], int n, int px, int py, int pos)
{
   char tecla;

   _setcursortype(FALSE);

   do {

      mostrarMenu(menu, n, px, py, pos);

      do {
         tecla = getch();
      } while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER && tecla != ESC);

      if (tecla != ESC)
      {
         if (tecla == ARRIBA)
         {
            if (pos != 0)
               pos--;
            else
               pos = n-1;
         }
         else if (tecla == ABAJO)
         {
            if (pos < n-1)
               pos++;
            else
               pos = 0;
         }
      }
      else pos = EXIT;

   } while (tecla != ENTER && tecla != ESC);

   _setcursortype(100);

   return pos;
}

/*
   Función   : mostrarMenu
   Argumentos: char menu[][MAXOPC]: contiene las opciones del menú
               int n: cantidad de opciones del menú
               int px: posición a desplegar en x
               int py: posición a desplegar en y
               int actual: posición actual del cursor
   Objetivo  : mostrar el menú
   Retorno   : ---
*/
void mostrarMenu(char menu[][MAXOPC], int n, int px, int py, int actual)
{
   int index;

   for (index = 0; index < n; index++)
   {
      setColor(BLUE, LIGHTGRAY);
      if (index == actual)
         setColor(YELLOW, BLUE);
      gotoxy(px, py+index);
      printf("%s", menu[index]);
   }

   defaultColor();
   return;
}

/*
   Función   : setColor
   Argumentos: int colortexto: color a cambiar del texto
               int colorfondo: color a cambiar del fondo
   Objetivo  : cambiar el color del texto y el fondo
   Retorno   : ---
*/
void setColor(int colortexto, int colorfondo)
{
   textcolor(colortexto);
   textbackground(colorfondo);
}

/*
   Función   : defaultColor
   Argumentos: ---
   Objetivo  : reestablecer los colores predeterminados de la consola
   Retorno   : ---
*/
void defaultColor()
{
   setColor(WHITE, BLACK);
}













































