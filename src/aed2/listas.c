#include "headers.h"
#include "../shared/ui.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "arrays.h"
#include "listas.h"
#include "files.h"


/**
 * Cria uma losta
 * @return 
 */
t_list* createList(){
    t_list* list = (t_list*) malloc(sizeof(t_list));
    list->size = 0;
    list->head = NULL;
    return list;
}

/**
 * Insere um valor na lista
 * @param list
 */
void pushSingular(t_list* list){
    t_datanode reg;
    t_id tamanho = list->size;
    //DataNode regHead; = list->&head;
    reg.humidade     = lerInteiro("Insira o valor da humidade para armazenar:",1,100);
    reg.temperatura  = lerInteiro("Insira o valor da temperatura para armazenar:",-30,60);

    reg.id      = tamanho;
    reg.data    = getDataTime();
    push(list, reg);

    // Mostra o tamanho da lista
    printSize(list);
    mostraTexto("Item adicionado com sucesso!");
}

/**
 * Mostra o tamanho de uma lista pelo list->size dela
 * @param list
 */
void printSize(t_list* list) {
    mostraCabecalho("--- Tamanho da lista gerada ---");
    mostraTexto(
            "Bytes:       \t%.2f B\n"
            "MBytes:      \t%.2f MB\n"
            "GBytes:      \t%.2f GB\n"
            "Nodos Total: \t%" PRIu64, 
            ((sizeof(t_datanode)*(list->size))/pow(1024,1)),
            ((sizeof(t_datanode)*(list->size))/pow(1024,2)),
            ((sizeof(t_datanode)*(list->size))/pow(1024,3)),
            list->size
        );
    mostraRodape("--- Tamanho da lista gerada ---");
}

/**
 * Coloca um nodo novo no final da lista
 * @param list
 * @param dataParam
 */
void push(t_list* list, t_datanode dataParam){
    // Cria um novo nodo
    t_node* node = (t_node*)malloc(sizeof(t_node));
    
    node->data = dataParam;
    node->next = list->head;
    
    list->head = node;
    list->size++;
}

/**
 * Adiciona um nodo no fim da lista
 * @param list
 * @param dataParam
 */
void append(t_list* list, t_datanode dataParam) {
    t_node* node = (t_node*)malloc(sizeof(t_node));
    
    t_node* pointer = list->head;
    node->data  = dataParam;
    node->next = NULL;
    
    if (pointer == NULL) {
       list->head = node;
       return;
    }  

    while (pointer != NULL)
        pointer = pointer->next;

    pointer->next = node;
    return;    
}


/**
 * Imprime a lista
 * @param list
 */
void printList(t_list* list){
    if(isEmpty(list)){
        mostraTexto("Lista vazia!");
        return;
    }
    t_node* pointer = list->head;
    while(pointer != NULL){
        // Mostra o nodo currente
        mostraNodo(&pointer->data);
        pointer = pointer->next;
    }
}

/**
 * Mostra um nodo da lista
 * @param pointer
 */
void mostraNodo(t_datanode* pointer) {
    mostraCabecalho("--- Dados ID [ %" PRIu64 " ] ---", pointer->id);
    mostraTexto("Humidade    :\t %d", pointer->humidade);
    mostraTexto("Temperatura :\t %d", pointer->temperatura);
    mostraTexto("Hora        :\t %d:%d:%d",
            pointer->data.hora, 
            pointer->data.min, 
            pointer->data.seg
            );
    mostraRodape("--- ID [%d] ---", pointer->id);
}

/**
 * 
 * @param list
 */
void pop(t_list* list){
    if (isEmpty(list)) {
        mostraTexto("Lista Vazia");
        return;
    }
    
    t_node* pointer = list->head;
    // Mostra o ultimo nodo

    mostraNodo(&pointer->data);
    list->head = pointer->next;
    free(pointer);
    list->size--;
}

/**
 * Verifica se uma lista está vazia
 * @param list
 * @return 
 */
bool isEmpty(t_list* list){
    return list->size == 0;
}

/**
 * 
 * @param list
 */
void pushAuto(t_list* list){
    int opcao = 0;
    uint64_t i = 0;
    mostraCabecalho("--- MENU GERACAO DADOS ---");
    mostraOpcao(0," Voltar <<<<");
    mostraOpcao(1," Inserir     10.000 registos");
    mostraOpcao(2," Inserir     50.000 registos");
    mostraOpcao(3," Inserir    100.000 registos");
    mostraOpcao(4," Inserir  1.000.000 registos");
    mostraOpcao(5," Inserir 10.000.000 registos");
    mostraOpcao(6," Inserir numero manual de registos");
    mostraRodape("--- MENU GERACAO DADOS ---");
    opcao = lerInteiro("OPCAO:",0,6);
    switch(opcao) {
        case 0 :
           Dashboard(list);
           break;
        case 2 :
           i = 50000;
           break;
        case 6 :
          i = ler_uint64("Insira a quantidade de registos a serem gerados: ",0,-1);
          // Return to dashboard
          break;
        default :
            i = (opcao > 2) ? 10000 * pow(10,(opcao - 2)) : 10000;
          break;
    }
    

    // Ciclo de inseção e contagem do tempo
    double tempo = cicloInserir(list, i);
    
    // Mostra o tamanho da lista gerada
    printSize(list);
    mostraTexto("Lista gerada com sucesso... (%.2f ms)",tempo);
}

/**
 * Ciclo que insere dados random na lista
 * @param list
 * @param i
 * @return 
 */
double cicloInserir(t_list* list, t_id i) {
    clock_t begin = clock();
    
    t_datanode reg;
    t_id tamanho_anterior = list->size;
    double time_spent = 0;
    clock_t end = clock();
    for(t_id f = 0; f < i; f++){
        reg.id = f + tamanho_anterior;
        reg.humidade = randomNumber(0,100);
        reg.temperatura = randomNumber(-10,60);
        reg.data = getDataTime();
        push(list, reg);
        
        // Mostra de 10000 em 10000
        if ((f % 10000) == 0) {
            int perc = f * 100 / i;
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("[PERC %d%%][Inserções %" PRIu64 "][%d OPS/S][%d TOTAL SEC][%d ETA SEC]" ,
                    perc ,
                    f , 
                    (time_spent>0) ? (int)(f / time_spent) : (int)0 , 
                    (int)time_spent,
                    (time_spent>0) ? (int)((i - f) / (f / time_spent)) : (int)0
                    );
            printf("]\n\033[F\033[J"); 
        }
    }
    printf("\n");
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
    return time_spent;
    
}

/**
 * Retorna o DReg struct da data actual
 * @return 
 */
t_datereg getDataTime() {
    t_datereg reg;
    time_t relogio = time(NULL);
    struct tm *sRelogio = localtime(&relogio);

    reg.hora = sRelogio->tm_hour;
    reg.min = sRelogio->tm_min;
    reg.seg = sRelogio->tm_sec;
    reg.dia = sRelogio->tm_mday +1;
    reg.mes = sRelogio->tm_mon + 1;
    reg.ano = sRelogio->tm_year + 1900;

    return reg;
}
