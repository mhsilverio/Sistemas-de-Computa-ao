#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Definindo o protótipo das tarefas 
void guinada(void *pvParameters);
void arfagem(void *pvParameters);
void rolagem(void *pvParameters);

volatile long velMotor0;
volatile long velMotor1;
volatile long velMotor2;
volatile long velMotor3;

int main_(void)
{
	// Criando duas tarefas 
	xTaskCreate(guinada, "Guinada", 1000, (void *) 1, 1, NULL);
	xTaskCreate(arfagem, "Arfagem", 1000, (void *) 0, 1, NULL);
	xTaskCreate(rolagem, "Rolagem", 1000, (void *) 1, 1, NULL);

	// Inicializa o escalonador
	vTaskStartScheduler();

	for (;; );
	return 0;
}

void guinada(void* pvParameters)
{
	int sentido = (int) pvParameters;
	char *stringSentido[20];
	char *resumo[200];
	// 0 -- Horario
	// 1 -- Anti-horario

	for (;;)
	{
		if (sentido == 0)
		{
			sprintf(stringSentido, "Horario");
			velMotor0 += 100;
			velMotor1 -= 100;
			velMotor2 += 100;
			velMotor3 -= 100;
		}
		else 
		{
			sprintf(stringSentido, "Anti-horario");
			velMotor0 -= 100;
			velMotor1 += 100;
			velMotor2 -= 100;
			velMotor3 += 100;
		}
		sprintf(resumo, "\nGuinada - Sentido: %s - M0: %d, M1: %d, M2: %d, M3: %d", stringSentido, velMotor0, velMotor1, velMotor2, velMotor3);

		sentido = rand() & 1;

		vPrintString(resumo);
		vTaskDelay(portTICK_RATE_MS * 10);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void arfagem(void* pvParameters)
{
	int sentido = (int)pvParameters;
	char *stringSentido[20];
	char *resumo[200];

	// 0 -- Frente
	// 1 -- Tras
	for (;;)
	{
		if (sentido == 0)
		{
			sprintf(stringSentido, "Frente");
			velMotor0 -= 25;
			velMotor1 -= 25;
			velMotor2 += 25;
			velMotor3 += 25;
		}
		else
		{
			sprintf(stringSentido, "Tras");
			velMotor0 += 25;
			velMotor1 += 25;
			velMotor2 -= 25;
			velMotor3 -= 25;
		}
		sprintf(resumo, "\nArfagem - Sentido: %s - M0: %d, M1: %d, M2: %d, M3: %d", stringSentido, velMotor0, velMotor1, velMotor2, velMotor3);

		sentido = rand() & 1;

		vPrintString(resumo);
		vTaskDelay(portTICK_RATE_MS * 40);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void rolagem (void* pvParameters)
{
	int sentido = (int)pvParameters;
	char *stringSentido[20];
	char *resumo[200];

	// 0 -- Direita
	// 1 -- Esquerda
	for (;;)
	{
		if (sentido == 0)
		{
			sprintf(stringSentido, "Direita");
			velMotor0 += 50;
			velMotor1 -= 50;
			velMotor2 -= 50;
			velMotor3 += 50;
		}
		else
		{
			sprintf(stringSentido, "Esquerda");
			velMotor0 -= 50;
			velMotor1 += 50;
			velMotor2 += 50;
			velMotor3 -= 50;
		}
		sprintf(resumo, "\nRolagem - Sentido: %s - M0: %d, M1: %d, M2: %d, M3: %d", stringSentido, velMotor0, velMotor1, velMotor2, velMotor3);

		sentido = rand() & 1;

		vPrintString(resumo);
		vTaskDelay(portTICK_RATE_MS * 20);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
