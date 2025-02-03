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
