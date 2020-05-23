/*
 * cliente.h
 *
 *  Created on: 28 abr. 2020
 *      Author: Usuario
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define NOMBRE_LEN 64
#define APELLIDO_LEN 64
#define CUIT_LEN 32

struct cliente
{
	char nombre[NOMBRE_LEN];
	char apellido[APELLIDO_LEN];
	char cuit[CUIT_LEN];
	int idCliente;
	int isEmpty;
}typedef Cliente;

int cli_imprimir(Cliente* pElemento);
int cli_imprimirClientes(Cliente* array,int limite);
int cli_inicializarArray(Cliente* array,int limite);
int cli_getEmptyIndex(Cliente* array,int limite);
int cli_DarAltaCliente(Cliente* array,int limite,int indice, int* id);
int cli_modificarCliente(Cliente* array,int limite,int indice);
int cli_buscarIdCliente(Cliente array[],int limite,int valorBuscado);
int cli_buscarCuit(Cliente* array,int limite,char* valorBuscado);
int cli_bajaCliente(Cliente* array,int limite,int indice);

int cli_altaArrayDebug(Cliente* array,int limite,int indice,int* idCliente,char* nombre,char* apellido,char* cuit);

#endif /* CLIENTE_H_ */
