/**
 * @file example.c
 * @author Carlos Eduardo Marques Assuncao Torres - Engenharia de Computacao
 * @author Milena Heloisa de Amorim Silverio - Engenharia de Computacao
 * @author Ricardo Godoi Kurashiki - Engenharia de Computacao
 * @brief Implementacao do TDE01 para a materia de Sistemas de Computacao.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Definindo o prototipo das tarefas 
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);

// Criando variavel global para ser acessada pelas tasks
volatile char* display[20];

// Criando a variavel para o semaforo
xSemaphoreHandle xSemaphore = NULL;

int main_(void)
{
	// Funcao para criar um semaforo Mutex
	xSemaphore = xSemaphoreCreateMutex();

	// Criando tres tarefas com pilha de 1000 bytes, argumento com seus IDs e prioridade 1.
	xTaskCreate(vTask1, "Task 1", 1000, (void *)1, 1, NULL);
	xTaskCreate(vTask2, "Task 2", 1000, (void *)2, 1, NULL);
	xTaskCreate(vTask3, "Task 3", 1000, (void *)3, 1, NULL);

	// Inicializa o escalonador
	vTaskStartScheduler();

	for (;;);
	return 0;
}

// Implementacao da task 1
void vTask1(void* pvParameters)
{
	int idTarefa = (int)pvParameters;
	for (;;)
	{
		// Verificando se o semaforo foi criado antes de utiliza-lo
		if (xSemaphore != NULL) 
		{
			/* 
			   A funcao xSemaphoreTake() verifica se o semaforo esta disponavel, caso o semaforo esteja  disponivel ele obtem o semaforo
			   Caso o semaforo estiver sendo utilizado este aguarde 10 ticks para ver o semaforo e liberado.
			   A funcao xSemaphoreTake() recebe dois parametros:
			   - O primeiro parametro corresponde ao semaforo
			   - O segundo parametro corresponde o tempo que a funcao deve aguardar caso o semaforo ja esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) 
			{
				time_t segundos;
				time(&segundos);

				int dia = localtime(&segundos)->tm_mday;
				int mes = localtime(&segundos)->tm_mon + 1;
				int ano = localtime(&segundos)->tm_year + 1900;

				sprintf(display, "Task %ld - %d/%d/%d\n", idTarefa, dia, mes, ano);
				vPrintString(display);

				// A funcao xSemaphoreGive() permite liberar o uso do semaforo
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}

	// A funcao vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

// Implementacao da task 2
void vTask2(void* pvParameters)
{
	int idTarefa = (int)pvParameters;
	for (;; )
	{
		if (xSemaphore != NULL) 
		{
			/* 
			   A funcao xSemaphoreTake() verifica se o semaforo esta disponavel, caso o semaforo esteja  disponivel ele obtem o semaforo
			   Caso o semaforo estiver sendo utilizado este aguarde 10 ticks para ver o semaforo e liberado.
			   A funcao xSemaphoreTake() recebe dois parametros:
			   - O primeiro parametro corresponde ao semaforo
			   - O segundo parametro corresponde o tempo que a funcao deve aguardar caso o semaforo ja esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) 
			{
				time_t segundos;
				time(&segundos);

				int hora = localtime(&segundos)->tm_hour;
				int min = localtime(&segundos)->tm_min;
				int seg = localtime(&segundos)->tm_sec;

				sprintf(display, "Task %ld - %d:%d:%d\n", idTarefa, hora, min, seg);
				vPrintString(display);

				// A funcao xSemaphoreGive() permite liberar o uso do semaforo
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semaforo nao tenha sido criado
			printf("O semaforo nao foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}
	// A funcao vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

// Implementacao da task 3.
void vTask3(void* pvParameters)
{
	int idTarefa = (int)pvParameters;
	for (;; )
	{
		if (xSemaphore != NULL) 
		{
			/* 
			   A funcao xSemaphoreTake() verifica se o semaforo esta disponavel, caso o semaforo esteja  disponivel ele obtem o semaforo
			   Caso o semaforo estiver sendo utilizado este aguarde 10 ticks para ver o semaforo e liberado.
			   A funcao xSemaphoreTake() recebe dois parametros:
			   - O primeiro parametro corresponde ao semaforo
			   - O segundo parametro corresponde o tempo que a funcao deve aguardar caso o semaforo ja esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) 
			{
				float maxTemp = 40.0;
				float temp = ((float)rand() / (float)(RAND_MAX)* maxTemp);

				sprintf(display, "Task %ld - Curitiba %.2f*C\n", idTarefa, temp);
				vPrintString(display);

				// A funcao xSemaphoreGive() permite liberar o uso do semaforo
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semaforo nao tenha sido criado
			printf("O semaforo nao foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}
	// A funcao vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
