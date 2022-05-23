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

// Definindo o prot�tipo das tarefas 
void Socrates(void *pvParameters);
void Descartes(void *pvParameters);
void Aristoteles(void* pvParameters);
void Kant(void* pvParameters);
void Hegel(void* pvParameters);
void mostraEstados(void *pvParameters);

// Criando a vari�vel para o sem�foro
xSemaphoreHandle garSH = NULL; // Garfo entre Socrates e Hegel
xSemaphoreHandle garSD = NULL; // Garfo entre Socrates e Descartes
xSemaphoreHandle garDA = NULL; // Garfo entre Descartes e Aristoteles
xSemaphoreHandle garAK = NULL; // Garfo entre Aristoteles e Kant
xSemaphoreHandle garKH = NULL; // Garfo entre Kant e Hegel
xSemaphoreHandle estados = NULL;

int socratesComendo = 0;
int descartesComendo = 0;
int aristotelesComendo = 0;
int kantComendo = 0;
int hegelComendo = 0;

TaskHandle_t SocratesHandle = NULL;
TaskHandle_t DescartesHandle = NULL;
TaskHandle_t AristotelesHandle = NULL;
TaskHandle_t KantHandle = NULL;
TaskHandle_t HegelHandle = NULL;
TaskHandle_t Estados = NULL;

int main_(void)
{
	// Funcao para criar um sem�foro Mutex
	garSH = xSemaphoreCreateMutex();
	garSD = xSemaphoreCreateMutex();
	garDA = xSemaphoreCreateMutex();
	garAK = xSemaphoreCreateMutex();
	garKH = xSemaphoreCreateMutex();
	estados = xSemaphoreCreateMutex();

	// Criando duas tarefas 
	xTaskCreate(Socrates, "Socrates", 1000, NULL, 1, &SocratesHandle);
	xTaskCreate(Descartes, "Descartes", 1000, NULL, 1, &DescartesHandle);
	xTaskCreate(Aristoteles, "Aristoteles", 1000, NULL, 1, &AristotelesHandle);
	xTaskCreate(Kant, "Kant", 1000, NULL, 1, &KantHandle);
	xTaskCreate(Hegel, "Hegel", 1000, NULL, 1, &HegelHandle);
	//xTaskCreate(estados, "Estados", 1000, NULL, 1, &Estados);

	// Inicializa o escalonador
	vTaskStartScheduler();

	for (;; );
	return 0;
}

void mostraEstados(void *pvParameters)
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
}

void Socrates(void* pvParameters)
{
	for (;; )
	{
		// Verificando se o semaforo foi criado antes de utiliz�-lo
		if (garSH != NULL && garSD != NULL) {

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(garSH, (portTickType)10) == pdTRUE &&
				xSemaphoreTake(garSD, (portTickType)10) == pdTRUE) 
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					socratesComendo = 1;
					xSemaphoreGive(estados);
				}
				
				// A funcao xSemaphoreGive() permite liberar o uso do sem�foro
				vTaskDelay(portTICK_RATE_MS * 50);
				xSemaphoreGive(garSH);
				xSemaphoreGive(garSD);
			}
			else
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					socratesComendo = 0;
					xSemaphoreGive(estados);
				}
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
		// Verificando se o semaforo foi criado antes de utiliz�-lo
		if (garSD != NULL && garDA != NULL) {

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(garSD, (portTickType)10) == pdTRUE &&
				xSemaphoreTake(garDA, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					descartesComendo = 1;
					xSemaphoreGive(estados);
				}

				// A funcao xSemaphoreGive() permite liberar o uso do sem�foro
				vTaskDelay(portTICK_RATE_MS * 1000);
				xSemaphoreGive(garSD);
				xSemaphoreGive(garDA);
			}
			else
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					descartesComendo = 0;
					xSemaphoreGive(estados);
				}
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
		// Verificando se o semaforo foi criado antes de utiliz�-lo
		if (garDA != NULL && garAK != NULL) {

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(garDA, (portTickType)10) == pdTRUE &&
				xSemaphoreTake(garAK, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					aristotelesComendo = 1;
					xSemaphoreGive(estados);
				}
				// A funcao xSemaphoreGive() permite liberar o uso do sem�foro
				vTaskDelay(portTICK_RATE_MS * 100);
				xSemaphoreGive(garDA);
				xSemaphoreGive(garAK);
			}
			else
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					aristotelesComendo = 0;
					xSemaphoreGive(estados);
				}
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
		if (garAK != NULL && garKH != NULL) {

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(garAK, (portTickType)10) == pdTRUE &&
				xSemaphoreTake(garKH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					kantComendo = 1;
					xSemaphoreGive(estados);
				}
				// A funcao xSemaphoreGive() permite liberar o uso do sem�foro
				vTaskDelay(portTICK_RATE_MS * 200);
				xSemaphoreGive(garAK);
				xSemaphoreGive(garKH);
			}
			else
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					kantComendo = 0;
					xSemaphoreGive(estados);
				}
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
		// Verificando se o semaforo foi criado antes de utiliz�-lo
		if (garKH != NULL && garSH != NULL) {

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(garKH, (portTickType)10) == pdTRUE &&
				xSemaphoreTake(garSH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					hegelComendo = 1;
					xSemaphoreGive(estados);
				}
				// A funcao xSemaphoreGive() permite liberar o uso do sem�foro
				vTaskDelay(portTICK_RATE_MS * 400);
				xSemaphoreGive(garKH);
				xSemaphoreGive(garSH);
			}
			else
			{
				if (xSemaphoreTake(estados, (portTickType)10) == pdTRUE)
				{
					hegelComendo = 0;
					xSemaphoreGive(estados);
				}
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
