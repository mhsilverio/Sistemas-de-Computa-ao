
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
	Esta é a única tarefa que tem permissão para gravar na saída do terminal. 
	Qualquer outra tarefa que queira gravar uma string na saída não acessa o terminal diretamente. 
	 - Em vez disso a demais tarefas devem enviar a string para que essa tarefa imprima. 
	Como apenas essa tarefa acessa a saída padrão, não é necessário considerar a implementação de exclusão mútua ou serialização dentro das tarefa.
	*/
	for (;; )
	{
		/* 
		
		Aguardando a chegada de uma mensagem. 
		Um tempo de bloqueio indefinido é especificado para que não haja necessidade de verificar o valor de retorno 
		Desta maneira a função só retornará quando alguma mensagem for recebida com sucesso
		
		*/
		xQueueReceive(filaMensagem, &mensagem, portMAX_DELAY);
		/* Imprime a string recebida. */
		printf("%s", mensagem);

		fflush(stdout);
		/* Agora basta voltar para aguardar a próxima mensagem. */

	}
}

static void printTask(void* pvParameters)
{
	int indiceMensagem;
	/* 
	 - O parâmetro da tarefa está sendo usado para passar um índice para uma matriz de strings na tarefa. 
     - Assim efetuamos a conversão para o tipo necessário.
	*/
	indiceMensagem = (int)pvParameters;
	for (;; )
	{
		/* 
		Esta tarefa a string não é impressa diretamente na tarefa
		Aqui é passado um ponteiro da string para tarefa gatekeeper por meio da estrutura fila.
		A fila foi criada antes do escalonador ser iniciado, deste modo já existira quando esta tarefa for executada pela primeira vez.
		Aqui não está sendo especificado nenhum tempo de bloqueia, pois neste caso sempre deve haver espaço na fila.
		*/
		xQueueSendToBack(filaMensagem, &(vetMessagens[indiceMensagem]), 0);
		/* 
		Gerando um delay pseudo aleatório
		 - Ressalta-se que a função rand() não é necessariamente reetrante
		 - Para este caso não faz muita diferença o código não se importa muito com o retorno da função. 
		 - Porém em aplicativos mais seguro deve ser utilizado uma versão da função rand() reentrante, 
		 - Ou as chamadas para função rand() devem ser protegidas utilizando uma seção crítica.
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
	A mensagem não é escrita diretamente na saída do console, 
	Enviada para tarefa gatekeeper utilizando a estrutura da fila.
	*/
	contador++;
	if (contador >= 200)
	{
		/* 
		O último parâmetro apesar de não ser utilizado é necessário ser fornecido. 
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

	// Cria duas instancias da tarefa que envia impressão para fila
	xTaskCreate(printTask, "Task 1", 1000, (void*)0, 1, NULL);
	xTaskCreate(printTask, "Task 2", 1000, (void*)1, 2, NULL);


	xTaskCreate(printGatekeeperTask, "Gatekeeper", 1000, NULL, 0, NULL);

	/* Inicia o escalonador de tarefas. */
	vTaskStartScheduler();

	for (;; );
	return 0;
}
