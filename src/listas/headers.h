#pragma once

#ifndef functions
#define functions

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
//#include <Windows.h>
#include <time.h>
#include <inttypes.h>

#pragma warning (disable : 4996)

#pragma region CONSTANTES GLOBAIS

typedef int64_t t_id;

typedef struct {
	int dia;	//mday        
	int mes;	//tm_mon  -> lembrar de add 1     
	int ano;	//tm_year
	int hora;	//tm_hour
	int min;	//tm_min
	int seg;	//tm_sec
} t_datereg;

typedef struct {
	t_id id;
	int humidade;
	int temperatura;
	t_datereg data;
} t_datanode;

typedef struct node {
	t_datanode data;
	//usamos o struct node para fazer a 
        // recursividade pq "Node" ainda nao esta definido
	struct node* next;
} t_node;

typedef struct {
	t_id size;
	t_node* head;
} t_list;



#define LISTA_FILENAME "list.dat"
#define ARRAY_FILENAME "list.dat"

#pragma endregion

#pragma region VARIÁVEIS GLOBAIS

#pragma endregion

#pragma region DECLARAÇÃO DE FUNÇÕES


void Dashboard(t_list* list);

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

/*Ordena array */
void converteArray(t_list* list);

void pushSingular(t_list* list);

t_id buscaBin(t_datanode arrayNode[], t_id arraySize, t_id buscarId);

int randomNumber(int min_num, int max_num);

double cicloInserir(t_list* list, t_id i);

void bubbleSort(t_datanode arr[], int n);

void swap(t_datanode *a,t_datanode *b);

t_datanode * criaArray(t_list* list);

double arrayPesquisaBinaria(t_datanode array[], t_id tamanho);

double arrayConverte(t_list* list);
double arrayDesordena(t_datanode *array, t_id tamanho);
double arrayOrdenabubbleSort(t_datanode arr[], t_id n);

#pragma endregion

#endif //!functions
