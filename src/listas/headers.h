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

int randomNumber(int min_num, int max_num);



#pragma endregion

#endif //!functions
