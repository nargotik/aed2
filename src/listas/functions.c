#include "headers.h"
#include "../shared/ui.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

const DataNode dataUtil;

/**
 * 
 * @param list
 */
void Dashboard(List* list){
    int opcao=0;
    clearScreen();
    mostraCabecalho("--- MENU PRINCIPAL ---");
    mostraOpcao(0,"Sair");
    mostraOpcao(1,"Inserir Item");
    mostraOpcao(2,"Remover Item");
    mostraOpcao(3,"Imprimir Lista");
    mostraOpcao(4,"Gerar Dados automaticamente");
    mostraOpcao(5,"Converter Array e realizar busca Binária");
    mostraRodape("--- MENU PRINCIPAL ---");
    opcao = lerInteiro("OPCAO:",0,5);
    switch(opcao) {
      case 0 :
         break;
      case 1 :
        pushSingular(list);
        getchar();getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 2 :
        pop(list);
        getchar();getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 3 :
        printList(list);
        getchar();getchar();
        // Return to dashboard
        Dashboard(list);
         break;
      case 4 :
        pushAuto(list);
        getchar();getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 5 :
        converteArray(list);
        getchar();getchar();
        // Return to dashboard
        Dashboard(list);
        break;
    }
}

/**
 * 
 * @return 
 */
List* createList(){
    List* list = (List*) malloc(sizeof(List));
    list -> size = 0;
    list -> head = NULL;
    return list;
}

/**
 * 
 * @param list
 */
void pushSingular(List* list){
    DataNode reg;
    //DataNode regHead; = list->&head;
    reg.umidade     = lerInteiro("Insira o valor da humidade para armazenar:",1,100);
    reg.temperatura = lerInteiro("Insira o valor da temperatura para armazenar:",1,60);

    reg.id      = 1;
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
void printSize(List* list) {
    mostraCabecalho("--- Tamanho da lista gerada ---");
    mostraTexto("Bytes:\t%.2fBytes\n"
            "MBytes:\t%.2f\n"
            "GBytes:\t%.2f\n", 
            ((sizeof(DataNode)*(list->size))/pow(1024,1)),
            ((sizeof(DataNode)*(list->size))/pow(1024,2)),
            ((sizeof(DataNode)*(list->size))/pow(1024,3))
        );
    mostraRodape("--- Tamanho da lista gerada ---");
}

/**
 * Coloca um nodo novo no final da lista
 * @param list
 * @param dataParam
 */
void push(List* list, DataNode dataParam){
    // Cria um novo nodo
    Node* node = (Node*) malloc(sizeof(Node));
    
    node->data = dataParam;
    node->next = list->head;
    list->head = node;
    list->size++;
}

/**
 * 
 * @param list
 */
void printList(List* list){
    if(isEmpty(list)){
        mostraTexto("Lista vazia!");
        return;
    }
    Node* pointer = list->head;
    while(pointer != NULL){
        // Mostra o nodo currente
        mostraNodo(pointer);
        pointer = pointer->next;
    }
}

void mostraNodo(Node* pointer) {
    mostraCabecalho("--- Dados ID [%d] ---", pointer->data.id);
    mostraTexto("Humidade    :\t %d", pointer->data.umidade);
    mostraTexto("Temperatura :\t %d", pointer->data.temperatura);
    mostraTexto("Hora        :\t %d:%d:%d",
            pointer->data.data.hora, 
            pointer->data.data.min, 
            pointer->data.data.seg
            );
    mostraRodape("--- ID [%d] ---", pointer->data.id);
}

/**
 * 
 * @param list
 */
void pop(List* list){
    if (isEmpty(list)) {
        mostraTexto("Lista Vazia");
        return;
    }
    
    Node* pointer = list->head;
    // Mostra o ultimo nodo
    mostraNodo(pointer);
    list->head = pointer->next;
    free(pointer);
    list->size--;
}

/**
 * 
 * @param list
 * @return 
 */
bool isEmpty(List* list){
    return list->size == 0;
}

/**
 * 
 * @param list
 */
void pushAuto(List* list){
    long long i, f;
    mostraTexto("Insira a quantidade de registos a serem gerados: ");
    scanf(" %lld",&i);

    DataNode reg;
    for(f=0;f<i;f++){
        reg.id = f;
        reg.umidade = genSeqRandom(f*2);
        reg.temperatura = genSeqRandom(f*3);
        reg.data = getDataTime();
        push(list, reg);
    }
    // Mostra o tamanho da lista gerada
    printSize(list);
    mostraTexto("Lista gerada com sucesso...");
}

/**
 * 
 * @param i
 * @return 
 */
int genSeqRandom(int i) {
    int min = 0;
    int max = 30;

    time_t relogio = time(NULL);
    struct tm *sRelogio = localtime(&relogio);

    srand(sRelogio->tm_sec + i);

    return rand () % max + min;
}	

/**
 * 
 * @return 
 */
DReg getDataTime() {
    DReg reg;
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

void buscaBin(DataNode arrayNode[], int arraySize, int buscarId){
    int idEncontrado = 0;
    int min = 0;
    int meio= 0;
    int max = (arraySize - 1);

    while( (idEncontrado == 0 )  && (max >= min) ){
        meio = (min + max) / 2;
        if ( arrayNode[meio].id == buscarId){
            idEncontrado = 1;
            mostraTexto("Id encontrado !");
            mostraTexto("Posição no array: %d",meio);
            mostraTexto("Id              : %d", arrayNode[meio].id);
            mostraTexto("Umidade         : %d", arrayNode[meio].umidade);
            mostraTexto("Temperatura     : %d", arrayNode[meio].temperatura);
            mostraTexto("Hora            : %d:%d:%d\n", 
                    arrayNode[meio].data.hora, 
                    arrayNode[meio].data.min, 
                    arrayNode[meio].data.seg
                    );
        } else{
            if (arrayNode[meio].id > buscarId ){
                min = meio + 1;
            } else {
                max = meio - 1;
            }
        }
    }
    if (idEncontrado == 0){
        mostraTexto("Id não encontrado");
    }
}

/**
 *
 * @param list
 */
void converteArray(List* list) {
    // @todo .. tem de converter para o array ordenado senao a busca binária nao funciona
    if(!isEmpty(list)){
        int arraySize = (int)list->size, i = 0;
        struct dataNode arrayNode [arraySize];
        int buscarId = 0;
        Node* pointer = list->head;

        while(pointer != NULL){
            DataNode dataItem = pointer->data;
            arrayNode[i] = dataItem;
            pointer = pointer->next;
            i++;
        }
        buscarId = lerInteiro("Insira o id do Registo que deseja buscar:",0,999999999);
        buscaBin(arrayNode, i, buscarId);
    } else{
        mostraTexto("A lista está vazia.");
    }
}

