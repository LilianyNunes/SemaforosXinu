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

// Filas de mensagens para comunicação entre processos
sid32 filaSemaforo1;
sid32 filaSemaforo2;

// Função auxiliar para esperar utilizando o temporizador do Xinu
void temporizador(int segundos) {
    uint32 tempo_inicial = clktime;  // Guarda o tempo atual
    while ((clktime - tempo_inicial) < segundos) {
        // Não faz nada, apenas espera
    }
}

// Função que simula os semáforos
void semaforoSimulacao() {
    while (TRUE) {
        wait(semaforoMutex); // Protege contra concorrência
        switch (estadoSemaforo) {
            case 0: // Semáforo 1 verde, Semáforo 2 vermelho
                kprintf("\nSemaforo 1: Verde ligado, Amarelo desligado, Vermelho desligado\n");
                kprintf("Semaforo 2: Verde desligado, Amarelo desligado, Vermelho ligado\n");
                signal(semaforoMutex);
                esperar(TEMPO_VERDE);
                estadoSemaforo = 1; // Próximo estado: Semáforo 1 amarelo
                break;

            case 1: // Semáforo 1 amarelo, Semáforo 2 vermelho
                wait(semaforoMutex);
                kprintf("\nSemaforo 1: Verde desligado, Amarelo ligado, Vermelho desligado\n");
                kprintf("Semaforo 2: Verde desligado, Amarelo desligado, Vermelho ligado\n");
                signal(semaforoMutex);
                esperar(TEMPO_AMARELO);
                estadoSemaforo = 2; // Próximo estado: Semáforo 2 verde
                break;

            case 2: // Semáforo 2 verde, Semáforo 1 vermelho
                wait(semaforoMutex);
                kprintf("\nSemaforo 1: Verde desligado, Amarelo desligado, Vermelho ligado\n");
                kprintf("Semaforo 2: Verde ligado, Amarelo desligado, Vermelho desligado\n");
                signal(semaforoMutex);
                esperar(TEMPO_VERDE);
                estadoSemaforo = 3; // Próximo estado: Semáforo 2 amarelo
                break;

            case 3: // Semáforo 2 amarelo, Semáforo 1 vermelho
                wait(semaforoMutex);
                kprintf("\nSemaforo 1: Verde desligado, Amarelo desligado, Vermelho ligado\n");
                kprintf("Semaforo 2: Verde desligado, Amarelo ligado, Vermelho desligado\n");
                signal(semaforoMutex);
                esperar(TEMPO_AMARELO);
                estadoSemaforo = 0; // Próximo estado: Semáforo 1 verde
                break;
        }
    }
}
