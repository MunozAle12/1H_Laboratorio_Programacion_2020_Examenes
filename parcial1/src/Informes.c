/*
 * Informes.c
 *
 *  Created on: 7 may. 2020
 *      Author: Usuario
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "Publicacion.h"
#include "Informes.h"
#include "utn.h"
static const char ESTADOS_TIPOS[2][8]={"PAUSADA","ACTIVA"};

/**
 * \brief Imprime los datos de un cliente junto con la cantidad de avisos
 * \param pElemento Puntero al elemento del array que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_imprimirClienteConCantidadAvisos(Cliente* pElemento,int* totalAvisos)
{
	int retorno = -1;
	if(pElemento != NULL)
	{
		retorno = 0;
		printf("\nID: %d - Nombre: %s - Apellido: %s - CUIT: %s - Avisos: %d\n",pElemento->idCliente,pElemento->nombre,pElemento->apellido,pElemento->cuit,*totalAvisos);
	}
	return retorno;
}
/**
 * \brief Busca e informa lista de clientes junto con la cantidad de avisos activos
 * \param arrayClientes Puntero al espacio de memoria donde comienza el array a ser actualizado
 * \param limiteClientes Tamaño del array de clientes
 * \param arrayPublicaciones Puntero al espacio de memoria donde comienza el array a ser actualizado
 * \param limitePublicaciones Tamaño del array de publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_informarClientesConAvisosActivos(Cliente* arrayClientes,int limiteClientes,Publicacion* arrayPublicaciones,int limitePublicaciones)
{
	int respuesta = -1;
	int i;
	int avisosActivos;
	if(arrayClientes!=NULL && limiteClientes>0 && arrayPublicaciones!=NULL && limitePublicaciones>0)
	{
		for(i=0; i<limiteClientes; i++)
		{
			if(arrayClientes[i].isEmpty != 1)
			{
				avisosActivos = pub_calcularAvisosActivosDeCliente(arrayPublicaciones,limitePublicaciones,arrayClientes[i].idCliente);
				if(avisosActivos != -1)
				{
					respuesta = 0;
					info_imprimirClienteConCantidadAvisos(&arrayClientes[i],&avisosActivos);
				}
			}
		}
	}
	return respuesta;
}

/**
 * \brief Imprime los datos de una publicacion junto con CUIT del cliente correspondiente
 * \param pElementoAviso Puntero al elemento del array que se busca imprimir
 * \param pElementoCliente Puntero al elemento del array que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_imprimirAvisoConCuit(Publicacion* pElementoAviso,Cliente* pElementoCliente)
{
	int retorno = -1;
	if(pElementoAviso!=NULL)
	{
		retorno=0;
		printf("\nID Publicacion: %d - Rubro: %d - Aviso: %s - Estado: %s - IdCliente: %d - CUIT: %s\n",pElementoAviso->idPublicacion,pElementoAviso->rubro,pElementoAviso->txtAviso,ESTADOS_TIPOS[pElementoAviso->estado],pElementoAviso->idCliente,pElementoCliente->cuit);
	}
	return retorno;
}
/**
 * \brief Busca e informa publicaciones con todos sus datos junto con el cuit del cliente correspondiente
 * \param arrayPublicaciones Puntero a espacio de memoria donde comienza el array a ser actualizado
 * \param limitePublicaciones Tamaño del array publicaciones
 * \param arrayClientes Puntero a espacio de memoria donde comienza el array a ser actualizado
 * \param limiteClientes Tamaño del array de clientes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_informarAvisosConCuit(Publicacion* arrayPublicaciones,int limitePublicaciones,Cliente* arrayClientes,int limiteClientes)
{
	int respuesta = -1;
	int i;
	int auxiliarIndiceCliente;
	if(arrayPublicaciones != NULL && limitePublicaciones > 0)
	{
		for(i=0; i<limitePublicaciones; i++)
		{
			if(arrayPublicaciones[i].isEmpty == 0)
			{
				auxiliarIndiceCliente = cli_buscarIdCliente(arrayClientes,limiteClientes,arrayPublicaciones[i].idCliente);
				if(auxiliarIndiceCliente != -1)
				{
					respuesta = 0;
					info_imprimirAvisoConCuit(&arrayPublicaciones[i],&arrayClientes[auxiliarIndiceCliente]);
				}
			}
		}
	}
	return respuesta;
}
/**
 * \brief Busca e informa cliente con mayor cantidad de avisos
 * \param arrayPublicaciones Array de publicaciones a ser analizado
 * \param limitePublicaciones Tamaño del array de publicaciones
 * \param arrayClientes Array de clientes a ser analizado
 * \param limiteClientes Tamaño del array de clientes
 * \return Retorna 0 (EXITO), -1 (ERROR)
 *
 */
int info_informarClienteConAvisosMax(Publicacion* arrayPublicaciones,int limitePublicaciones,Cliente* arrayClientes,int limiteClientes)
{
	int respuesta = -1;
	int cantidadAvisos;
	int cantidadAvisosMax;
	Cliente clienteConMasAvisos;
	int i;
	if(arrayClientes!=NULL && limiteClientes>0 && arrayPublicaciones!=NULL && limitePublicaciones>0)
	{
		for(i=0; i<limiteClientes; i++)
		{
			if(arrayClientes[i].isEmpty != 1)
			{
				cantidadAvisos = pub_calcularAvisosDeCliente(arrayPublicaciones,limitePublicaciones,arrayClientes[i].idCliente);
				if( cantidadAvisos!= -1 &&
					(i==0 || cantidadAvisos > cantidadAvisosMax) )
				{
					respuesta = 0;
					clienteConMasAvisos = arrayClientes[i];
					cantidadAvisosMax = cantidadAvisos;
				}
			}
		}
		printf("\nCliente con mas avisos:\n");
		info_imprimirClienteConCantidadAvisos(&clienteConMasAvisos,&cantidadAvisosMax);
		pub_imprimirAvisosDeCliente(arrayPublicaciones,limitePublicaciones,clienteConMasAvisos.idCliente);
	}
	return respuesta;
}
/**
 * \brief Busca e informa los clientes con mayor cantidad de avisos ACTIVOS
 * \param arrayPublicaciones Array de publicaciones a ser analizado
 * \param limitePublicaciones Tamaño del array de publicaciones
 * \param arrayClientes Array de clientes a ser analizado
 * \param limiteClientes Tamaño del array de clientes
 * \return Retorna 0 (EXITO), -1 (ERROR)
 *
 */
int info_informarClientesConAvisosActivosMax(Publicacion* arrayPublicaciones,int limitePublicaciones,Cliente* arrayClientes,int limiteClientes)
{
	int respuesta = -1;
	int cantidadAvisos;
	int cantidadAvisosMax;
	Cliente clienteConMasAvisos;
	int i;
	if(arrayClientes!=NULL && limiteClientes>0 && arrayPublicaciones!=NULL && limitePublicaciones>0)
	{
		for(i=0; i<limiteClientes; i++)
		{
			if(arrayClientes[i].isEmpty != 1)
			{
				cantidadAvisos = pub_calcularAvisosActivosDeCliente(arrayPublicaciones,limitePublicaciones,arrayClientes[i].idCliente);
				if( cantidadAvisos != -1 &&
					(i==0 || cantidadAvisos > cantidadAvisosMax) )
				{
					respuesta = 0;
					clienteConMasAvisos = arrayClientes[i];
					cantidadAvisosMax = cantidadAvisos;
				}
			}
		}
		printf("\nCliente con mas avisos activos:\n");
		info_imprimirClienteConCantidadAvisos(&clienteConMasAvisos,&cantidadAvisosMax);
		pub_imprimirAvisosDeCliente(arrayPublicaciones,limitePublicaciones,clienteConMasAvisos.idCliente);
	}
	return respuesta;
}
/**
 * \brief Busca e informa los clientes con mayor cantidad de avisos PAUSADOS
 * \param arrayPublicaciones Array de publicaciones a ser analizado
 * \param limitePublicaciones Tamaño del array de publicaciones
 * \param arrayClientes Array de clientes a ser analizado
 * \param limiteClientes Tamaño del array de clientes
 * \return Retorna 0 (EXITO), -1 (ERROR)
 *
 */
int info_informarClientesConAvisosPausadosMax(Publicacion* arrayPublicaciones,int limitePublicaciones,Cliente* arrayClientes,int limiteClientes)
{
	int respuesta = -1;
	int cantidadAvisos;
	int cantidadAvisosMax;
	Cliente clienteConMasAvisos;
	int i;
	if(arrayClientes!=NULL && limiteClientes>0 && arrayPublicaciones!=NULL && limitePublicaciones>0)
	{
		for(i=0; i<limiteClientes; i++)
		{
			if(arrayClientes[i].isEmpty != 1)
			{
				cantidadAvisos = pub_calcularAvisosPausadosDeCliente(arrayPublicaciones,limitePublicaciones,arrayClientes[i].idCliente);
				if( cantidadAvisos != -1 &&
					(i==0 || cantidadAvisos > cantidadAvisosMax) )
				{
					respuesta = 0;
					clienteConMasAvisos = arrayClientes[i];
					cantidadAvisosMax = cantidadAvisos;
				}
			}
		}
		printf("\nCliente con mas avisos pausados:\n");
		info_imprimirClienteConCantidadAvisos(&clienteConMasAvisos,&cantidadAvisosMax);
		pub_imprimirAvisosDeCliente(arrayPublicaciones,limitePublicaciones,clienteConMasAvisos.idCliente);
	}
	return respuesta;
}
/**
 * \brief Busca e informa los avisos activos de un rubro
 * \param array Array de publicaciones a ser actualizada
 * \param limite Limite de array publicaciones
 * \param rubroBuscado Valor del rubro a ser buscado
 * \return Retorna 0 (EXITO), -1 (ERROR)
 *
 */
int info_informarAvisosActivosDeRubro(Publicacion* array,int limite,int rubroBuscado)
{
	int respuesta = -1;
	int cantidadAvisos;
	if(array != NULL && limite >= 0 && rubroBuscado > 0)
	{
		cantidadAvisos = pub_calcularAvisosActivosDeRubro(array,limite,rubroBuscado);
		if(cantidadAvisos != -1)
		{
			respuesta = 0;
			printf("\nLa cantidad de avisos activos del rubro %d es: %d\n",rubroBuscado,cantidadAvisos);
			pub_imprimirAvisosPorRubro(array,limite,rubroBuscado);
		}
	}
	return respuesta;
}
/**
 * Busca e informa el rubro con mas avisos activos
 * \param array Array de publicaciones a ser actualizada
 * \param limite Limite de array publicaciones
 * \return Retorna 0 (EXITO), -1 (ERROR)
 *
 */
int info_informarRubroConMasAvisosActivos(Publicacion* array,int limite)
{
	int respuesta = -1;
	int i;
	int cantidadAvisos;
	int cantidadAvisosMax;
	int rubroConMasAvisos;
	if(array != NULL && limite >= 0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty != 1 && array[i].estado == ESTADO_ACTIVO)
			{
				cantidadAvisos = pub_calcularAvisosActivosDeRubro(array,limite,array[i].rubro);
				if( cantidadAvisos != -1 &&
					(i==0 || cantidadAvisos > cantidadAvisosMax) )
				{
					respuesta = 0;
					rubroConMasAvisos = array[i].rubro;
					cantidadAvisosMax = cantidadAvisos;
				}
			}
		}
		printf("\nRubro con mas avisos activos: %d - Total avisos: %d\n",rubroConMasAvisos,cantidadAvisosMax);
		pub_imprimirAvisosPorRubro(array,limite,rubroConMasAvisos);
	}
	return respuesta;
}
/**
 * \brief Busca e informa el rubro con menos avisos activos
 * \param array Array de publicaciones a ser actualizada
 * \param limite Tamaño de array publicaciones
 * \return Retorna 0 (EXITO), -1 (ERROR)
 *
 */
int info_informarRubroConMenosAvisosActivos(Publicacion* array,int limite)
{
	int respuesta = -1;
	int i;
	int cantidadAvisos;
	int cantidadAvisosMin;
	int rubroConMenosAvisos;
	if(array != NULL && limite >= 0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty != 1 && array[i].estado == ESTADO_ACTIVO)
			{
				cantidadAvisos = pub_calcularAvisosActivosDeRubro(array,limite,array[i].rubro);
				if( cantidadAvisos != -1 &&
					(i==0 || cantidadAvisos < cantidadAvisosMin) )
				{
					respuesta = 0;
					rubroConMenosAvisos = array[i].rubro;
					cantidadAvisosMin = cantidadAvisos;
				}
			}
		}
		printf("\nRubro con menos avisos activos: %d - Total avisos: %d\n",rubroConMenosAvisos,cantidadAvisosMin);
		pub_imprimirAvisosPorRubro(array,limite,rubroConMenosAvisos);
	}
	return respuesta;
}
