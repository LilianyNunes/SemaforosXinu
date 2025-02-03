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
