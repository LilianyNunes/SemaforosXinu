#include <xinu.h>

// Definição do tempo para cada estado (em segundos)
#define TEMPO_VERDE 5
#define TEMPO_AMARELO 2
#define TEMPO_VERMELHO 5

// Controle do estado atual dos semáforos
// O valor de 'estadoSemaforo' indica o estado atual dos semáforos:
// 0 = Semáforo 1 está verde e Semáforo 2 está vermelho
// 1 = Semáforo 1 está amarelo e Semáforo 2 está vermelho
// 2 = Semáforo 1 está vermelho e Semáforo 2 está verde
// 3 = Semáforo 1 está vermelho e Semáforo 2 está amarelo
int estadoSemaforo = 0;

// Semáforo para evitar concorrência entre processos
sid32 semaforoMutex; 

// Função auxiliar para aguardar um tempo específico e mostrar a contagem no console
void esperar(int segundos) {
    int i;
    for (i = 1; i <= segundos; i++) {  // Loop que se repete até atingir o tempo desejado
        kprintf("Segundos: %d\n", i);  // Exibe no console quantos segundos já se passaram
        sleepms(1000);  // Faz o processo "dormir" por 1000 milissegundos (1 segundo)
    }
}
