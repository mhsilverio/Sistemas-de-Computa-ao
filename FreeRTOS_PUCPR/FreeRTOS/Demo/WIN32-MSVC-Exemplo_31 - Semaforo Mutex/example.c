#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "basic_io.h"

void vTaskGreen(void *pvParameters);
void vTaskYellow(void *pvParameters);
void vTaskRed(void *pvParameters);

// Criando a variável para o semáforo
xSemaphoreHandle xSemaphore = NULL;

// Criando uma variável buffer para manipular a mensagem do sinaleiro 
char sinal[100];

int main_(void)
{
	    // Função para criar um semáforo binário
	    xSemaphore = xSemaphoreCreateMutex();
		
		// Criando uma tarefa para cada um das cores do sinaleiro
		xTaskCreate(vTaskGreen, "Task Green", 1000, NULL, 1, NULL);
		xTaskCreate(vTaskYellow, "Task Yellow", 1000, NULL, 1, NULL);
		xTaskCreate(vTaskRed, "Task Red", 1000, NULL, 1, NULL);

		// Iniciando o escalonador de tarefas
		vTaskStartScheduler();

	for (;; );
	return 0;
}

void vTaskGreen(void* pvParameters)
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

				//Adiciona conteúdo na variável display
				sprintf(sinal, "Task Green\n");
				//Imprime o conteúdo do display na saída do console
				vPrintString(sinal);

				/*
				A função xSemaphoreGive() permite liberar o uso do semáforo
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			vPrintString("O semaforo não foi criado!\n");
		}
		vTaskDelay(portTICK_RATE_MS * 1000);
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}


void vTaskYellow(void* pvParameters)
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

				//Adiciona conteúdo na variável display
				sprintf(sinal, "Task Yellow\n");
				//Imprime o conteúdo do display na saída do console
				vPrintString(sinal);

				/*
				A função xSemaphoreGive() permite liberar o uso do semáforo
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			vPrintString("O semaforo não foi criado!\n");
		}
		vTaskDelay(portTICK_RATE_MS * 1000);
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTaskRed(void* pvParameters)
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

				//Adiciona conteúdo na variável display
				sprintf(sinal, "Task Red\n");
				//Imprime o conteúdo do display na saída do console
				vPrintString(sinal);

				/*
				A função xSemaphoreGive() permite liberar o uso do semáforo
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			vPrintString("O semaforo não foi criado!\n");
		}
		vTaskDelay(portTICK_RATE_MS * 1000);
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}