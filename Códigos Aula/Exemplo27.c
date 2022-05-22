
#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include "queue.h"

xQueueHandle filaMensagem;

static char* vetMessagens[] =
{
"*** Tarefa - Instancia 1 ***\n\n",
"--- Tarefa - Instancia 2 ---\n",
"### Tick Hook Interrupt ####\n"
};

static void printGatekeeperTask(void* pvParameters)
{
	char* mensagem;
	/* 
	Esta � a �nica tarefa que tem permiss�o para gravar na sa�da do terminal. 
	Qualquer outra tarefa que queira gravar uma string na sa�da n�o acessa o terminal diretamente. 
	 - Em vez disso a demais tarefas devem enviar a string para que essa tarefa imprima. 
	Como apenas essa tarefa acessa a sa�da padr�o, n�o � necess�rio considerar a implementa��o de exclus�o m�tua ou serializa��o dentro das tarefa.
	*/
	for (;; )
	{
		/* 
		
		Aguardando a chegada de uma mensagem. 
		Um tempo de bloqueio indefinido � especificado para que n�o haja necessidade de verificar o valor de retorno 
		Desta maneira a fun��o s� retornar� quando alguma mensagem for recebida com sucesso
		
		*/
		xQueueReceive(filaMensagem, &mensagem, portMAX_DELAY);
		/* Imprime a string recebida. */
		printf("%s", mensagem);

		fflush(stdout);
		/* Agora basta voltar para aguardar a pr�xima mensagem. */

	}
}

static void printTask(void* pvParameters)
{
	int indiceMensagem;
	/* 
	 - O par�metro da tarefa est� sendo usado para passar um �ndice para uma matriz de strings na tarefa. 
     - Assim efetuamos a convers�o para o tipo necess�rio.
	*/
	indiceMensagem = (int)pvParameters;
	for (;; )
	{
		/* 
		Esta tarefa a string n�o � impressa diretamente na tarefa
		Aqui � passado um ponteiro da string para tarefa gatekeeper por meio da estrutura fila.
		A fila foi criada antes do escalonador ser iniciado, deste modo j� existira quando esta tarefa for executada pela primeira vez.
		Aqui n�o est� sendo especificado nenhum tempo de bloqueia, pois neste caso sempre deve haver espa�o na fila.
		*/
		xQueueSendToBack(filaMensagem, &(vetMessagens[indiceMensagem]), 0);
		/* 
		Gerando um delay pseudo aleat�rio
		 - Ressalta-se que a fun��o rand() n�o � necessariamente reetrante
		 - Para este caso n�o faz muita diferen�a o c�digo n�o se importa muito com o retorno da fun��o. 
		 - Por�m em aplicativos mais seguro deve ser utilizado uma vers�o da fun��o rand() reentrante, 
		 - Ou as chamadas para fun��o rand() devem ser protegidas utilizando uma se��o cr�tica.
		*/
		vTaskDelay((rand() & 0x1FF));
	}
	// Excluir explicitamente a tarefa
	vTaskDelete(NULL);
}

void vApplicationTickHook(void)
{
	static int contador = 0;

	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	/* 
	Imprima uma mensagem a cada 200 ticks. 
	A mensagem n�o � escrita diretamente na sa�da do console, 
	Enviada para tarefa gatekeeper utilizando a estrutura da fila.
	*/
	contador++;
	if (contador >= 200)
	{
		/* 
		O �ltimo par�metro apesar de n�o ser utilizado � necess�rio ser fornecido. 
		*/
		xQueueSendToFrontFromISR(filaMensagem, &(vetMessagens[2]), &xHigherPriorityTaskWoken);
		/* Inicia novamene a contagem para imprimir a string daqui 200 ticks  */
		contador = 0;
	}
}

int main_(void)
{
	// Cria uma estrutura fila para imprimir as tarefas
	filaMensagem = xQueueCreate(5, sizeof(char*));

	/* The tasks are going to use a pseudo random delay, seed the random number generator. */
	srand(567);

	static const char* msg1 = "Tarefa - Instancia 1\n";
	static const char* msg2 = "Tarefa - Instancia 2\n";

	// Cria duas instancias da tarefa que envia impress�o para fila
	xTaskCreate(printTask, "Task 1", 1000, (void*)0, 1, NULL);
	xTaskCreate(printTask, "Task 2", 1000, (void*)1, 2, NULL);


	xTaskCreate(printGatekeeperTask, "Gatekeeper", 1000, NULL, 0, NULL);

	/* Inicia o escalonador de tarefas. */
	vTaskStartScheduler();

	for (;; );
	return 0;
}
