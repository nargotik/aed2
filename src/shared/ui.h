/* 
 * File:   ui.h
 * 
 * Created on 25 de Maio de 2019
 */

#ifndef UI_H
#define UI_H

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
void mostraCabecalho(const char *msg, ...);
void mostraRodape(const char *msg, ...);
void mostraOpcao(int opcao,char* msg);
void mostraTexto(const char *msg, ...);
void err(char* msg);
void clearScreen();

datahora_t lerDiaMesAno();
int fsize(FILE *fp);

#endif /* UI_H */

