#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Definindo o protótipo das tarefas 
void Socrates(void *pvParameters);
void Descartes(void *pvParameters);
void Aristoteles(void* pvParameters);
void Kant(void* pvParameters);
void Hegel(void* pvParameters);

void PegaGarfos(void* pvParameters);
void SoltaGarfo(void* pvParameters);

// Criando a variável para o semáforo
xSemaphoreHandle xSemaphore = NULL;

TaskHandle_t SocratesHandle = NULL;
TaskHandle_t DescartesHandle = NULL;
TaskHandle_t AristotelesHandle = NULL;
TaskHandle_t KantHandle = NULL;
TaskHandle_t HegelHandle = NULL;

int main_(void)
{
		// Função para criar um semáforo Mutex
		xSemaphore = xSemaphoreCreateMutex();

		// Criando duas tarefas 
		xTaskCreate(Socrates, "Socrates", 1000, NULL, 1, &SocratesHandle);
		xTaskCreate(Descartes, "Descartes", 1000, NULL, 1, &DescartesHandle);
		xTaskCreate(Aristoteles, "Aristoteles", 1000, NULL, 1, &AristotelesHandle);
		xTaskCreate(Kant, "Kant", 1000, NULL, 1, &KantHandle;
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
		// Verificando se o semáforo foi criado antes de utilizá-lo
		if (xSemaphore != NULL) {

			/* A função xSemaphoreTake() verifica se o semáforo está disponível, caso o semáforo esteja  disponível ele obtém o semáforo
			   Caso o semáforo estiver sendo utilizado este aguarde 10 ticks para ver o semáforo é liberado.
			   A função xSemaphoreTake() recebe dois parâmetros:
			   - O primeiro parâmetro corresponde ao semáforo
			   - O segundo parâmetro corresponde o tempo que a função deve aguardar caso o semáforo já esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				
				if () {
					vPrintString("\nSocrates esta comendo");
				} else vPrintString("\nSocrates esta pensando");
				
				// A função xSemaphoreGive() permite liberar o uso do semáforo
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
void Descartes(void* pvParameters)
{

	for (;; )
	{
		// Verificando se o semáforo foi criado antes de utilizá-lo
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				vPrintString("\nDecartes esta comendo");
				vPrintString("\nDecartes esta pensando");

				/*
				A função xSemaphoreGive() permite liberar o uso do semáforo
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
void Aristoteles(void* pvParameters)
{

	for (;; )
	{
		// Verificando se o semáforo foi criado antes de utilizá-lo
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				vPrintString("\nAristoteles esta comendo");
				vPrintString("\nAristoteles esta pensando");

				/*
				A função xSemaphoreGive() permite liberar o uso do semáforo
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
void Kant(void* pvParameters)
{

	for (;; )
	{
		// Verificando se o semáforo foi criado antes de utilizá-lo
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				vPrintString("\nKant esta comendo");
				vPrintString("\nKant esta pensando");

				/*
				A função xSemaphoreGive() permite liberar o uso do semáforo
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
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
				A função xSemaphoreGive() permite liberar o uso do semáforo
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 100 ticks
		vTaskDelay(portTICK_RATE_MS * 100);
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
