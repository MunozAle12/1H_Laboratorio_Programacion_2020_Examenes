/*
 ============================================================================
 Name        : parcial1.c
 Author      : Ale Mu�oz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 Desarrollar en ANSI C:
 Una empresa requiere un sistema que le permita gestionar publicidad en sitios web,
 dicha publicidad podra ser visualizada en p�ginas web de terceros en forma de
 banners.

 Men� de la aplicacion:

 1) Alta de cliente: Se da de alta un cliente con nombre, apellido y cuit. Se generar�
    un ID �nico para este cliente que se imprimir� por pantalla si el alta es correcta.
 2) Modificar datos de cliente : Se ingresa el ID de cliente y se permitir� cambiar el
    nombre,el apellido y el cuit.
 3) Baja de cliente : Se ingresa el ID del cliente y se listar�n todas las publicaciones de
    dicho cliente. Luego se preguntar� si se quiere confirmar la eliminaci�n, la cual
    implicar� la eliminaci�n de todas las publicaciones y del cliente.
 4) Publicar: Permitir� crear un nuevo aviso. Primero imprime por pantalla la lista de
    clientes, luego se pedir�n los siguientes datos: ID de cliente, n�mero de rubro, texto
    del aviso (64 caracteres). Se generar� autom�ticamente un identificador num�rico
    para el aviso y se imprimir� en pantalla.
 5) Pausar publicaci�n: Se pedir� el ID de la publicaci�n y se imprimir� la informaci�n
    del cliente al que pertenece, luego se pedir� confirmaci�n para cambiarse de estado y
    se cambiar� al estado "pausada".
 6) Reanudar publicaci�n: Se pedir� el ID de la publicaci�n y se imprimir� la
    informaci�n del cliente al que pertenece, luego se pedir� confirmaci�n para cambiarse
    de estado y se cambiar� al estado "activa".
 7) Imprimir Clientes: Se imprimir� una lista de clientes con todos sus datos junto con
    la cantidad de avisos activos que posee.
 8) Imprimir publicaciones: Se imprimir� una lista de publicaciones con todos sus
    datos junto con el cuit del cliente correspondiente. se deber� indicar si est� activa o no
    con la palabras �ACTIVA� o �PAUSADA�.
 9) Informar clientes:
    a) Cliente con m�s avisos activos.
    b) Cliente con m�s avisos pausados.
    c) Cliente con m�s avisos.
 10) Informar publicaciones:
     a) Cantidad de publicaciones de un rubro: Se ingresar� el n�mero de rubro y se imprimir�
        la cantidad de publicaciones activas de dicho rubro.
     b) Rubro con m�s publicaciones activas.
     c) Rubro con menos publicaciones activas.

 Nota 0: El sistema soportar� una capacidad m�xima de 100 clientes y 1000
         publicaciones
 Nota 1: Se deber�n desarrollar bibliotecas por cada entidad las cuales contendr�n las funciones
         (Alta, Baja, Modificar, etc.). Los informes deber�n estar en una biblioteca aparte.
 Nota 2: El c�digo deber� tener comentarios con la documentaci�n de cada una de las
         funciones y respetar las reglas de estilo de la c�tedra.
 ============================================================================
*/
#include "Cliente.h"
#include "Publicacion.h"
#include "Informes.h"
#include "utn.h"

#include <stdio.h>
#include <stdlib.h>
#define CANTIDAD_CLIENTES 100
#define CANTIDAD_PUBLICACIONES 1000

int main(void)
{
	setbuf(stdout,NULL);
	Cliente arrayClientes[CANTIDAD_CLIENTES];
	Publicacion arrayPublicaciones[1000];
	int opcion;
	int idCliente = 0;
	int idPublicacion = 0;
	int auxiliarIndice;
	int auxiliarId;
	int auxIdCliente;
	int auxIndiceCliente;
	int auxRubro;
	char respuesta;

	if(!cli_inicializarArray(arrayClientes,CANTIDAD_CLIENTES))
	{
		printf("Array de clientes inicializado con �xito\n");
	}
	if(!pub_inicializarArray(arrayPublicaciones,CANTIDAD_PUBLICACIONES))
	{
		printf("Array de publicaciones inicializado con �xito\n\n");
	}

	cli_altaArrayDebug(arrayClientes,CANTIDAD_CLIENTES,0,&idCliente,"Facundo","Veron","30332455218");
	cli_altaArrayDebug(arrayClientes,CANTIDAD_CLIENTES,1,&idCliente,"Juliana","Vilchez","27232797219");
	cli_altaArrayDebug(arrayClientes,CANTIDAD_CLIENTES,2,&idCliente,"Diego","Silva","23299715032");
	cli_altaArrayDebug(arrayClientes,CANTIDAD_CLIENTES,3,&idCliente,"Hernan","Llorente","24347239906");
	cli_altaArrayDebug(arrayClientes,CANTIDAD_CLIENTES,4,&idCliente,"Paula","Luro","30325551291");
	cli_altaArrayDebug(arrayClientes,CANTIDAD_CLIENTES,5,&idCliente,"Silvana","Galvan","20273981014");

	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,0,&idPublicacion,120,"Ofertas en Kevingston",3,1);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,1,&idPublicacion,20,"Coca-Cola destap� felicidad",3,1);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,2,&idPublicacion,80,"Quedate en casa",3,1);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,3,&idPublicacion,110,"2x1 en McDonals",2,0);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,4,&idPublicacion,80,"Vacuna contra la gripe para grupos de riesgo",4,1);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,5,&idPublicacion,72,"Superfindesemana Coto: Los miercoles, 20% de descuento",0,1);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,6,&idPublicacion,10,"Contrat� Movistar Fibra",2,0);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,7,&idPublicacion,10,"Contrat� Fibertel",1,0);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,8,&idPublicacion,10,"Contrat� Claro: Conoc� nuestros planes de tel�fonos",2,1);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,9,&idPublicacion,120,"Adidas Impossible is Nothing",4,1);
	pub_altaArrayDebug(arrayPublicaciones,CANTIDAD_PUBLICACIONES,10,&idPublicacion,120,"Liquidacion oto�o invierno en Zara",3,1);

	do
	{
		if(!utn_getNumero(&opcion,"\nIngrese una opci�n:\n"
								  "1. Alta de cliente\n"
								  "2. Modificar datos del cliente\n"
								  "3. Baja de cliente\n"
								  "4. Publicar\n"
								  "5. Pausar publicaci�n\n"
								  "6. Reanudar publicaci�n\n"
								  "7. Imprimir clientes\n"
								  "8. Imprimir publicaciones\n"
								  "9. Informar clientes\n"
								  "10. Informar publicaciones\n"
								  "11. Salir\n\n",
								  "OPCION NO VALIDA. ",0,11,2))
		{
			switch(opcion)	//Ejecuto un caso dependiendo del valor de opcion
			{
				case 1:	//Alta de cliente
					auxiliarIndice = cli_getEmptyIndex(arrayClientes,CANTIDAD_CLIENTES);
					if( auxiliarIndice != -1 &&
						!cli_DarAltaCliente(arrayClientes,CANTIDAD_CLIENTES,auxiliarIndice,&idCliente) )	//Se solicita y verifica datos de cliente
					{
						printf("\n�El alta de cliente fue un �xito!\n");
					}
					else
					{
						printf("\nEl alta de cliente fall�.\n");
					}
					break;
				case 2:	//Modificar datos del cliente
					if(!utn_getNumero(&auxiliarId,"Ingrese ID de cliente a modificar: \n","\nINGRESO NO VALIDO. ",0,idCliente,2)) //Se solicita y valida ID cliente
					{
						auxiliarIndice = cli_buscarIdCliente(arrayClientes,CANTIDAD_CLIENTES,auxiliarId); //Se verifica existencia de cliente en el array
						if( auxiliarIndice != -1 &&
							!cli_modificarCliente(arrayClientes,CANTIDAD_CLIENTES,auxiliarIndice) )
						{
							printf("\n�La modificaci�n de datos fue un �xito!\n");
						}
						else
						{
							printf("\n�La modificaci�n de datos fall�!\n");
						}
					}
					else
					{
						printf("\n�Agot� sus reintentos. Ingreso incorrecto!\n");
					}
					break;
				case 3:	//Baja de cliente
					if(!utn_getNumero(&auxiliarId,"Ingrese ID de cliente a dar de baja: \n","\nINGRESO NO VALIDO. ",0,idCliente,2))	//Se solicita y valida ID cliente
					{
						auxiliarIndice = cli_buscarIdCliente(arrayClientes,CANTIDAD_CLIENTES,auxiliarId);	//Se verifica existencia de cliente en el array
						if(auxiliarIndice != -1)
						{
							pub_imprimirAvisosDeCliente(arrayPublicaciones,CANTIDAD_PUBLICACIONES,auxiliarId);
							if(!utn_getLetra(&respuesta,"\n�Quiere confirmar la eliminaci�n del cliente y sus publicaciones? [s/n]: \n","\nINGRESO NO V�LIDO. ",2))
							{
								if(respuesta=='s')
								{
									if( !cli_bajaCliente(arrayClientes,CANTIDAD_CLIENTES,auxiliarIndice) &&
										!pub_DarBajaAvisos(arrayPublicaciones,CANTIDAD_PUBLICACIONES,auxiliarId) )
									{
										printf("\n�La baja del cliente y sus publicaciones fue un �xito!\n");
									}
									else
									{
										printf("\n�La baja del cliente y sus publicaciones fall�!\n");
									}
								}
								else if(respuesta=='n')
								{
									printf("\n�La baja del cliente y sus publicaciones se cancel�!\n");
								}
								else
								{
									printf("\n�Respuesta incorrecta!\n");
								}
							}
							else
							{
								printf("\n�Agot� sus reintentos. Respuesta incorrecta!\n");
							}
						}
						else
						{
							printf("\n�El cliente no existe!\n");
						}
					}
					else
					{
						printf("\n�Agot� sus reintentos. Ingreso incorrecto!\n");
					}
					break;
				case 4: //Publicar
					auxiliarIndice = pub_getEmptyIndex(arrayPublicaciones,CANTIDAD_PUBLICACIONES);
					if(auxiliarIndice != -1)
					{
						if(!cli_imprimirClientes(arrayClientes,CANTIDAD_CLIENTES))
						{
							if(!utn_getNumero(&auxiliarId,"Ingrese ID de cliente: \n","\nINGRESO NO VALIDO. ",0,idCliente,2))	//Se solicita y valida ID cliente
							{
								if( cli_buscarIdCliente(arrayClientes,CANTIDAD_CLIENTES,auxiliarId) != -1 &&	//Se verifica existencia de cliente
									!pub_DarAltaAviso(arrayPublicaciones,CANTIDAD_PUBLICACIONES,auxiliarIndice,&idPublicacion,auxiliarId) )
								{
									printf("\n�La publicaci�n fue un �xito!\n");
								}
								else
								{
									printf("\n�La publicaci�n fall�!\n");
								}
							}
							else
							{
								printf("\n�Agot� sus reintentos. Ingreso incorrecto!\n");
							}
						}
						else
						{
							printf("\n�ERROR!\n");
						}
					}
					else
					{
						printf("\n�No hay lugar disponible!\n");
					}
					break;
				case 5: //Pausar publicaci�n
					if(!utn_getNumero(&auxiliarId,"Ingrese ID de publicaci�n: \n","\nINGRESO NO V�LIDO. ",0,idPublicacion,2))	//Se solicita y valida ID aviso
					{
						auxiliarIndice = pub_buscarIdAviso(arrayPublicaciones,CANTIDAD_PUBLICACIONES,auxiliarId);	//Se verifica existencia y ubicacion del aviso
						if(auxiliarIndice != -1)
						{
							auxIdCliente = arrayPublicaciones[auxiliarIndice].idCliente;	//Conociendo la ubicacion del aviso puedo saber el ID del cliente
							auxIndiceCliente = cli_buscarIdCliente(arrayClientes,CANTIDAD_CLIENTES,auxIdCliente); //Busco ubicacion del cliente en array
							if(auxIndiceCliente != 1)
							{
								if(cli_imprimir(&arrayClientes[auxIndiceCliente]) == -1) //Imprimo informaci�n del cliente
								{
									printf("\n�ERROR!\n");
								}
								if(!utn_getLetra(&respuesta,"\n�Desea pausar la publicaci�n? [s/n]: \n","\nINGRESO NO V�LIDO. ",2))
								{
									if(respuesta=='s')
									{
										if(pub_cambiarEstadoDeAviso(&arrayPublicaciones[auxiliarIndice]))
										{
											printf("\n�Se paus� la publicaci�n!\n");
										}
										else
										{
											printf("\n�ERROR!\n");
										}
									}
									else if(respuesta=='n')
									{
										printf("\n�Se cancel� el cambio de estado de publicaci�n!\n");
									}
									else
									{
										printf("\n�Respuesta incorrecta!\n");
									}
								}
								else
								{
									printf("\n�Agot� sus reintentos. Respuesta incorrecta!\n");
								}
							}
							else
							{
								printf("\nID Cliente no existe!\n");
							}
						}
						else
						{
							printf("\nID publicaci�n no existe!\n");
						}
					}
					else
					{
						printf("\n�Agot� sus reintentos. Ingreso incorrecto!\n");
					}
					break;
				case 6:	//Reanudar publicaci�n
					if(!utn_getNumero(&auxiliarId,"Ingrese ID de publicaci�n: \n","\nINGRESO NO V�LIDO. ",0,idPublicacion,2))	//Se solicita y valida ID aviso
					{
						auxiliarIndice = pub_buscarIdAviso(arrayPublicaciones,CANTIDAD_PUBLICACIONES,auxiliarId);	//Se verifica existencia y ubicacion del aviso
						if(auxiliarIndice != -1)
						{
							auxIdCliente = arrayPublicaciones[auxiliarIndice].idCliente;	//Conociendo la ubicacion del aviso puedo saber el ID del cliente
							auxIndiceCliente = cli_buscarIdCliente(arrayClientes,CANTIDAD_CLIENTES,auxIdCliente);	//Busco ubicacion del cliente en array
							if(auxIndiceCliente != 1)
							{
								if(cli_imprimir(&arrayClientes[auxIndiceCliente]) == -1)	//Imprimo informaci�n del cliente
								{
									printf("\n�ERROR!\n");
								}
								if(!utn_getLetra(&respuesta,"\n�Desea reanudar la publicaci�n? [s/n]: \n","\nINGRESO NO V�LIDO. ",2))
								{
									if(respuesta=='s')
									{
										if(pub_cambiarEstadoDeAviso(&arrayPublicaciones[auxiliarIndice]))
										{
											printf("\n�Se reanud� la publicaci�n!\n");
										}
										else
										{
											printf("\n�ERROR!\n");
										}
									}
									else if(respuesta=='n')
									{
										printf("\n�Se cancel� el cambio de estado de publicaci�n!\n");
									}
									else
									{
										printf("\n�Respuesta incorrecta!\n");
									}
								}
								else
								{
									printf("\n�Agot� sus reintentos. Respuesta incorrecta!\n");
								}
							}
							else
							{
								printf("\nID Cliente no existe!\n");
							}
						}
						else
						{
							printf("\nID publicaci�n no existe!\n");
						}
					}
					else
					{
						printf("\n�Agot� sus reintentos. Ingreso incorrecto!\n");
					}
					break;
				case 7:	//Imprimir clientes con la cantidad de avisos activos que poseen
					if(info_informarClientesConAvisosActivos(arrayClientes,CANTIDAD_CLIENTES,arrayPublicaciones,CANTIDAD_PUBLICACIONES) == -1)
					{
						printf("\n�ERROR\n");
					}
					break;
				case 8:	//Imprimir publicaciones junto con el cuit del cliente correspondiente
					if(info_informarAvisosConCuit(arrayPublicaciones,CANTIDAD_PUBLICACIONES,arrayClientes,CANTIDAD_CLIENTES) == -1)
					{
						printf("\n�ERROR!\n");
					}
					break;
				case 9:	//Informar clientes: Cliente con m�s avisos activos. Cliente con m�s avisos pausados. Cliente con m�s avisos.
					if(info_informarClienteConAvisosMax(arrayPublicaciones,CANTIDAD_PUBLICACIONES,arrayClientes,CANTIDAD_CLIENTES) == -1)
					{
						printf("\n�ERROR!\n");
					}
					if(info_informarClientesConAvisosActivosMax(arrayPublicaciones,CANTIDAD_PUBLICACIONES,arrayClientes,CANTIDAD_CLIENTES) == -1)
					{
						printf("\n�ERROR!\n");
					}
					if(info_informarClientesConAvisosPausadosMax(arrayPublicaciones,CANTIDAD_PUBLICACIONES,arrayClientes,CANTIDAD_CLIENTES) == -1)
					{
						printf("\n�ERROR!\n");
					}
					break;
				case 10: //Informar publicaciones
					if(!utn_getNumero(&auxRubro,"Ingresar n�mero de rubro: \n","\nINGRESO NO VALIDO. ",0,1000,2))	//Solicito y valido numero de rubro
					{
						if(pub_buscarRubro(arrayPublicaciones,CANTIDAD_PUBLICACIONES,auxRubro) != -1)	//Verifico que el rubro exista en array publicaciones
						{
							info_informarAvisosActivosDeRubro(arrayPublicaciones,CANTIDAD_PUBLICACIONES,auxRubro);
						}
						else
						{
							printf("\nEl rubro no existe!\n");
						}
						if(info_informarRubroConMasAvisosActivos(arrayPublicaciones,CANTIDAD_PUBLICACIONES) == -1)
						{
							printf("\n�ERROR!\n");
						}
						if(info_informarRubroConMenosAvisosActivos(arrayPublicaciones,CANTIDAD_PUBLICACIONES) == -1)
						{
							printf("\n�ERROR!\n");
						}
					}
					break;
			}
		}
		else
		{
			printf("ERROR. \n");
		}
	}while(opcion != 11);	//Se termina la ejecucion del programa ingresando la opcion 11
	return EXIT_SUCCESS;
}
