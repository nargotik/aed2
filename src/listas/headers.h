#pragma once

#ifndef functions
#define functions

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
//#include <Windows.h>
#include <time.h>

#pragma warning (disable : 4996)

#pragma region CONSTANTES GLOBAIS

typedef struct dReg {
	int dia;	//mday        
	int mes;	//tm_mon  -> lembrar de add 1     
	int ano;	//tm_year
	int hora;	//tm_hour
	int min;	//tm_min
	int seg;	//tm_sec
}DReg;

typedef struct dataNode{
	int id;
	int umidade;
	int temperatura;
	DReg data;
}DataNode;

typedef struct node{
	DataNode data;
	//usamos o struct node para fazer a recursividade pq "Node" ainda nao esta definido
	struct node* next;
}Node;

typedef struct list{
	long long size;
	Node* head;
}List;


#pragma endregion

#pragma region VARIÁVEIS GLOBAIS

#pragma endregion

#pragma region DECLARAÇÃO DE FUNÇÕES

void Dashboard(List* list);

/*Cria uma lista e retorna um ponteiro de List*/
List* createList();

/*Imprime a lista*/
void printList(List* list);

/*Insere um node no topo*/
void push (List* list, DataNode dataParam);

/*Remove o primeiro elemento da lista*/
void pop(List* list);

/*Verifica se a lista está vazia*/
bool isEmpty(List* list);

void pushAuto (List* list);

int genSeqRandom(int i);

DReg getDataTime();

void pushSingular(List* list);

#pragma endregion

#endif //!functions
