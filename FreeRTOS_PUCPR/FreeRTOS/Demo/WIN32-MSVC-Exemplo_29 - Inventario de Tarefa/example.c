#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"

/*
 Defin��o do prot�tipo das tarefa para gerar interrup��o
*/
void vExampleISR(void);

//Criando os prot�tipos das fun��es para as tarefas 1 � 5
void vTask1(void* pvParameters);
void vTask2(void* pvParameters);
void vTask3(void* pvParameters);
void vTask4(void* pvParameters);
void vTask5(void* pvParameters);

/*
 Identificador Handler para as Tarefas 1 e 2.
*/
TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;
TaskHandle_t taskHandle3 = NULL;
TaskHandle_t taskHandle4 = NULL;
TaskHandle_t taskHandle5 = NULL;

// Vari�vel para armazenar as informa��es das tarefas
char ptrTaskList[250];

/*
	Esta tarefa vai simular uma interrup��o
*/
void vTask1(void* pvParameters)
{
	for (;; )
	{
		vPrintString("Task 1 - Begin\n");

		// Gerando a simula��o de uma interrup��o
		vPortGenerateSimulatedInterrupt(3);
		
		// Imprimindo mensagem Tarefa 1
		vPrintString("Task 1 - End\n");
		
		// Criando um delay de 1000ms
		vTaskDelay(1000);
	}
}

// A interru��o altera o fluxo para Tarefa 2
void vTask2(void* pvParameters) 
{
	for (;; )
	{
		vPrintString("Task 2 Running\n");
		// A tarefa se suspende
		vTaskSuspend(NULL);
		// A tarefa agora est� suspensa, ent�o dever� chegar neste ponto apenas quando a ISR (rotina de servi�o de interrup��o) retornar.
		vPrintString("Task 2 - Interruption\n");
	}
}

// A Tarefa 3 vai suspender e ativar as tarefas 3 e 4
void vTask3(void* pvParameters)
{
	volatile int estado = 0;

	for (;; )
	{

		vPrintString("Task3 Running\n");

		if (estado == 1)
		{
			//Quando a vari�vel 'estado' for igual a 1 a Tarefa 4 ser� suspensa e a tarefa 5 ativada 
			vPrintString("Task3 ative\n");

			vTaskSuspend(taskHandle4);
			vTaskResume(taskHandle5);
			estado = 0;
		}
		else
		{
			vPrintString("Task3 desative\n");
			//Quando a vari�vel 'estado' for igual a 0 a Tarefa 5 ser� suspensa e a tarefa 4 ativada
			vTaskSuspend(taskHandle5);
			vTaskResume(taskHandle4);
			estado = 1;
		}

		// Gera um delay em periodo, um tick a cada 200ms
		vTaskDelay(200 / portTICK_PERIOD_MS);

	}
	// Exclui explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTask4(void* pvParameters)
{

	for (;; )
	{
		vPrintString("Task4 Running\n");
		vTaskDelay(100 / portTICK_PERIOD_MS);

	}
	vTaskDelete(NULL);
}


void vTask5(void* pvParameters)
{
	for (;; )
	{
		vPrintString("Task5 Running\n");

		// Gera um delay em periodo, um tick a cada 100ms
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}

// Esta fun��o implementa a interrup��o
void vExampleISR(void) {

	BaseType_t checkIfYieldRequired;
	// Retoma a tarefa suspensa. 
	checkIfYieldRequired = xTaskResumeFromISR(taskHandle2);

	if (checkIfYieldRequired == pdTRUE)
	{

		vPrintString("Task Rotine\n");

		/*
		
		A fun��o vTaskList() � usada para leitura dos detalhes da tarefa (nome, estado, prioridade, num). 
		 - Esta fun��o recebe como par�metro o endere�o de uma vari�vel string (buffer) na qual ser� armazendo os detalhes das tarefas. 
		 - O tamanho do buffer deve ser de no m�nimo 40 bytes por tarefa.

		*/
		vTaskList(ptrTaskList);
		vPrintString("\n*******************************************\n");
		vPrintString("Task          State    Prio    Stack   Num\n");
		vPrintString("*******************************************\n");
		vPrintString(ptrTaskList);
		vPrintString("\n");

		// A fun��o portYIELD_FROM_ISR() permite mudar de contexto para que o ISR retorne para uma tarefa diferente.
		portYIELD_FROM_ISR(checkIfYieldRequired);
	}
	
}


int main_(void)
{
	/*
		Criando duas tarefas, cada tarefa possui seu pr�prio identificador handler 
	*/
	xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, &taskHandle1);
	xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, &taskHandle2);
	xTaskCreate(vTask3, "Task 3", 1000, NULL, 1, &taskHandle3);
	xTaskCreate(vTask4, "Task 4", 1000, NULL, 1, &taskHandle4);
	xTaskCreate(vTask5, "Task 5", 1000, NULL, 1, &taskHandle5);


	/* A fun��o vPortSetInterruptHandler() permite setar uma interrup��o.
	   - O primeiro par�metro corresponde ao identificador da interrup��o, esta faixa de valores pode ser configurado de 3 a 31 sendo poss�vel simular um total de 29 interrup��es.
	   - O segundo par�metro manipula a fun��o que gera a interrup��o. 
	*/
	vPortSetInterruptHandler(3, vExampleISR);

	// Inicializa o escalonador 
	vTaskStartScheduler();

	for (;; );
}