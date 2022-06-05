#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Alunos:
// Carlos Eduardo Marques Assunção Torres
// Milena Heloísa de Silvério Amorim
// Ricardo Godoi Kurashiki
// Engenharia de Comuputacao - 7 periodo
// Sistemas de computacao

// Definindo o prototipo das tarefas 
void Socrates(void* pvParameters);
void Descartes(void* pvParameters);
void Aristoteles(void* pvParameters);
void Kant(void* pvParameters);
void Hegel(void* pvParameters);
void mostraEstados(void* pvParameters);

// Criando a variavel para o semaforo
xSemaphoreHandle garSH = NULL; // Garfo entre Socrates e Hegel
xSemaphoreHandle garSD = NULL; // Garfo entre Socrates e Descartes
xSemaphoreHandle garDA = NULL; // Garfo entre Descartes e Aristoteles
xSemaphoreHandle garAK = NULL; // Garfo entre Aristoteles e Kant
xSemaphoreHandle garKH = NULL; // Garfo entre Kant e Hegel
xSemaphoreHandle estados = NULL;

volatile int socratesComendo = 0;
volatile int descartesComendo = 0;
volatile int aristotelesComendo = 0;
volatile int kantComendo = 0;
volatile int hegelComendo = 0;

TaskHandle_t SocratesHandle = NULL;
TaskHandle_t DescartesHandle = NULL;
TaskHandle_t AristotelesHandle = NULL;
TaskHandle_t KantHandle = NULL;
TaskHandle_t HegelHandle = NULL;

int main_(void)
{
	// Funcao para criar um semaforo Mutex
	garSH = xSemaphoreCreateMutex();
	garSD = xSemaphoreCreateMutex();
	garDA = xSemaphoreCreateMutex();
	garAK = xSemaphoreCreateMutex();
	garKH = xSemaphoreCreateMutex();
	estados = xSemaphoreCreateMutex();

	// Criando tarefas 
	xTaskCreate(Socrates, "Socrates", 500, NULL, 1, &SocratesHandle);
	xTaskCreate(Descartes, "Descartes", 500, NULL, 1, &DescartesHandle);
	xTaskCreate(Aristoteles, "Aristoteles", 500, NULL, 1, &AristotelesHandle);
	xTaskCreate(Kant, "Kant", 500, NULL, 1, &KantHandle);
	xTaskCreate(Hegel, "Hegel", 500, NULL, 1, &HegelHandle);
	xTaskCreate(mostraEstados, "Estados", 500, NULL, 1, NULL);

	// Inicializa o escalonador
	vTaskStartScheduler();

	for (;; );
	return 0;
}

void mostraEstados(void* pvParameters)
{
	for (;;)
	{
		if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
		{
			if (socratesComendo == 1)
				vPrintString("Socrates esta comendo\n");
			else
				vPrintString("Socrates esta pensando\n");

			if (descartesComendo == 1)
				vPrintString("Descartes esta comendo\n");
			else
				vPrintString("Descartes esta pensando\n");

			if (aristotelesComendo == 1)
				vPrintString("Aristoteles esta comendo\n");
			else
				vPrintString("Aristoteles esta pensando\n");

			if (kantComendo == 1)
				vPrintString("Kant esta comendo\n");
			else
				vPrintString("Kant esta pensando\n");

			if (hegelComendo == 1)
				vPrintString("Hegel esta comendo\n");
			else
				vPrintString("Hegel esta pensando\n");

			vPrintString("\n");
			xSemaphoreGive(estados);
		}

		vTaskDelay(portTICK_RATE_MS * 500);
	}

	vTaskDelete(NULL);
}

void Socrates(void* pvParameters)
{
	for (;; )
	{
		if (garSH != NULL && garSD != NULL) 
		{
			if (xSemaphoreTake(garSH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garSD, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						socratesComendo = 1;
						xSemaphoreGive(estados);
					}

					vTaskDelay(portTICK_RATE_MS * 250);

					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						socratesComendo = 0;
						xSemaphoreGive(estados);
					}
					
					xSemaphoreGive(garSD);
				}

				xSemaphoreGive(garSH);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 50);
	}

	vTaskDelete(NULL);
}
void Descartes(void* pvParameters)
{
	for (;; )
	{
		if (garSD != NULL && garDA != NULL) 
		{
			if (xSemaphoreTake(garSD, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garDA, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						descartesComendo = 1;
						xSemaphoreGive(estados);
					}
					
					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						descartesComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garDA);
				}

				xSemaphoreGive(garSD);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 100);
	}

	vTaskDelete(NULL);
}
void Aristoteles(void* pvParameters)
{
	for (;; )
	{
		if (garDA != NULL && garAK != NULL) 
		{
			if (xSemaphoreTake(garDA, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garAK, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						aristotelesComendo = 1;
						xSemaphoreGive(estados);
					}
					
					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						aristotelesComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garAK);
				}

				xSemaphoreGive(garDA);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 150);
	}

	vTaskDelete(NULL);
}
void Kant(void* pvParameters)
{
	for (;; )
	{
		if (garAK != NULL && garKH != NULL) {
			if (xSemaphoreTake(garAK, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garKH, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						kantComendo = 1;
						xSemaphoreGive(estados);
					}
					vTaskDelay(portTICK_RATE_MS * 250);

					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						kantComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garKH);
				}

				xSemaphoreGive(garAK);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 200);
	}
	vTaskDelete(NULL);
}

void Hegel(void* pvParameters)
{
	for (;; )
	{
		if (garKH != NULL && garSH != NULL) {
			if (xSemaphoreTake(garKH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garSH, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						hegelComendo = 1;
						xSemaphoreGive(estados);
					}

					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						hegelComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garSH);
				}
				xSemaphoreGive(garKH);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 250);
	}
	vTaskDelete(NULL);
}
