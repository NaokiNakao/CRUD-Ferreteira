/*
   Sistema de una empresa de alquiler de equipos que tiene clientes que pueden alquilar equipos
   para uno o varios proyectos. Permite ingresar/modificar/eliminar clientes, proyectos, equipos,
   los procesos de: conteo, despacho, devolución, generación de facturas, cuenta del cliente y
   cobros al cliente.

   Autor: Naoki Nakao
   Fecha: en curso
*/

#include "utils.h"
#include <conio.c>

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
   NODOCLIENTE *cabeza = NULL, *temp;
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
         fread(cliente, sizeof(CLIENTE), 1, pf);
         insertarFrenteCliente(&cabeza, *cliente);
      }
      free(cliente);
      fclose(pf);
   }
   else if (opcion != AGREGAR)
   {
      puts("No hay clientes agregados.");
      Sleep(DELAY);
      clrscr();
      return;
   }

   if (opcion == AGREGAR)
   {
      do {

         cliente = (CLIENTE*)calloc(1, sizeof(CLIENTE));
         printf("Digite los datos del cliente: \n\n");
         capturarDatosCliente(cliente);
         insertarFrenteCliente(&cabeza, *cliente);
         free(cliente);

         printf("\n\n%cDesea agregar otro cliente? S(i) o N(o): ", 168);
         do {
            tecla = toupper(getch());
         } while (tecla != 'S' && tecla != 'N');

         clrscr();

      } while (tecla != 'N');
   }
   else if (opcion == LEER)
   {
      seleccionar = listarClientes(cabeza, cantidad, INIX, INIY, 2);
      clrscr();
   }
   else if (opcion == MODIFICAR)
   {
      seleccionar = listarClientes(cabeza, cantidad, INIX, INIY, 2);
      clrscr();

      temp = cabeza;
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
      }
      else clrscr();
   }
   else if (opcion == BORRAR)
   {
      seleccionar = listarClientes(cabeza, cantidad, INIX, INIY, 2);
      gotoxy(INIX, INIY+9);
      printf("%cSeguro que desea eliminar este cliente? S(i) o N(o): ");
      do {
         tecla = toupper(getch());
      } while (tecla != 'S' && tecla != 'N');

      if (tecla == 'S')
      {
         temp = cabeza;
         for (index = 0; index < seleccionar; index++)
            temp = temp->siguiente;
         eliminarCliente(&cabeza, temp);

         gotoxy(INIX, INIY+10);
         printf("Cliente eliminado.");
         Sleep(DELAY);
      }
      clrscr();
   }

   // sobreescribiendo el archivo si la opción seleccionada fue
   // para agregar, modificar o borrar clientes
   if (opcion != LEER)
   {
      if ((pf = fopen(archivo, "wb")) != NULL)
      {
         cliente = (CLIENTE*)malloc(sizeof(CLIENTE));

         for (temp = cabeza, index = 0; temp != NULL; temp = temp->siguiente, index++)
         {
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
   printf("       ID          Nombre completo                        ");
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
      printf("%s", index->datos.primernomb);
      if (index->datos.segnomb[0] != NULL)
         printf(" %c.", index->datos.segnomb[0]);
      printf(" %s", index->datos.primerapel);
      printf(" %s", index->datos.segapel);
   }

   defaultColor();

   return;
}

/*
   Función     : modificarDatosCliente
   Arrgumentos : NODOCLIENTE *cliente: regerencia del cliente
                 int campo: indica el campo que se va a modificar
   Objetivo    : modificar un campo en la información del cliente
   Retorno     : ---
*/
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

/*
   Función   : opcionesEquipos
   Argumentos: int opcion: indica la acción a realizar
               char *archivo: nombre del archivo donde se encuentran los datos
   Objetivo  : agregar, leer, modificar o borrar datos de los equipos
   Retorno   : ---
*/
void opcionesEquipos(int opcion, char *archivo)
{
   FILE *pf;
   NODOEQUIPO *cabeza = NULL, *temp;
   EQUIPO *equipo;
   long cantidad;
   int seleccionar, index;
   char tecla;

   // abriendo el archivo
   if ((pf = fopen(archivo, "rb")) != NULL)
   {
      cantidad = fsize(pf)/sizeof(EQUIPO);
      equipo = (EQUIPO*)malloc(sizeof(EQUIPO));

      for (index = 0; index < cantidad; index++)
      {
         fseek(pf, index*sizeof(EQUIPO), SEEK_SET);
         fread(equipo, sizeof(EQUIPO), 1, pf);
         insertarFrenteEquipo(&cabeza, *equipo);
      }
      free(equipo);
      fclose(pf);
   }
   else if (opcion != AGREGAR)
   {
      puts("No hay equipos agregados.");
      Sleep(DELAY);
      clrscr();
      return;
   }

   if (opcion == AGREGAR)
   {
      do {

         equipo = (EQUIPO*)calloc(1, sizeof(EQUIPO));
         printf("Digite los datos del equipo:\n\n");
         capturarDatosEquipo(equipo);
         insertarFrenteEquipo(&cabeza, *equipo);
         free(equipo);

         printf("\n\n%cDesea agregar otro equipo? S(i) o N(o): ", 168);
         do {
            tecla = toupper(getch());
         } while (tecla != 'S' && tecla != 'N');

         clrscr();

      } while (tecla != 'N');
   }
   else if (opcion == LEER)
   {
      seleccionar = listarEquipos(cabeza, cantidad, INIX, INIY, RANGO);
      clrscr();
   }
   else if (opcion == MODIFICAR)
   {
      seleccionar = listarEquipos(cabeza, cantidad, INIX, INIY, RANGO);
      clrscr();

      if (seleccionar != EXIT)
      {
         temp = cabeza;
         for (index = 0; index < seleccionar; index++)
            temp = temp->siguiente;

         char campos[][MAXOPC] = {"ID del equipo         ",
                                  "Nombre                ",
                                  "Cantidad en inventario",
                                  "Precio de alquiler    ",
                                  "Costo de venta        ",};
         int camposel;

         do {

            gotoxy(INIX, INIY);
            printf("Seleccione un campo");
            gotoxy(INIX, INIY+10);
            printf("Presione [ESC] para salir");
            camposel = seleccionarOpcion(campos, 5, INIX, INIY+2, 0);
            modificarInfoEquipos(temp, camposel);
            clrscr();

         } while (camposel != EXIT);
      }
      else clrscr();
   }

   if (opcion != LEER)
   {
      if ((pf = fopen(archivo, "wb")) != NULL)
      {
         equipo = (EQUIPO*)malloc(sizeof(EQUIPO));

         for (temp = cabeza, index = 0; temp != NULL; temp = temp->siguiente, index++)
         {
            fseek(pf, index*sizeof(EQUIPO), SEEK_SET);
            (*equipo) = temp->datos;
            fwrite(equipo, sizeof(EQUIPO), 1, pf);
         }
         free(equipo);
         fclose(pf);
      }
   }

   return;
}

/*
   Función     : capturarDatosEquipo
   Arrgumentos : EQUIPO *equipo: referencia donde se almacenarán los datos
   Objetivo    : capturar los datos de un equipo
   Retorno     : ---
*/
void capturarDatosEquipo(EQUIPO *equipo)
{
   printf("Nombre del equipo: ");
   captureTextField(equipo->descripcion, LENDESC, 19, 3, FALSE, FALSE);
   printf("Cantidad en inventario: ");
   captureIntegerField(&equipo->cantinventario, 10, 24, 4);
   printf("Precio de pr%cstamo: ", 130);
   captureNumericField(&equipo->precioprestamo, 10, 2, 20, 5);
   printf("Precio de venta: ");
   captureNumericField(&equipo->costoequipo, 10, 2, 17, 6);

   // la cantidad de equipos prestados inicia en 0
   equipo->cantprestados = 0;

   // generando un ID para el equipo
   randomString(equipo->idequipo, IDEQUIPOAUX, INFNUM, SUPNUM);

   return;
}

/*
   Función     : insertarFrenteEquipo
   Arrgumentos : NODOEQUIPO **cabeza: cabeza de la lista
                 EQUIPO info: nueva infromación
   Objetivo    : insertar información de equipos al inicio de la lista
   Retorno     : ---
*/
void insertarFrenteEquipo(NODOEQUIPO **cabeza, EQUIPO info)
{
   NODOEQUIPO *nuevo = (NODOEQUIPO*)malloc(sizeof(NODOEQUIPO));
   nuevo->datos = info;
   nuevo->siguiente = (*cabeza);
   nuevo->anterior = NULL;

   if ((*cabeza) != NULL)
      (*cabeza)->anterior = nuevo;

   (*cabeza) = nuevo;

   return;
}

/*
   Función     : listarEquipos
   Arrgumentos : NODOEQUIPO *equipos: lista donde están almacenados los equipos
                 int n: cantidad de clientes
                 int px: posción en x
                 int py: posición en y
                 int rango: cantidad de equipos mostrados en el menú de scroll
   Objetivo    : desplegar un menú con cursor para seleccionar un equipo
   Retorno     : (int) pos: equipo seleccionado
*/
int listarEquipos(NODOEQUIPO *equipos, int n, int px, int py, int rango)
{
   char tecla;
   int pos = 0, inf = 0, sup = rango;

   _setcursortype(FALSE);

   do {

      mostrarEquipos(equipos, n, px, py, pos, inf, sup);

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
   Función     : mostrarEquipos
   Arrgumentos : NODOEQUIPO *equipos: lista donde están almacenados los equipos
                 int n: cantidad de clientes
                 int px: posción en x
                 int py: posición en y
                 int inf: indica el primer equipo mostrado en la salida
                 int sup: indica el último equipo mostrado en la salida
   Objetivo    : mostrar los equipos
   Retorno     : ---
*/
void mostrarEquipos(NODOEQUIPO *equipos, int n, int px, int py, int actual, int inf, int sup)
{
   NODOEQUIPO *index = equipos;
   int cont, renglon;

   // se recorre la lista hasta el primer cliente que
   // se mostrará en el menú de scroll
   for (cont = 0; cont != inf; cont++)
      index = index->siguiente;

   gotoxy(px, py);
   setColor(WHITE, GREEN);
   printf("   ID    Descripci%cn            Inventario   Alquilados   Pr%cstamo   Costo        ", 162, 130);
   char espacio[] = "                                                                                  ";

   for (index, cont = inf, renglon = 0; cont <= sup && index != NULL; index = index->siguiente, cont++, renglon++)
   {
      gotoxy(px, py+renglon+2);
      setColor(BLUE, LIGHTGRAY);
      if (cont == actual)
         setColor(YELLOW, BLUE);
      printf("%s", espacio);
      gotoxy(px+1, py+renglon+2);
      printf("%s", index->datos.idequipo);
      gotoxy(px+9, py+renglon+2);
      printf("%s", index->datos.descripcion);
      gotoxy(px+32, py+renglon+2);
      printf("%d", index->datos.cantinventario);
      gotoxy(px+45, py+renglon+2);
      printf("%d", index->datos.cantprestados);
      gotoxy(px+58, py+renglon+2);
      printf("%.2f", index->datos.precioprestamo);
      gotoxy(px+69, py+renglon+2);
      printf("%.2f", index->datos.costoequipo);
   }

   defaultColor();

   return;
}

/*
   Función     : modificarInfoEquipos
   Arrgumentos : NODOCLIENTE *equipo: regerencia del equipo
                 int campo: indica el campo que se va a modificar
   Objetivo    : modificar un campo en la información del equipo
   Retorno     : ---
*/
void modificarInfoEquipos(NODOEQUIPO *equipos, int campo)
{
   int px = INIX+23, py = INIY+2+campo;

   if (campo == 0)
   {
      captureTextField(equipos->datos.idequipo, MAXIDEQUIPO-1, px, py, FALSE, TRUE);
   }
   if (campo == 1)
   {
      captureTextField(equipos->datos.descripcion, LENDESC-1, px, py, FALSE, FALSE);
   }
   if (campo == 2)
   {
      captureIntegerField(&equipos->datos.cantinventario, 10, px, py);
   }
   if (campo == 3)
   {
      captureNumericField(&equipos->datos.precioprestamo, 10, 2, px, py);
   }
   if (campo == 4)
   {
      captureNumericField(&equipos->datos.costoequipo, 10, 2, px, py);
   }
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
void captureIntegerField(int* num, int digits, int pos_x, int pos_y)
{
   int index = 0, n = digits, last = index;
   char key, *str;

   str = (char*)calloc(digits, sizeof(char));

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
   printf(" %d", *num);
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
void captureNumericField(float* num, int digits, int precision, int pos_x, int pos_y)
{
   int index = 0, n = digits, last = index, flag = FALSE;
   char key, *str;

   str = (char*)calloc(digits, sizeof(char));

   do {

      showField(str, index, n, pos_x, pos_y);

      do {
         key = getch();
      } while (!(key >= '0' && key <= '9') && (key != DOT && !flag) && key != ENTER
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
      else if (key == DOT)
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
         if (*(str+count) == DOT)
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
   printf(" %.2f", *num);
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
