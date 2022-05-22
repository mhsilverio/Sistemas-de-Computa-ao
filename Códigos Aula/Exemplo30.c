#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"


//Criando os prot�tipos das fun��es para as tarefas 1 � 5
void vTask1(void* pvParameters);
void vTask2(void* pvParameters);
void vTask3(void* pvParameters);

void vTask1(void* pvParameters)
{
	for (;; )
	{
		// Imprimindo - Tarefa 1
		vPrintString("Task 1 Running\n");
	}
	//Excluindo explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTask2(void* pvParameters)
{

	for (;; )
	{
		// Imprimindo - Tarefa 2
		vPrintString("Task 2 Running\n");
	}
	//Excluindo explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTask3(void* pvParameters)
{
	volatile int estado = 0;

	int aux =  0;

	for (;; )
	{

		vPrintString("Task 3 Running\n");

		// Vari�vel para armazenar o handler 1
		TaskHandle_t xHandle1;
		// Vari�vel para armazenar os detalhes da tarefa 1
		TaskStatus_t xTaskDetails1;

		// Vari�vel para armazenar o handler 2
		TaskHandle_t xHandle2;
		// Vari�vel para armazenar os detalhes da tarefa 2
		TaskStatus_t xTaskDetails2;

		// A fun��o xTaskGetHandle() obt�m o handler a partir do nome da tarefa 1 (nome fantasia)
		xHandle1 = xTaskGetHandle("Task 1");

		// A fun��o xTaskGetHandle() obt�m o handler a partir do nome da tarefa 2 (nome fantasia)
		xHandle2 = xTaskGetHandle("Task 2");

		// Permite checar se o valor da vari�vel xHandle1 n�o � nulo (NULL).  
		configASSERT(xHandle1);

		// Permite checar se o valor da vari�vel xHandle2 n�o � nulo (NULL).
		configASSERT(xHandle2);

		/*
		
		A fun��o vTaskGetTaskInfo() obt�m informa��es sobre as tarefas (individualmente)
		 - 
		*/
		vTaskGetTaskInfo(xHandle1, &xTaskDetails1, pdTRUE, eInvalid);
		vTaskGetTaskInfo(xHandle2, &xTaskDetails2, pdTRUE, eInvalid);

		// A condi��o permite imprimir os detalhes apenas da tarefa de maior prioridade
		if (xTaskDetails2.uxBasePriority < xTaskDetails1.uxBasePriority) {

			// Imprime os detalhes da Tarefa 1
			vPrintString("\n### Details Task ###\n");
			printf("Name %s\n", xTaskDetails1.pcTaskName);
			printf("Priority %d\n", xTaskDetails1.uxBasePriority);
			printf("State %d\n", xTaskDetails1.eCurrentState);
			printf("Stack %d\n", xTaskDetails1.usStackHighWaterMark);
			printf("Number %d\n\n", xTaskDetails1.xTaskNumber);

		}
		else {
			
			// Imprime os detalhes da Tarefa 2
			vPrintString("\n### Details Task ###\n");
			printf("Name %s\n", xTaskDetails2.pcTaskName);
			printf("Priority %d\n", xTaskDetails2.uxBasePriority);
			printf("State %d\n", xTaskDetails2.eCurrentState);
			printf("Stack %d\n", xTaskDetails2.usStackHighWaterMark);
			printf("Number %d\n\n", xTaskDetails2.xTaskNumber);

		}


		// Utilizando uma vari�vel auxiliar para armazenar a prioridade da tarefa 1
		aux = xTaskDetails1.uxBasePriority;

		// Invertendo as prioridades das tarefas
		vTaskPrioritySet(xHandle1, xTaskDetails2.uxBasePriority);
		vTaskPrioritySet(xHandle2, aux);

		// Gera um delay em periodo, um tick a cada 200ms
		vTaskDelay(50 / portTICK_PERIOD_MS);

	}
	// Exclui explicitamente a tarefa
	vTaskDelete(NULL);
}


int main_(void)
{
	/*
		Criando tr�s tarefas, cada tarefa possui uma prioridade diferente
		N�o foi adicionado o identificador handler para tarefas
	*/
	xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
	xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, NULL);
	xTaskCreate(vTask3, "Task 3", 1000, NULL, 3, NULL);

	// Inicializa o escalonador 
	vTaskStartScheduler();

	for (;; );
}