
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <stdlib.h>

// Prototipando a funcao da task que ira monitorar os batimentos cardiacos.
void monitBatimentos(void *pvParameters);
// Prototipando a funcao da task que ira monitorar a saturacao.
void monitSaturacao(void* pvParameters);
// Prototipando a funcao da task que ira monitorar a temperatura.
void monitTemperatura(void* pvParameters);

// Criacao das variaveis que irao simular o batimento, a saturacao e a temperatura.
volatile int batimentos = 0;
volatile double saturacao = 0;
volatile double temperatura = 0;

int main_(void)
{
	// Criando processo de monitoramento de batimentos passando a funcao de monitoramento de batimentos, pilha de 1000 bytes, e prioridade 1.
	xTaskCreate(monitBatimentos, "Monitoramento de Batimentos", 1000, NULL, 1, NULL);
	// Criando processo de monitoramento de saturacao passando a funcao de monitoramento de saturacao, pilha de 1000 bytes, e prioridade 1.
	xTaskCreate(monitSaturacao, "Monitoramento de Saturacao", 1000, NULL, 1, NULL);
	// Criando processo de monitoramento de temperatura passando a funcao de monitoramento de temperatura, pilha de 1000 bytes, e prioridade 1.
	xTaskCreate(monitTemperatura, "Monitoramento de Temperatura", 1000, NULL, 1, NULL);

	// Iniciando o escalonador para gerenciamento dos processos.
	vTaskStartScheduler();

	for (;;);

	return 0;
}

void monitBatimentos(void *pvParameters)
{
	for (;;)
	{
		// Gera um numero aleatorio para batimentos entre 0 e 140.
		batimentos = rand() % 141;

		vPrintStringAndNumber("\n\nBATIMENTOS: ", batimentos);
		
		/*
		Caso os batimentos sejam menores que 50, informara o usuario que esta com 
		batimentos baixos, caso seja maior que 90, informara o usuario que esta com
		batimentos altos.
		*/
		if (batimentos < 50)
			vPrintString("!! Batimentos cardiacos baixos. !!");
		else if (batimentos > 90)
			vPrintString("!! Batimentos cardiacos altos. !!");
			
		vTaskDelay(500);
	}

	vTaskDelete(NULL);
}

void monitSaturacao(void* pvParameters)
{
	for (;;)
	{
		// Gera um numero aleatorio para saturacao entre 0 e 100  por cento.
		saturacao = rand() % 101;

		vPrintStringAndNumber("\n\nSATURACAO: ", saturacao);

		// Caso a saturacao seja menor que 90%, informara ao usuario que esta com saturacao baixa.
		if (saturacao < 90)
			vPrintString("!! Saturacao baixa. !!");

		vTaskDelay(500);
	}

	vTaskDelete(NULL);
}

void monitTemperatura(void* pvParameters)
{
	for (;;)
	{
		// Gera um numero aleatorio para saturacao entre 0 e 41.
		temperatura = rand() % 42;
			
		vPrintStringAndNumber("\n\nTEMPERATURA: ", temperatura);

		/*
		Caso a temperatura seja menor que 35, informara o usuario que esta com
		hipotermia, caso seja maior que 37.5, informara o usuario que esta com
		febre.
		*/
		if (temperatura < 35)
			vPrintString("!! Voce esta com hipotermia. !!");
		else if (temperatura > 37.5)
			vPrintString("!! Voce esta febril. !!");

		vTaskDelay(500);
	}

	vTaskDelete(NULL);
}

