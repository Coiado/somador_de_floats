/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_MAX 1000

/* Maquina de estados:
 * Detecta se existe ao menos um numero inteiro na linha inserida */

int eh_digito(char c)
{
    if ((c >= '0') && (c <= '9')) return 1;
    else return 0;
}

typedef struct {
    int estado_atual;
} fsm, *Fsm; /* fsm = finite state machine */

int opera_fsm(void *this_fsm, char entrada) {
    Fsm maquina = (Fsm) this_fsm;
    switch (maquina->estado_atual) {
        case 0:
            if (eh_digito(entrada)) {
                maquina->estado_atual = 2;
            } else {
                if (entrada == ' ' || entrada == '\n') {
                    maquina->estado_atual = 4;
                } else {
                    maquina->estado_atual = 1;
                }
            }
            break;
            
        case 1:
            if (entrada == ' ') {
                maquina->estado_atual = 0;
            } else {
                maquina->estado_atual = 1;
            }
            break;
            
        case 2:
            if (eh_digito(entrada)) {
                maquina->estado_atual = 2;
            } else {
                if (entrada == ' ' || entrada == '\n') {
                    maquina->estado_atual = 4;
                } else {
                    if ( entrada == '.') {
                        maquina->estado_atual = 3;
                    } else {
                        maquina->estado_atual = 1;
                    }
                }
            }
            break;
            
        case 3:
            if (eh_digito(entrada)) {
                maquina->estado_atual = 3;
            } else {
                if (entrada == ' ' || entrada == '\n') {
                    maquina->estado_atual = 4;
                } else {
                    maquina->estado_atual = 1;
                }
            }
            break;
        
        case 4:
            break;
    }
    return (maquina->estado_atual);
}


int main() {
    char buffer_in[TAM_MAX];
    int pointer;
    int achei_inteiro;
    
    for (int i=0; i<TAM_MAX; i++) buffer_in[i] = '\0';
    
    pointer = 0;
    char c;
    
    do {
        c=getchar();
        buffer_in[pointer++] = c;
    } while (c != '\n');
    
    fsm maquina;
    maquina.estado_atual = 0;
    
    pointer = 0;
    achei_inteiro = 0;
    float soma = 0;
    char numero[TAM_MAX];
    for (int i=0; i<TAM_MAX; i++) numero[i] = '\0';
    int dig = 0;
    while (buffer_in[pointer] != '\0') {
        
        opera_fsm((void*) (&maquina), buffer_in[pointer]);
        if (maquina.estado_atual == 0 || maquina.estado_atual == 2 || maquina.estado_atual == 3) {
            numero[dig] = buffer_in[pointer];
            dig++;
        } else {
            if(maquina.estado_atual == 4) {
                float val;
                numero[dig] = '\0';
                val = atof(numero);
                soma = soma + val;
                for (int i=0; i<100; i++) numero[i] = '\0';
                
                maquina.estado_atual = 0;
                dig = 0;
            }
        }
        pointer++;
    }
    printf("%g\n",soma);
    
    return 0;
}
