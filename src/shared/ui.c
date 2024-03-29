/*!
 * @header      ui.c
 * @version     1.0 25 de Maio de 2019
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // exit()
#include<stdarg.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#include "ui.h"

/**
 * Le um inteiro
 * @param msg
 * @return 
 */
int lerInteiro(char* msg, int min, int max) {
    if (max<min) {
        min = -(int)((unsigned int)~0 >>1) -1;
        max = (int)((unsigned int)~0 >> 1);
    }
    int numero=0;
    int res = 0;
    do { 
        printf("%s",msg);
        res = scanf(" %d", &numero);   // res=1 se valor válido
        getchar();
        if (res==0 || !(numero>=min && numero<=max)) puts("Valor inválido!");
    } while (res != 1 || !(numero>=min && numero<=max) )  ;
    return(numero);
}

/**
 * Le um inteiro
 * @param msg
 * @return 
 */
uint64_t ler_uint64(char* msg, uint64_t min, uint64_t max) {
    if (max<min) {
        min = 0;
        max = (uint64_t)~0;
    }
    uint64_t numero=0;
    uint64_t res = 0;
    do { 
        printf("%s",msg);
        res = scanf(" %" PRIu64, &numero);   // res=1 se valor válido
        getchar();
        if (res==0 || !(numero>=min && numero<=max)) puts("Valor inválido!");
    } while (res != 1 || !(numero>=min && numero<=max) )  ;
    return(numero);
}

/**
 * Le um char mediante regras de scanf
 * @param msg
 * @param rule
 * @return 
 */
char lerChar(char* msg, char* rule) {
    char sentinela='-';
    int res = 0;
    do { 
        printf("%s",msg);
        res = scanf(rule, &sentinela);   // res=1 se o sentinela estiver nos parametros
        getchar();
        if (res==0) puts("Valor inválido!");
    } while (res != 1);
    return(toupper(sentinela));
}


/**
 * Mostra opcao 
 * @param msg
 */
void mostraOpcao(int opcao,char* msg) {
    printf("   %d - %s\n",opcao,msg);
}

/*
 * Limpa o ecra
 */
void clearScreen() {
#ifdef LINUX
    // Limpa o ecrã
    printf("\x1B[2J");
    // Põe o cursor no topo
    printf("\x1B[1H");
    //(void)system("clear");
#endif
#ifdef WINDOWS
    // Limpa o ecrã
    printf("\x1B[2J");
    // Põe o cursor no topo
    printf("\x1B[1H");
    //(void)system("cls");
#endif
}

/**
 * Mostra um erro 
 * @param msg
 */
void err(char* msg) {
    fprintf(stderr, msg);
    exit(0);
}

/**
 * Mostra uma notice
 * @param msg
 */
void mostraTexto(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    vfprintf(stdout, msg, args);
    printf("\n");
    va_end(args);
}

/**
 * Mostra um cabeçalho 
 * @param msg
 */
void mostraCabecalho(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    printf("==========");
    vfprintf(stdout, msg, args);
    va_end(args);
    printf("==========\n");
}

/**
 * Mostra um rodape mostrar == do tamanho da msg
 * @param msg
 */
void mostraRodape(const char *msg, ...) {
    printf("==========");
    int tam = strlen(msg);
    for (int i = 0; i < tam; i++) {
        printf("=");
    }
    printf("==========\n");
}

/**
 * Ler um dia mes e ano
 * @return 
 */
datahora_t lerDiaMesAno() {
    datahora_t aux;
    aux.dia = lerInteiro("Insere o Dia [1-31]:",1,31);
    aux.mes = lerInteiro("Insere o Mes [1-12]:",1,12);
    aux.ano = lerInteiro("Insere o Ano [2010-2099]:",2010,2099);
    return aux;
}

