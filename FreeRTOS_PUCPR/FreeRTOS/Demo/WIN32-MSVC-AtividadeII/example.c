Mi Silvério
#9572

RicardoKurashiki — 06/12/2021
🙏 🙏 🙏 🙏 🙏 🙏 🙏 🙏 🙏
Mi Silvério — 13/04/2022
AHHH NÃO
muito fofo ele ❤️
olha essa foto de perfil!
👏 👏 👏 👏 👏
RicardoKurashiki — 13/04/2022
Hehehe
Brigado
RicardoKurashiki — 18/04/2022
Imagem
Imagem
RicardoKurashiki — 19/04/2022
Imagem
Tipo de arquivo em anexo: acrobat
Diagrama_dos_Setores.pdf
73.81 KB
Mi Silvério — 19/04/2022
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental_parte1.pdf
1.74 MB
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental_parte2.pdf
908.73 KB
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental_parte3.pdf
26.82 KB
Mi Silvério — 22/04/2022
heyy, tá ai?
RicardoKurashiki — 22/04/2022
opa
to sim
Mi Silvério — 22/04/2022
por acaso, vc chegou a fazer as questões de potência e energia da lista 2?
mais especificamente agora a questão 6b
RicardoKurashiki — 22/04/2022
putz
pior que n cheguei a fazer essa parte
eu só fiz a 1 da lista 2
e dps fiquei fazendo a prova lá
e na prova eu parei bem na questão 3 que era de energia
Mi Silvério — 22/04/2022
ahhh tendi
Mi Silvério — 22/04/2022
hello
estudando ou trabalhando?
RicardoKurashiki — 22/04/2022
ambos e nenhum ao mesmo tempo
Mi Silvério — 22/04/2022
hahahahah
ai ai ai
conseguiu terminar as listas?
os da potência e energia consegui fazer na lista, mas agora não faço a mínima ideia de como faz a 4
RicardoKurashiki — 22/04/2022
putz Mi, vou começar mesmo agora
Mi Silvério — 22/04/2022
susse
RicardoKurashiki — 22/04/2022
posso te mandar as fotos que o Cadu me mandou ontem da resolução dele da prova
pode ser?
ai ja tem uma base
Mi Silvério — 22/04/2022
não é da prova
é da lista 2
RicardoKurashiki — 22/04/2022
aaaah sim
cafundi
Mi Silvério — 03/05/2022
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental.pdf
3.06 MB
Mi Silvério — 04/05/2022
.
Imagem
Mi Silvério — 10/05/2022
oi, tudo bem??
por acaso vc lembra o site que vc baixou o emu8086 no seu note?? não tô lembrada qual era o site em específico
RicardoKurashiki — 11/05/2022
eita, só agora que vi a msg
foi no softsonic se eu n me engano
Mi Silvério — 12/05/2022
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental.pdf
3.12 MB
Mi Silvério — Ontem às 16:39
https://prod.liveshare.vsengsaas.visualstudio.com/join?CFBE2595D7ABD065B2C2705BF1FB52962C92
Visual Studio Code for the Web
Build with Visual Studio Code, anywhere, anytime, entirely in your browser.
Mi Silvério — Hoje às 16:00
https://prod.liveshare.vsengsaas.visualstudio.com/join?CB11F058BCBDC5747098193BAAEAA7D51609
Visual Studio Code for the Web
Build with Visual Studio Code, anywhere, anytime, entirely in your browser.
RicardoKurashiki — Hoje às 16:51
.
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
Expandir
message.c
7 KB
﻿
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
// Engenharia de Comuputacao - 7 periodo
// Sistemas de computacao

// Definindo o prototipo das tarefas 
void Socrates(void* pvParameters);
void Descartes(void* pvParameters);
void Aristoteles(void* pvParameters);
void Kant(void* pvParameters);
void Hegel(void* pvParameters);
void mostraEstados(void* pvParameters);

// Criando a variavel para o semaforo
xSemaphoreHandle garSH = NULL; // Garfo entre Socrates e Hegel
xSemaphoreHandle garSD = NULL; // Garfo entre Socrates e Descartes
xSemaphoreHandle garDA = NULL; // Garfo entre Descartes e Aristoteles
xSemaphoreHandle garAK = NULL; // Garfo entre Aristoteles e Kant
xSemaphoreHandle garKH = NULL; // Garfo entre Kant e Hegel
xSemaphoreHandle estados = NULL;

volatile int socratesComendo = 0;
volatile int descartesComendo = 0;
volatile int aristotelesComendo = 0;
volatile int kantComendo = 0;
volatile int hegelComendo = 0;

TaskHandle_t SocratesHandle = NULL;
TaskHandle_t DescartesHandle = NULL;
TaskHandle_t AristotelesHandle = NULL;
TaskHandle_t KantHandle = NULL;
TaskHandle_t HegelHandle = NULL;

int main_(void)
{
	// Funcao para criar um semaforo Mutex
	garSH = xSemaphoreCreateMutex();
	garSD = xSemaphoreCreateMutex();
	garDA = xSemaphoreCreateMutex();
	garAK = xSemaphoreCreateMutex();
	garKH = xSemaphoreCreateMutex();
	estados = xSemaphoreCreateMutex();

	// Criando tarefas 
	xTaskCreate(Socrates, "Socrates", 500, NULL, 1, &SocratesHandle);
	xTaskCreate(Descartes, "Descartes", 500, NULL, 1, &DescartesHandle);
	xTaskCreate(Aristoteles, "Aristoteles", 500, NULL, 1, &AristotelesHandle);
	xTaskCreate(Kant, "Kant", 500, NULL, 1, &KantHandle);
	xTaskCreate(Hegel, "Hegel", 500, NULL, 1, &HegelHandle);
	xTaskCreate(mostraEstados, "Estados", 500, NULL, 1, NULL);

	// Inicializa o escalonador
	vTaskStartScheduler();

	for (;; );
	return 0;
}

void mostraEstados(void* pvParameters)
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

	vTaskDelete(NULL);
}

void Socrates(void* pvParameters)
{
	for (;; )
	{
		if (garSH != NULL && garSD != NULL) 
		{
			if (xSemaphoreTake(garSH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garSD, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						socratesComendo = 1;
						xSemaphoreGive(estados);
					}

					vTaskDelay(portTICK_RATE_MS * 250);

					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						socratesComendo = 0;
						xSemaphoreGive(estados);
					}
					
					xSemaphoreGive(garSD);
				}

				xSemaphoreGive(garSH);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 50);
	}

	vTaskDelete(NULL);
}
void Descartes(void* pvParameters)
{
	for (;; )
	{
		if (garSD != NULL && garDA != NULL) 
		{
			if (xSemaphoreTake(garSD, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garDA, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						descartesComendo = 1;
						xSemaphoreGive(estados);
					}
					
					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						descartesComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garDA);
				}

				xSemaphoreGive(garSD);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 100);
	}

	vTaskDelete(NULL);
}
void Aristoteles(void* pvParameters)
{
	for (;; )
	{
		if (garDA != NULL && garAK != NULL) 
		{
			if (xSemaphoreTake(garDA, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garAK, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						aristotelesComendo = 1;
						xSemaphoreGive(estados);
					}
					
					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						aristotelesComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garAK);
				}

				xSemaphoreGive(garDA);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 150);
	}

	vTaskDelete(NULL);
}
void Kant(void* pvParameters)
{
	for (;; )
	{
		if (garAK != NULL && garKH != NULL) {
			if (xSemaphoreTake(garAK, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garKH, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						kantComendo = 1;
						xSemaphoreGive(estados);
					}
					vTaskDelay(portTICK_RATE_MS * 250);

					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						kantComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garKH);
				}

				xSemaphoreGive(garAK);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 200);
	}
	vTaskDelete(NULL);
}

void Hegel(void* pvParameters)
{
	for (;; )
	{
		if (garKH != NULL && garSH != NULL) {
			if (xSemaphoreTake(garKH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garSH, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						hegelComendo = 1;
						xSemaphoreGive(estados);
					}

					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						hegelComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garSH);
				}
				xSemaphoreGive(garKH);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 250);
	}
	vTaskDelete(NULL);
}
message.c
7 KBMi Silvério
#9572

RicardoKurashiki — 06/12/2021
🙏 🙏 🙏 🙏 🙏 🙏 🙏 🙏 🙏
Mi Silvério — 13/04/2022
AHHH NÃO
muito fofo ele ❤️
olha essa foto de perfil!
👏 👏 👏 👏 👏
RicardoKurashiki — 13/04/2022
Hehehe
Brigado
RicardoKurashiki — 18/04/2022
Imagem
Imagem
RicardoKurashiki — 19/04/2022
Imagem
Tipo de arquivo em anexo: acrobat
Diagrama_dos_Setores.pdf
73.81 KB
Mi Silvério — 19/04/2022
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental_parte1.pdf
1.74 MB
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental_parte2.pdf
908.73 KB
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental_parte3.pdf
26.82 KB
Mi Silvério — 22/04/2022
heyy, tá ai?
RicardoKurashiki — 22/04/2022
opa
to sim
Mi Silvério — 22/04/2022
por acaso, vc chegou a fazer as questões de potência e energia da lista 2?
mais especificamente agora a questão 6b
RicardoKurashiki — 22/04/2022
putz
pior que n cheguei a fazer essa parte
eu só fiz a 1 da lista 2
e dps fiquei fazendo a prova lá
e na prova eu parei bem na questão 3 que era de energia
Mi Silvério — 22/04/2022
ahhh tendi
Mi Silvério — 22/04/2022
hello
estudando ou trabalhando?
RicardoKurashiki — 22/04/2022
ambos e nenhum ao mesmo tempo
Mi Silvério — 22/04/2022
hahahahah
ai ai ai
conseguiu terminar as listas?
os da potência e energia consegui fazer na lista, mas agora não faço a mínima ideia de como faz a 4
RicardoKurashiki — 22/04/2022
putz Mi, vou começar mesmo agora
Mi Silvério — 22/04/2022
susse
RicardoKurashiki — 22/04/2022
posso te mandar as fotos que o Cadu me mandou ontem da resolução dele da prova
pode ser?
ai ja tem uma base
Mi Silvério — 22/04/2022
não é da prova
é da lista 2
RicardoKurashiki — 22/04/2022
aaaah sim
cafundi
Mi Silvério — 03/05/2022
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental.pdf
3.06 MB
Mi Silvério — 04/05/2022
.
Imagem
Mi Silvério — 10/05/2022
oi, tudo bem??
por acaso vc lembra o site que vc baixou o emu8086 no seu note?? não tô lembrada qual era o site em específico
RicardoKurashiki — 11/05/2022
eita, só agora que vi a msg
foi no softsonic se eu n me engano
Mi Silvério — 12/05/2022
Tipo de arquivo em anexo: acrobat
Plano_de_gestao_ambiental.pdf
3.12 MB
Mi Silvério — Ontem às 16:39
https://prod.liveshare.vsengsaas.visualstudio.com/join?CFBE2595D7ABD065B2C2705BF1FB52962C92
Visual Studio Code for the Web
Build with Visual Studio Code, anywhere, anytime, entirely in your browser.
Mi Silvério — Hoje às 16:00
https://prod.liveshare.vsengsaas.visualstudio.com/join?CB11F058BCBDC5747098193BAAEAA7D51609
Visual Studio Code for the Web
Build with Visual Studio Code, anywhere, anytime, entirely in your browser.
RicardoKurashiki — Hoje às 16:51
.
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
Expandir
message.c
7 KB
﻿
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
// Engenharia de Comuputacao - 7 periodo
// Sistemas de computacao

// Definindo o prototipo das tarefas 
void Socrates(void* pvParameters);
void Descartes(void* pvParameters);
void Aristoteles(void* pvParameters);
void Kant(void* pvParameters);
void Hegel(void* pvParameters);
void mostraEstados(void* pvParameters);

// Criando a variavel para o semaforo
xSemaphoreHandle garSH = NULL; // Garfo entre Socrates e Hegel
xSemaphoreHandle garSD = NULL; // Garfo entre Socrates e Descartes
xSemaphoreHandle garDA = NULL; // Garfo entre Descartes e Aristoteles
xSemaphoreHandle garAK = NULL; // Garfo entre Aristoteles e Kant
xSemaphoreHandle garKH = NULL; // Garfo entre Kant e Hegel
xSemaphoreHandle estados = NULL;

volatile int socratesComendo = 0;
volatile int descartesComendo = 0;
volatile int aristotelesComendo = 0;
volatile int kantComendo = 0;
volatile int hegelComendo = 0;

TaskHandle_t SocratesHandle = NULL;
TaskHandle_t DescartesHandle = NULL;
TaskHandle_t AristotelesHandle = NULL;
TaskHandle_t KantHandle = NULL;
TaskHandle_t HegelHandle = NULL;

int main_(void)
{
	// Funcao para criar um semaforo Mutex
	garSH = xSemaphoreCreateMutex();
	garSD = xSemaphoreCreateMutex();
	garDA = xSemaphoreCreateMutex();
	garAK = xSemaphoreCreateMutex();
	garKH = xSemaphoreCreateMutex();
	estados = xSemaphoreCreateMutex();

	// Criando tarefas 
	xTaskCreate(Socrates, "Socrates", 500, NULL, 1, &SocratesHandle);
	xTaskCreate(Descartes, "Descartes", 500, NULL, 1, &DescartesHandle);
	xTaskCreate(Aristoteles, "Aristoteles", 500, NULL, 1, &AristotelesHandle);
	xTaskCreate(Kant, "Kant", 500, NULL, 1, &KantHandle);
	xTaskCreate(Hegel, "Hegel", 500, NULL, 1, &HegelHandle);
	xTaskCreate(mostraEstados, "Estados", 500, NULL, 1, NULL);

	// Inicializa o escalonador
	vTaskStartScheduler();

	for (;; );
	return 0;
}

void mostraEstados(void* pvParameters)
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

	vTaskDelete(NULL);
}

void Socrates(void* pvParameters)
{
	for (;; )
	{
		if (garSH != NULL && garSD != NULL) 
		{
			if (xSemaphoreTake(garSH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garSD, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						socratesComendo = 1;
						xSemaphoreGive(estados);
					}

					vTaskDelay(portTICK_RATE_MS * 250);

					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						socratesComendo = 0;
						xSemaphoreGive(estados);
					}
					
					xSemaphoreGive(garSD);
				}

				xSemaphoreGive(garSH);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 50);
	}

	vTaskDelete(NULL);
}
void Descartes(void* pvParameters)
{
	for (;; )
	{
		if (garSD != NULL && garDA != NULL) 
		{
			if (xSemaphoreTake(garSD, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garDA, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						descartesComendo = 1;
						xSemaphoreGive(estados);
					}
					
					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						descartesComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garDA);
				}

				xSemaphoreGive(garSD);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 100);
	}

	vTaskDelete(NULL);
}
void Aristoteles(void* pvParameters)
{
	for (;; )
	{
		if (garDA != NULL && garAK != NULL) 
		{
			if (xSemaphoreTake(garDA, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garAK, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						aristotelesComendo = 1;
						xSemaphoreGive(estados);
					}
					
					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						aristotelesComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garAK);
				}

				xSemaphoreGive(garDA);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}

		vTaskDelay(portTICK_RATE_MS * 150);
	}

	vTaskDelete(NULL);
}
void Kant(void* pvParameters)
{
	for (;; )
	{
		if (garAK != NULL && garKH != NULL) {
			if (xSemaphoreTake(garAK, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garKH, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						kantComendo = 1;
						xSemaphoreGive(estados);
					}
					vTaskDelay(portTICK_RATE_MS * 250);

					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						kantComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garKH);
				}

				xSemaphoreGive(garAK);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 200);
	}
	vTaskDelete(NULL);
}

void Hegel(void* pvParameters)
{
	for (;; )
	{
		if (garKH != NULL && garSH != NULL) {
			if (xSemaphoreTake(garKH, (portTickType)10) == pdTRUE)
			{
				if (xSemaphoreTake(garSH, (portTickType)10) == pdTRUE)
				{
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						hegelComendo = 1;
						xSemaphoreGive(estados);
					}

					vTaskDelay(portTICK_RATE_MS * 250);
					
					if (xSemaphoreTake(estados, (portTickType)1000) == pdTRUE)
					{
						hegelComendo = 0;
						xSemaphoreGive(estados);
					}

					xSemaphoreGive(garSH);
				}
				xSemaphoreGive(garKH);
			}
		}
		else
		{
			printf("O semaforo nao foi criado\n");
		}
		vTaskDelay(portTICK_RATE_MS * 250);
	}
	vTaskDelete(NULL);
}
