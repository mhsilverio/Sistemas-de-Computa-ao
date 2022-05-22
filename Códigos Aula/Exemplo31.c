#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "basic_io.h"

void vTaskGreen(void *pvParameters);
void vTaskYellow(void *pvParameters);
void vTaskRed(void *pvParameters);

// Criando a vari�vel para o sem�foro
xSemaphoreHandle xSemaphore = NULL;

// Criando uma vari�vel buffer para manipular a mensagem do sinaleiro 
char sinal[100];

int main_(void)
{
	    // Fun��o para criar um sem�foro bin�rio
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
		// Verificando se o sem�foro foi criado antes de utiliz�-lo
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
		vTaskDelay(portTICK_RATE_MS * 1000);
	}
	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}


void vTaskYellow(void* pvParameters)
{
	for (;; )
	{
		
		// Verificando se o sem�foro foi criado antes de utiliz�-lo
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
	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTaskRed(void* pvParameters)
{
	for (;; )
	{
		// Verificando se o sem�foro foi criado antes de utiliz�-lo
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
		vTaskDelay(portTICK_RATE_MS * 1000);
	}
	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}