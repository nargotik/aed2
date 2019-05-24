/* 
 * File:   ui.h
 * 
 * Created on 25 de Maio de 2019
 */

#ifndef FUNCOES13_H
#define FUNCOES13_H

#include <stdio.h>
typedef struct datahora_t {
    int dia;
    int mes;
    int ano;
    int hr;
    int min;
    int seg;
} datahora_t;

// Function declaration 
int lerInteiro(char* msg, int min, int max);
char lerChar(char* msg, char* rule);
char* lerString(char* msg);
void mostraCabecalho(char* msg);
void mostraRodape(char* msg);
void mostraOpcao(int opcao,char* msg);
void notice(char* msg);
void err(char* msg);
void clearScreen();

datahora_t lerDiaMesAno();
int fsize(FILE *fp);

#endif /* FUNCOES13_H */

