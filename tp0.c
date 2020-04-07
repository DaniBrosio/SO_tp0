/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* respuesta;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	//Loggear "soy un log"
	log_info(logger,"soy un log");

	config = leer_config();

	//Aplicar configuraciones
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");

	printf("Direccion: %s:%s", ip, puerto);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	conexion = crear_conexion(ip, puerto);

	//enviar mensaje
	enviar_mensaje("holis",conexion);

	//recibir mensaje
	respuesta = recibir_mensaje(conexion);
	log_info(logger,"<respuesta>");

	//loguear mensaje recibido

	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	return log_create("tp0.log", "tp0", 1, LOG_LEVEL_INFO);
}

//TODO
t_config* leer_config(void)
{
	return config_create("tp0.config");
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}
