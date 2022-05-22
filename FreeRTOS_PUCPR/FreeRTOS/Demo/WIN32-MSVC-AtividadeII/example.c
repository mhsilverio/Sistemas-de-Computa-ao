#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Definindo o prot�tipo das tarefas 
void Socrates(void *pvParameters);
void Descartes(void *pvParameters);
void Aristoteles(void* pvParameters);
void Kant(void* pvParameters);
void Hegel(void* pvParameters);

void PegaGarfos(void* pvParameters);
void SoltaGarfo(void* pvParameters);

// Criando a vari�vel para o sem�foro
xSemaphoreHandle xSemaphore = NULL;

TaskHandle_t SocratesHandle = NULL;
TaskHandle_t DescartesHandle = NULL;
TaskHandle_t AristotelesHandle = NULL;
TaskHandle_t KantHandle = NULL;
TaskHandle_t HegelHandle = NULL;

int main_(void)
{
		// Funcao para criar um sem�foro Mutex
		xSemaphore = xSemaphoreCreateMutex();

		// Criando duas tarefas 
		xTaskCreate(Socrates, "Socrates", 1000, NULL, 1, &SocratesHandle);
		xTaskCreate(Descartes, "Descartes", 1000, NULL, 1, &DescartesHandle);
		xTaskCreate(Aristoteles, "Aristoteles", 1000, NULL, 1, &AristotelesHandle);
		xTaskCreate(Kant, "Kant", 1000, NULL, 1, &KantHandle);
		xTaskCreate(Hegel, "Hegel", 1000, NULL, 1, &HegelHandle);

		// Inicializa o escalonador
		vTaskStartScheduler();

	for (;; );
	return 0;
}

void PegaGarfos(void* pvParameters)
{

}

void SoltaGarfo(void* pvParameters)
{

}


void Socrates(void* pvParameters)
{
	for (;; )
	{
		// Verificando se o semaforo foi criado antes de utiliz�-lo
		if (xSemaphore != NULL) {

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				
				if () {
					vPrintString("\nSocrates esta comendo");
				} else vPrintString("\nSocrates esta pensando");
				
				// A funcao xSemaphoreGive() permite liberar o uso do sem�foro
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

	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
void Descartes(void* pvParameters)
{

	for (;; )
	{
		// Verificando se o sem�foro foi criado antes de utiliz�-lo
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				vPrintString("\nDecartes esta comendo");
				vPrintString("\nDecartes esta pensando");

				/*
				A fun��o xSemaphoreGive() permite liberar o uso do sem�foro
				*/
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

	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
void Aristoteles(void* pvParameters)
{

	for (;; )
	{
		// Verificando se o sem�foro foi criado antes de utiliz�-lo
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				vPrintString("\nAristoteles esta comendo");
				vPrintString("\nAristoteles esta pensando");

				/*
				A funcao xSemaphoreGive() permite liberar o uso do sem�foro
				*/
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

	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
void Kant(void* pvParameters)
{

	for (;; )
	{
		// Verificando se o semaforo foi criado antes de utiliz�-lo
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				vPrintString("\nKant esta comendo");
				vPrintString("\nKant esta pensando");

				/*
				A funcao xSemaphoreGive() permite liberar o uso do sem�foro
				*/
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

	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void Hegel(void* pvParameters)
{

	for (;; )
	{
		
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				vPrintString("\nHegel esta comendo");
				vPrintString("\nHegel esta pensando");
				/*
				A fun��o xSemaphoreGive() permite liberar o uso do sem�foro
				*/
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
	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
