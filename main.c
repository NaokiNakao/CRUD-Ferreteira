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
#define POINT       46
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

#define AGREGAR     0
#define LEER        1
#define MODIFICAR   2
#define BORRAR      3

#define ARCHCLIENTES   "clientes.txt"

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
   struct nodocliente *anterior;
   struct nodocliente *siguiente;
}NODOCLIENTE;

/* Prototipos de funciones */

// menús
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
void eliminarCliente(NODOCLIENTE**, NODOCLIENTE*);
void modificarDatosCliente(NODOCLIENTE*, int);

// validador de campo
void captureTextField(char*, int, int, int, int, int);
int strEnd(char*);
void captureDateField(char*, int, int, int);
int validDate(char*, int*, int*, int*);
void captureIntegerField(int*, char*, int, int, int);
void captureNumericField(float*, char*, int, int, int, int);
void showField(char*, int, int, int, int);
void clearLine(int, int);

/*
   Función   :
   Argumentos:
   Objetivo  :
   Retorno   :
*/

int main()
{
   srand(time(NULL));

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

      // datos de clientes
      if (opcionini == 0)
      {
         opcionesCliente(opcioncrud, ARCHCLIENTES);
      }
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

/*
   Función   : randomString
   Argumentos: char *destino: cadena de destino
               char *aux: cadena auxiliar con espacios en blanco
               int inf: valor mínimo para el caracter
               int sup: valor máximo para el caracter
   Objetivo  : agregar caracteres aleatorios a "destino"
   Retorno   : ---
*/
void randomString(char *destino, char *aux, int inf, int sup)
{
   int index;

   strcpy(destino, aux);

   for (index = 0; *(destino+index) != NULL; index++)
      destino[index] = (rand() % (sup-inf+1)) + inf;

   return;
}

/*
   Función   : fsize
   Argumentos: FILE *pf: referencia del archivo
   Objetivo  : calcular la longitud en bytes de "pf"
   Retorno   : (long) cantbytes
*/
long fsize(FILE *pf)
{
   long posarch = ftell(pf), cantbytes;

   fseek(pf,0L,SEEK_END);
   cantbytes = ftell(pf);
   fseek(pf,posarch,SEEK_SET);

   return cantbytes;
}

/*
   Función   : opcionesCliente
   Argumentos: int opcion: indica la acción a realizar
               char *archivo: nombre del archivo donde se encuentran los datos
   Objetivo  : agregar, leer, modificar o borrar datos de los clientes
   Retorno   : ---
*/
void opcionesCliente(int opcion, char *archivo)
{
   FILE *pf;
   NODOCLIENTE *listaclientes = NULL, *temp;
   CLIENTE *cliente;
   long cantidad;
   int seleccionar, index;
   char tecla;

   // abriendo el archivo
   if ((pf = fopen(archivo, "rb")) != NULL)
   {
      cantidad = fsize(pf)/sizeof(CLIENTE);
      cliente = (CLIENTE*)malloc(sizeof(CLIENTE));

      for (index = 0; index < cantidad; index++)
      {
         fseek(pf, index*sizeof(CLIENTE), SEEK_SET);
         fread(cliente, sizeof(CLIENTE), 1, pf);
         insertarFrenteCliente(&listaclientes, *cliente);
      }
      free(cliente);
      fclose(pf);
   }

   if (opcion == AGREGAR)
   {
      do {

         cliente = (CLIENTE*)calloc(1, sizeof(CLIENTE));
         printf("Digite los datos del cliente: \n\n");
         capturarDatosCliente(cliente);
         insertarFrenteCliente(&listaclientes, *cliente);
         free(cliente);

         printf("\n\n%cDesea agregar otro cliente? S(i) o N(o): ", 168);
         do {
            tecla = toupper(getch());
         } while (tecla != 'S' && tecla != 'N');

         clrscr();

      } while (tecla != 'N');

      /*if ((pf = fopen(archivo, "wb")) != NULL)
      {
         cliente = (CLIENTE*)calloc(1, sizeof(CLIENTE));

         for (temp = listaclientes, index = 0; temp != NULL; temp = temp->siguiente, index++)
         {
            fseek(pf, index*sizeof(CLIENTE), SEEK_SET);
            (*cliente) = temp->datos;
            fwrite(cliente, sizeof(CLIENTE), 1, pf);
         }
         free(cliente);
         fclose(pf);
      }*/
   }
   else if (opcion == LEER)
   {
      seleccionar = listarClientes(listaclientes, cantidad, INIX, INIY, 2);
      clrscr();
   }
   else if (opcion == MODIFICAR)
   {
      seleccionar = listarClientes(listaclientes, cantidad, INIX, INIY, 2);
      clrscr();

      temp = listaclientes;
      for (index = 0; index < seleccionar; index++)
         temp = temp->siguiente;

      if (seleccionar != EXIT)
      {
         char campos[][MAXOPC] = {"ID cliente      ",
                                  "Primer nombre   ",
                                  "Segundo nombre  ",
                                  "Primer apellido ",
                                  "Segundo apellido",
                                  "ID documento    ",
                                  "Direccion       "};
         int camposel;

         do {

            gotoxy(INIX, INIY);
            printf("Seleccione un campo");
            gotoxy(INIX, INIY+10);
            printf("Presione [ESC] para salir");
            camposel = seleccionarOpcion(campos, 7, INIX, INIY+2, 0);
            modificarDatosCliente(temp, camposel);
            clrscr();

         } while (camposel != EXIT);

         /*if ((pf = fopen(archivo, "wb")) != NULL)
         {
            cliente = (CLIENTE*)calloc(1, sizeof(CLIENTE));

            for (temp = listaclientes, index = 0; temp != NULL; temp = temp->siguiente, index++)
            {
               fseek(pf, index*sizeof(CLIENTE), SEEK_SET);
               (*cliente) = temp->datos;
               fwrite(cliente, sizeof(CLIENTE), 1, pf);
            }
            free(cliente);
            fclose(pf);
         }*/
      }
      else clrscr();
   }
   else if (opcion == BORRAR)
   {
      seleccionar = listarClientes(listaclientes, cantidad, INIX, INIY, 2);
      gotoxy(INIX, INIY+9);
      printf("%cSeguro que desea eliminar este cliente? S(i) o N(o): ");
      do {
         tecla = toupper(getch());
      } while (tecla != 'S' && tecla != 'N');

      if (tecla == 'S')
      {
         temp = listaclientes;
         for (index = 0; index < seleccionar; index++)
            temp = temp->siguiente;
         eliminarCliente(&listaclientes, temp);

         /*if ((pf = fopen(archivo, "wb")) != NULL)
         {
            cliente = (CLIENTE*)calloc(1, sizeof(CLIENTE));

            for (temp = listaclientes, index = 0; temp != NULL; temp = temp->siguiente, index++)
            {
               fseek(pf, index*sizeof(CLIENTE), SEEK_SET);
               (*cliente) = temp->datos;
               fwrite(cliente, sizeof(CLIENTE), 1, pf);
            }
            free(cliente);
            fclose(pf);
         }*/
         gotoxy(INIX, INIY+10);
         printf("Cliente eliminado.");
         Sleep(2000);
      }
      clrscr();
   }

   if (opcion != LEER)
   {
      if ((pf = fopen(archivo, "wb")) != NULL)
      {
         cliente = (CLIENTE*)calloc(1, sizeof(CLIENTE));

         for (temp = listaclientes, index = 0; temp != NULL; temp = temp->siguiente, index++)
         {
            fseek(pf, index*sizeof(CLIENTE), SEEK_SET);
            (*cliente) = temp->datos;
            fwrite(cliente, sizeof(CLIENTE), 1, pf);
         }
         free(cliente);
         fclose(pf);
      }
   }

   return;
}

/*
   Función     : capturarDatosCliente
   Arrgumentos : CLIENTE *cliente: referencia donde se almacenarán los datos
   Objetivo    : capturar los datos de un cliente
   Retorno     : ---
*/
void capturarDatosCliente(CLIENTE *cliente)
{
   printf("Primer nombre: ");
   captureTextField(cliente->primernomb, LENPRINOMBRE, 15, 3, FALSE, FALSE);
   printf("Segundo nombre: ");
   captureTextField(cliente->segnomb, LENSEGNOMBRE, 16, 4, FALSE, FALSE);
   printf("Primer apellido: ");
   captureTextField(cliente->primerapel, LENPRIAPEL, 17, 5, FALSE, FALSE);
   printf("Segundo apellido: ");
   captureTextField(cliente->segapel, LENSEGAPEL, 18, 6, FALSE, FALSE);
   printf("ID documento: ");
   captureTextField(cliente->docid, MAXID, 14, 7, TRUE, TRUE);
   printf("Direcci%cn: ", 162);
   captureTextField(cliente->direccion, LENDIR, 11, 8, FALSE, FALSE);

   // generando un id para el cliente
   randomString(cliente->idcliente, IDCLIENTEAUX, INFNUM, SUPNUM);

   return;
}

/*
   Función     : insertarFrenteCliente
   Arrgumentos : NODOCLIENTE **cabeza: cabeza de la lista
                 CLIENTE info: nueva infromación
   Objetivo    : insertar información de clientes al inicio de la lista
   Retorno     : ---
*/
void insertarFrenteCliente(NODOCLIENTE **cabeza, CLIENTE info)
{
   NODOCLIENTE *nuevo = (NODOCLIENTE*)malloc(sizeof(NODOCLIENTE));
   nuevo->datos = info;
   nuevo->siguiente = (*cabeza);
   nuevo->anterior = NULL;

   if ((*cabeza) != NULL)
      (*cabeza)->anterior = nuevo;

   (*cabeza) = nuevo;

   return;
}

/*
   Función     : listarClientes
   Arrgumentos : NODOCLIENTE *clientes: lista donde están almacenados los clientes
                 int n: cantidad de clientes
                 int px: posción en x
                 int py: posición en y
                 int rango: cantidad de clientes mostrados en el menú de scroll
   Objetivo    : desplegar un menú con cursor para seleccionar un cliente
   Retorno     : (int) pos: cliente seleccionado
*/
int listarClientes(NODOCLIENTE *clientes, int n, int px, int py, int rango)
{
   char tecla;
   int pos = 0, inf = 0, sup = rango;

   _setcursortype(FALSE);

   do {

      mostrarClientes(clientes, n, px, py, pos, inf, sup);

      do {
         tecla = getch();
      } while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER && tecla != ESC);

      if (tecla != ESC)
      {
         if (tecla == ARRIBA)
         {
            if (pos != 0)
            {
               pos--;
               if (pos < inf)
               {
                  inf--;
                  sup--;
               }
            }
            else
            {
               pos = n-1;
               sup = n-1;
               inf = sup-rango;
            }
         }
         else if (tecla == ABAJO)
         {
            if (pos < n-1)
            {
               pos++;
               if (pos > sup)
               {
                  sup++;
                  inf++;
               }
            }
            else
            {
               pos = 0;
               inf = 0;
               sup = rango;
            }
         }
      }
      else pos = EXIT;

   } while (tecla != ENTER && tecla != ESC);

   _setcursortype(100);

   return pos;
}

/*
   Función     : mostrarClientes
   Arrgumentos : NODOCLIENTE *clientes: lista donde están almacenados los clientes
                 int n: cantidad de clientes
                 int px: posción en x
                 int py: posición en y
                 int inf: indica el primer cliente mostrado en la salida
                 int sup: indica el último cliente mostrado en la salida
   Objetivo    : mostrar los clientes
   Retorno     : ---
*/
void mostrarClientes(NODOCLIENTE *clientes, int n, int px, int py, int actual, int inf, int sup)
{
   NODOCLIENTE *index = clientes;
   int cont, renglon;

   // se recorre la lista hasta el primer cliente que
   // se mostrará en el menú de scroll
   for (cont = 0; cont != inf; cont++)
      index = index->siguiente;

   gotoxy(px, py);
   setColor(WHITE, GREEN);
   printf("       ID          Nombre y apellido                      ");
   char espacio[] = "                                                          ";

   for (index, cont = inf, renglon = 0; cont <= sup && index != NULL; index = index->siguiente, cont++, renglon++)
   {
      gotoxy(px, py+renglon+2);
      setColor(BLUE, LIGHTGRAY);
      if (cont == actual)
         setColor(YELLOW, BLUE);
      printf("%s", espacio);
      gotoxy(px+1, py+renglon+2);
      printf("%s", index->datos.idcliente);
      gotoxy(px+19, py+renglon+2);
      printf("%s %s", index->datos.primernomb, index->datos.primerapel);
   }

   defaultColor();

   return;
}

/*
   Función     : eliminarCliente
   Arrgumentos : NODOCLIENTE **cabeza: referencia a la cabeza de la lista
                 NODOCLIENTE *elim: nodo de la lista a eliminar
   Objetivo    : eliminar un cliente
   Retorno     : ---
*/
void eliminarCliente(NODOCLIENTE **cabeza, NODOCLIENTE *elim)
{
   if ((*cabeza) == NULL || elim == NULL)
      return;

   if ((*cabeza) == elim)
      (*cabeza) = elim->siguiente;

   if (elim->siguiente != NULL)
      elim->siguiente->anterior = elim->anterior;

   if (elim->anterior != NULL)
      elim->anterior->siguiente = elim->siguiente;

   free(elim);

   return;
}

void modificarDatosCliente(NODOCLIENTE *cliente, int campo)
{
   int px = INIX+17, py = INIY+2+campo;

   if (campo == 0)
   {
      captureTextField(cliente->datos.idcliente, MAXIDCLIENTE, px, py, FALSE, TRUE);
   }
   else if (campo == 1)
   {
      captureTextField(cliente->datos.primernomb, LENPRINOMBRE, px, py, FALSE, FALSE);
   }
   else if (campo == 2)
   {
      captureTextField(cliente->datos.segnomb, LENSEGNOMBRE, px, py, FALSE, FALSE);
   }
   else if (campo == 3)
   {
      captureTextField(cliente->datos.primerapel, LENPRIAPEL, px, py, FALSE, FALSE);
   }
   else if (campo == 4)
   {
      captureTextField(cliente->datos.segapel, LENSEGAPEL, px, py, FALSE, FALSE);
   }
   else if (campo == 5)
   {
      captureTextField(cliente->datos.docid, MAXID, px, py, FALSE, TRUE);
   }
   else if (campo == 6)
   {
      captureTextField(cliente->datos.direccion, LENDIR, px, py, FALSE, FALSE);
   }

   return;
}

/*
   Función     : captureTextField
   Arrgumentos : char* str    : cadena de texto a capturar
                 int n        : longitud de "str"
                 char* tipo   : indica el mensaje según el tipo de dato
                 int pos_x    : posición en las columnas
                 int pos_y    : posición en las filas
                 int flag     : indica si se restringe el espacio
                 int alfanumeric: indica si el campo será alfa-numérico
   Objetivo    : capturar campo de tipo texto
   Retorno     : ---
*/
void captureTextField(char* str, int n, int pos_x, int pos_y, int flag, int alfanumeric)
{
   int index, last;
   char key, temp[n];

   for (index = 0; *(str+index) != NULL; index++);
   last = index;

   do {

      showField(str, index, n, pos_x, pos_y);

      do {
         key = getch();
      } while (!(key >= 33 && key <= 126) && key != IZQUIERDA && key != DERECHA &&
               key != BARRA && key != BKSP && key != ESC && key != ENTER);

      if (alfanumeric && !(key >= INFNUM && key <= SUPNUM) && key != BKSP && key != ESC && key != ENTER)
         continue;

      if (key == DERECHA)
      {
         if (index < n-1 && index < last)
         {
            index++;
         }
      }
      else if (key == IZQUIERDA)
      {
         if (index > 0)
            index--;
      }
      else if (key == BARRA)
      {
         if (!flag)
         {
            // se verifica que los caracteres no se salgan del margen
            // permitido al presionar la barra espaciadora
            if (index < n-1 && strEnd(str) < n)
            {
               strcpy(temp, str+index);
               strcpy(str+index, " ");
               strcpy(str+index+1, temp);
               index++;
               last++;
            }
         }
      }
      else
      {
         if (key != ENTER && key != ESC)
         {
            if (key == BKSP)
            {
               if (index)
               {
                  strcpy(temp, str+index);
                  index--;
                  strcpy(str+index, temp);
                  last--;
               }
            }
            else if (index < n)
            {
               *(str+index) = key;
               index++;

               if (index > last)
                  last = index;
            }
         }
      }

      *(str+last) = NULL;

   } while (key != ENTER && key != ESC);

   clearLine(pos_x, pos_y);
   gotoxy(pos_x, pos_y);
   printf(" %s", str);
   printf("\n");

   return;
}

/*
   Función     : strEnd
   Arrgumentos : char* str : cadena de texto
   Objetivo    : encontrar la posición del caracter NULL
   Retorno     : (int) count : posición del caracter NULL
*/
int strEnd(char* str)
{
   int count = 0;

   while (*(str+count))
      count++;

   return count;
}

/*
   Función     : captureDateField
   Arrgumentos : char* str    : cadena de texto a capturar
                 int n        : longitud de "str"
                 int pos_x    : columnas
                 int pos_y    : filas
   Objetivo    : capturar campo de tipo fecha
   Retorno     : ---
*/
void captureDateField(char* str, int n, int pos_x, int pos_y)
{
   int index = 0, last = index;
   char key;

   do {

      showField(str, index, n, pos_x, pos_y);

      do {
         key = getch();
      } while (!(key >= INFNUM && key <= SUPNUM) && key != SLASH && key != ENTER && key != ESC
               && key != DERECHA && key != IZQUIERDA && key != BKSP);

      if (key == DERECHA)
      {
         if (index < n-1 && index < last)
            index++;
      }
      else if (key == IZQUIERDA)
      {
         if (index > 0)
            index--;
      }
      else
      {
         if (key != ENTER && key != ESC)
         {
            if (key == BKSP)
            {
               if (index)
               {
                  index--;
                  *(str+index) = NULL;
                  last--;
               }
            }
            else if (index < n)
            {
               *(str+index) = key;
               index++;

               if (index > last)
                  last = index;
            }
         }
      }

      *(str+last) = NULL;

   } while (key != ENTER && key != ESC);

   return;
}

/*
   Función     : validDate
   Arrgumentos : char* date : fecha en cadena de texto
                 int* day   : almacena el día en "date"
                 int* month : almacena el mes en "date"
                 int* year  : almacena el año en "date"
   Objetivo    : validar que la fecha y su formato sean correctos
   Retorno     : (int) 1 si la fecha es correcta; (int) 0 en caso contrario
*/
int validDate(char* date, int* day, int* month, int* year)
{
   int index, count;

   // validando la posición de los slash
   if (*(date+2) != SLASH && *(date+5) != SLASH)
      return FALSE;

   // validando la cantidad de números
   for (index = 0, count = 0; index < MAXDATE; index++)
   {
      if (*(date+index) >= '0' && *(date+index) <= '9')
         count++;
   }

   if (count != 8) return FALSE;

   char temp[MAXDATE-6];
   int d_months[] = {DM31, DM30-2, DM31, DM30, DM31, DM30, DM31, DM31, DM30, DM31, DM30, DM31};

   strncpy(temp, date, 2);
   *day = strtol(temp, NULL, 10);
   strncpy(temp, date+3, 2);
   *month = strtol(temp, NULL, 10);
   strncpy(temp, date+6, 4);
   *year = strtol(temp, NULL, 10);

   // validando la cantidad de días en los meses
   if (*month <= 12 && *month > 0 && *day > 0)
   {
      if (*month == FEB)
      {
         // validando año bisiesto
         if ( *day == DM30-1 && !(*year % 4) )
            return TRUE;
      }

      if (*day > d_months[*month-1])
         return FALSE;
   }
   else
      return FALSE;

   return TRUE;
}

/*
   Función     : captureIntegerField
   Arrgumentos : int* num      : número a capturar
                 int digits    : cantidad de dígitos permitidos en "str"
                 int pos_x    : posición en las columnas
                 int pos_y    : posición en las filas
   Objetivo    : capturar campo de tipo numérico
   Retorno     : ---
*/
void captureIntegerField(int* num, char* tipo, int digits, int pos_x, int pos_y)
{
   int index = 0, n = digits, last = index;
   char key, *str;

   str = (char*)calloc(digits, sizeof(char));

   printf("%s", tipo);

   do {

      showField(str, index, n, pos_x, pos_y);

      do {
         key = getch();
      } while (!(key >= '0' && key <= '9') && key != ENTER && key != ESC &&
                key != DERECHA && key != IZQUIERDA && key != BKSP);

      if (key == DERECHA)
      {
         if (index < n-1 && index < last)
            index++;
      }
      else if (key == IZQUIERDA)
      {
         if (index > 0)
            index--;
      }
      else
      {
         if (key != ENTER && key != ESC)
         {
            if (key == BKSP)
            {
               if (index)
               {
                  index--;
                  *(str+index) = NULL;
                  last--;
               }
            }
            else if (index < n)
            {
               *(str+index) = key;
               index++;

               if (index > last)
                  last = index;
            }
         }
      }

      *(str+last) = NULL;

   } while (key != ENTER && key != ESC);

   *num = strtol(str, NULL, 10);

   clearLine(pos_x, pos_y);
   gotoxy(pos_x, pos_y);
   printf("%d", *num);
   printf("\n");

   return;
}

/*
   Función     : captureNumericField
   Arrgumentos : int* num      : número a capturar
                 int digits    : cantidad de dígitos permitidos en "str"
                 int precision : cantidad de números después del punto
                 int pos_x    : posición en las columnas
                 int pos_y    : posición en las filas
   Objetivo    : capturar campo de tipo numérico
   Retorno     : ---
*/
void captureNumericField(float* num, char* tipo, int digits, int precision, int pos_x, int pos_y)
{
   int index = 0, n = digits, last = index, flag = FALSE;
   char key, *str;

   str = (char*)calloc(digits, sizeof(char));

   printf("%s", tipo);

   do {

      showField(str, index, n, pos_x, pos_y);

      do {
         key = getch();
      } while (!(key >= '0' && key <= '9') && (key != POINT && !flag) && key != ENTER
               && key != ESC && key != DERECHA && key != IZQUIERDA && key != BKSP);

      if (key == DERECHA)
      {
         if (index < n-1 && index < last)
            index++;
      }
      else if (key == IZQUIERDA)
      {
         if (index > 0)
            index--;
      }
      else if (key == POINT)
      {
         if (!flag)
         {
            *(str+index) = key;
            index++;

            if (index > last)
               last = index;
         }
      }
      else
      {
         if (key != ENTER && key != ESC)
         {
            if (key == BKSP)
            {
               if (index)
               {
                  index--;
                  *(str+index) = NULL;
                  last--;
               }
            }
            else if (index < n)
            {
               *(str+index) = key;
               index++;

               if (index > last)
                  last = index;
            }
         }
      }

      flag = FALSE;

      for (int count = 0; *(str+count); count++)
      {
         if (*(str+count) == POINT)
         {
            flag = TRUE;
            if ( (n - (count+1)) > precision )
            {
               n = count+precision+1;
               clearLine(pos_x, pos_y);
            }
            break;
         }
      }

      *(str+last) = NULL;

      if (flag)
         continue;
      else
         n = digits;

   } while (key != ENTER && key != ESC);

   *num = strtof(str, NULL);

   clearLine(pos_x, pos_y);
   gotoxy(pos_x, pos_y);
   printf("%.2f", *num);
   printf("\n");

   return;
}

/*
   Función     : showField
   Arrgumentos : char* str : cadena de texto
                 int pos   : posición del cursor
                 int n     : longitud de "str"
                 int x     : posición en x (columnas)
                 int y     : posición en y (filas)
   Objetivo    : mostrar el campo de texto
   Retorno     : ---
*/
void showField(char* str, int pos, int n, int x, int y)
{
   int index;

   setColor(BLUE, LIGHTGRAY);

   for (index = 0; index < n; index++)
   {
      gotoxy(x+index+1, y);

      if (*(str+index))
         printf("%c", *(str+index));
      else
         printf(" ");
   }

   defaultColor();
   gotoxy(x+pos+1, y);

   return;
}

/*
   Función     : clearLine
   Arrgumentos : int pos_x: columnas
                 int pos_y: filas
   Objetivo    : borrar la línea "line"
   Retorno     : ---
*/
void clearLine(int pos_x, int pos_y)
{
   for (pos_x; pos_x <= MAXLINE; pos_x++)
   {
      gotoxy(pos_x, pos_y);
      printf(" ");
   }

   return;
}














































