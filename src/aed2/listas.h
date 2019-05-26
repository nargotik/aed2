/* 
 * File:   listas.h
 * 
 * Created on 26 de Maio de 2019, 23:32
 */

#ifndef LISTAS_H
#define LISTAS_H

#include "headers.h"
#include "arrays.h"

extern t_datanode *arrayDeNodos;
extern t_id tamanho_array;
extern int array_ordenado;

void pushSingular(t_list* list);

t_id buscaBin(t_datanode arrayNode[], t_id arraySize, t_id buscarId);

double cicloInserir(t_list* list, t_id i);

/*Cria uma lista e retorna um ponteiro de List*/
t_list* createList();

void printSize(t_list* list);

/*Imprime a lista*/
void printList(t_list* list);

/*Insere um node no topo*/
void push (t_list* list, t_datanode dataParam);

/*Mostra um nodo*/
void mostraNodo(t_datanode* pointer);

/*Remove o primeiro elemento da lista*/
void pop(t_list* list);

/*Verifica se a lista está vazia*/
bool isEmpty(t_list* list);

void pushAuto (t_list* list);

int genSeqRandom(int i);

t_datereg getDataTime();


#endif /* LISTAS_H */

