/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "utils.h"

//TODO
/*
 * Recibe un paquete a serializar, y un puntero a un int en el que dejar
 * el tamaño del stream de bytes serializados que devuelve
 */
void* serializar_paquete(t_paquete* paquete, int *bytes)
{
	*bytes = paquete->buffer->size + 2*sizeof(int);

	void *stream = malloc(*bytes);
	int offset = 0;

	memcpy(stream + offset, &(paquete->codigo_operacion), sizeof(int));
	offset += sizeof(int);
	memcpy(stream + offset, &(paquete->buffer->size), sizeof(int));
	offset += sizeof(int);
	memcpy(stream + offset, paquete->buffer->stream, paquete->buffer->size);

	return stream;
}

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

//TODO
void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);

	int* bytes_serializados;
	void* serializado = serializar_paquete(paquete, bytes_serializados);

	send(socket_cliente, serializado, *bytes_serializados, 0);

	free(serializado);
	eliminar_paquete(paquete);
}

//TODO
char* recibir_mensaje(int socket_cliente)
{

}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}
