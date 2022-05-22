#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "basic_io.h"

// Criando prot�tipo para as fun��es das tarefas
void vTaskGreen(void *pvParameters);
void vTaskYellow(void *pvParameters);
void vTaskRed(void *pvParameters);
void vTaskMonitor(void* pvParameters);

// Definindo uma vari�vel para cria��o do sem�foro
xSemaphoreHandle xSemaphore = NULL;

// Criando uma vari�vel para simular o recurso comum entre as tarefas
char sinal[100];

// Criando uma vari�vel para receber as informa��es de execu��o das tarefas
char stats[100];

int main_(void)
{
		// Criando o semaforo do tipo mutex
	    xSemaphore = xSemaphoreCreateMutex();
		
		// Criando as tarefas, aqui foi definido uma tarefa com uma prioridade diferente
		xTaskCreate(vTaskGreen, "Task Green", 1000, NULL, 1, NULL);
		xTaskCreate(vTaskYellow, "Task Yellow", 1000, NULL, 2, NULL);
		xTaskCreate(vTaskRed, "Task Red", 1000, NULL, 3, NULL);

		// Esta tarefa esta sendo criada para obter o recurso de execu��o de todas as tarefas sendo escalonadas
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

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				//Adiciona conte�do na vari�vel display
				sprintf(sinal, "Task Green\n");
				//Imprime o conte�do do display na sa�da do console
				vPrintString(sinal);
				
				/*
				A fun��o xSemaphoreGive() permite liberar o uso do sem�foro
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			vPrintString("O semaforo n�o foi criado!\n");
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

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				//Adiciona conte�do na vari�vel display
				sprintf(sinal, "Task Yellow\n");
				//Imprime o conte�do do display na sa�da do console
				vPrintString(sinal);
				
				/*
				A fun��o xSemaphoreGive() permite liberar o uso do sem�foro
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			vPrintString("O semaforo n�o foi criado!\n");
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

			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				//Adiciona conte�do na vari�vel display
				sprintf(sinal, "Task Red\n");
				//Imprime o conte�do do display na sa�da do console
				vPrintString(sinal);

				/*
				A fun��o xSemaphoreGive() permite liberar o uso do sem�foro
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			vPrintString("O semaforo n�o foi criado!\n");
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
			/* A fun��o xSemaphoreTake() verifica se o sem�foro est� dispon�vel, caso o sem�foro esteja  dispon�vel ele obt�m o sem�foro
			   Caso o sem�foro estiver sendo utilizado este aguarde 10 ticks para ver o sem�foro � liberado.
			   A fun��o xSemaphoreTake() recebe dois par�metros:
			   - O primeiro par�metro corresponde ao sem�foro
			   - O segundo par�metro corresponde o tempo que a fun��o deve aguardar caso o sem�foro j� esteja sendo utilizado.
			*/
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				/*
				A fun��o vTaskGetRunTimeStats() permite obter a quantidade de tempo de processamento que foi usado por cada tarefa.
				A fun��o apresenta essas informa��es em um formato tabular.
				- Esta fun��o recebe como parametro uma vari�vel do tipo string para armazenar as informa��es, esta vari�vel deve ter no m�nimo 40 bytes.
				
				*/
				vTaskGetRunTimeStats(stats);

				// Imprime o conte�do da vari�vel stats - tempo de execu��o de cada tarefa.
				printf("%s", stats);

				/*
				A fun��o xSemaphoreGive() permite liberar o uso do sem�foro
				*/
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			vPrintString("O semaforo n�o foi criado!\n");
		}
		vTaskDelay(portTICK_RATE_MS * 1000);
	}
	vTaskDelete(NULL);
}