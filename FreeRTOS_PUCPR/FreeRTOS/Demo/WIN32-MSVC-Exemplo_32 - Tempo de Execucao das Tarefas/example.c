#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "basic_io.h"

// Criando protótipo para as funções das tarefas
void vTaskGreen(void *pvParameters);
void vTaskYellow(void *pvParameters);
void vTaskRed(void *pvParameters);
void vTaskMonitor(void* pvParameters);

// Definindo uma variável para criação do semáforo
xSemaphoreHandle xSemaphore = NULL;

// Criando uma variável para simular o recurso comum entre as tarefas
char sinal[100];

// Criando uma variável para receber as informações de execução das tarefas
char stats[100];

int main_(void)
{
		// Criando o semaforo do tipo mutex
	    xSemaphore = xSemaphoreCreateMutex();
		
		// Criando as tarefas, aqui foi definido uma tarefa com uma prioridade diferente
		xTaskCreate(vTaskGreen, "Task Green", 1000, NULL, 1, NULL);
		xTaskCreate(vTaskYellow, "Task Yellow", 1000, NULL, 2, NULL);
		xTaskCreate(vTaskRed, "Task Red", 1000, NULL, 3, NULL);

		// Esta tarefa esta sendo criada para obter o recurso de execução de todas as tarefas sendo escalonadas
		xTaskCreate(vTaskMonitor, "Monitor", 1000, NULL, 4, NULL);

		// Inicia o escalonador de tarefas
		vTaskStartScheduler();

	for (;; );
	return 0;
}

void vTaskGreen(void* pvParameters)
{
	for (;; )
	{
		// Verifica se o semaforo foi criado
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
		vTaskDelay(portTICK_RATE_MS * 500);
	}
	vTaskDelete(NULL);
}


void vTaskYellow(void* pvParameters)
{
	for (;; )
	{
		
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
	vTaskDelete(NULL);
}

void vTaskRed(void* pvParameters)
{
	for (;; )
	{

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
		vTaskDelay(portTICK_RATE_MS * 1500);
	}
	vTaskDelete(NULL);
}

void vTaskMonitor(void* pvParameters)
{
	for (;; )
	{

		if (xSemaphore != NULL) {
			/* A função xSemaphoreTake() verifica se o semáforo está disponível, caso o semáforo esteja  disponível ele obtém o semáforo
			   Caso o semáforo estiver sendo utilizado este aguarde 10 ticks para ver o semáforo é liberado.
			   A função xSemaphoreTake() recebe dois parâmetros:
			   - O primeiro parâmetro corresponde ao semáforo
			   - O segundo parâmetro corresponde o tempo que a função deve aguardar caso o semáforo já esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				/*
				A função vTaskGetRunTimeStats() permite obter a quantidade de tempo de processamento que foi usado por cada tarefa.
				A função apresenta essas informações em um formato tabular.
				- Esta função recebe como parametro uma variável do tipo string para armazenar as informações, esta variável deve ter no mínimo 40 bytes.
				
				*/
				vTaskGetRunTimeStats(stats);

				// Imprime o conteúdo da variável stats - tempo de execução de cada tarefa.
				printf("%s", stats);

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
	vTaskDelete(NULL);
}