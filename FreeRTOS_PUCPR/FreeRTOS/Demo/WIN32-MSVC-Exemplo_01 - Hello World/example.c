
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"

/*
 1 - O protótipo da função de uma tarefa deve sempre retornar void, ou seja, a tarefa não possui retorno.
 2 - A função de uma tarefa deve receber um parâmetro de ponteiro void. 
*/
void myTask(void *pvParameters);

/*
 Denição da estrutura da função
*/
void myTask(void *pvParameters)
{

	const char *hello = "Hello World!!!\n";

	printf("Esta linha sera executada uma unica vez!!\n");

	for (;; )
	{
		vPrintString(hello);
		vTaskDelay(1000);
		
	}

	// Quando uma tarefa não for mais necessária, ela deverá ser excluída explicitamente.
	vTaskDelete(NULL);
}

int main_(void)
{

	xTaskCreate(myTask, "Task Hello", 1000, NULL, 1, NULL);

	// Inicia o escalonador de tarefas
	vTaskStartScheduler();

	for (;; );
	return 0;
}
