/*
   Sistema de una empresa de alquiler de equipos que tiene clientes que pueden alquilar equipos
   para uno o varios proyectos. Permite ingresar/modificar/eliminar clientes, proyectos, equipos,
   los procesos de: conteo, despacho, devolución, generación de facturas, cuenta del cliente y
   cobros al cliente.

   Autor: Naoki Nakao
   Fecha: en curso
*/

#include <stdio.h>
#include "utils.h"

int main()
{
   srand(time(NULL));

   NODOPROYECTO *cabproyectos;
   PROYECTO proyecto;
   NODOPROPCONTRACTO *cabpropcontracto;
   PROPCONTRACTO propcontracto;
   FILE *archproyectos, *archpropocontractos;
   int index, cantproyectos, cantpropcontractos;

   char menuinicio[][MAXOPC] = {"Datos de clientes       ",
                                "Equipos en inventario   ",
                                "Proyectos               ",
                                "Cuentas de clientes     ",
                                "Propuestas de contrato  ",
                                "Despacho                ",
                                "Conteo                  ",
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
      // equipos en inventario
      else if (opcionini == 1)
      {
         opcionesEquipos(opcioncrud, ARCHEQUIPOS);
      }
      // proyectos
      else if (opcionini == 2)
      {
         cabproyectos = NULL, cabpropcontracto = NULL;

         // abriendo los archivos de que contienen la información de
         // los proyectos y propuestas de contractos

         if ((archproyectos = fopen(ARCHPROYECTOS, "rb")) != NULL)
         {
            cantproyectos = fsize(archproyectos)/sizeof(PROYECTO);
            for (index = 0; index < cantproyectos; index++)
            {
               fread(&proyecto, sizeof(PROYECTO), 1, archproyectos);
               insertarFrenteProyecto(&cabproyectos, proyecto);
            }
            fclose(archproyectos);
         }
         else if (opcioncrud != AGREGAR)
         {
            printf("No hay proyectos en marcha.");
            Sleep(DELAY);
            clrscr();
            continue;
         }

         if ((archpropocontractos) = fopen(ARCHPROPCONTRACTO, "rb") != NULL)
         {
            cantpropcontractos = fsize(archpropocontractos)/sizeof(PROPCONTRACTO);
            for (index = 0; index < cantpropcontractos; index++)
            {
               fread(&propcontracto, sizeof(PROPCONTRACTO), 1, archpropocontractos);
               insertarFrentePropcontracto(&cabpropcontracto, propcontracto);
            }
            fclose(archpropocontractos);
         }

         if (opcioncrud == AGREGAR)
         {
            proyecto = nuevoProyecto(cabproyectos, ARCHCLIENTES);
            clrscr();
         }
      }
   }

   return 0;
}















































