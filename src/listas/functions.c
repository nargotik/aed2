#include "headers.h"
#include "../shared/ui.h"
#include "../shared/helper.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

const t_datanode dataUtil;

t_datanode *arrayDeNodos;
t_id tamanho_array = 0;
int array_ordenado = 1;

/**
 * Dashboard do programa
 * @param list
 */
void Dashboard(t_list* list){
    int opcao=0;
    double tempo = 0;
    clearScreen();
    mostraCabecalho("--- DADOS LISTA ---");
    mostraTexto("TAMANHO LISTA         : %" PRIu64, list->size);
    mostraTexto("TAMANHO ARRAY         : %" PRIu64, tamanho_array);
    mostraTexto("ARRAY (%s)" , (array_ordenado == 1) ? "ORDENADO": "DESORDENADO");
    mostraTexto("");
    mostraCabecalho("--- MENU PRINCIPAL ---");
    mostraOpcao(0,"Sair");
    mostraOpcao(1,"Lista => Inserir Item");
    mostraOpcao(2,"Lista => Remover Item");
    mostraOpcao(3,"Lista => Imprimir Lista");
    mostraOpcao(4,"Lista => Gerar Dados automaticamente");
    mostraOpcao(5,"Arrays => Converter Lista para Array");
    mostraOpcao(6,"Arrays => Destruir Array");
    mostraOpcao(7,"Arrays => Pesquisa Binária");
    mostraOpcao(8,"Arrays => Desordena Array");
    mostraOpcao(9,"Arrays => Ordena Array (BubleSort)");
    //mostraOpcao(6,"Ficheiro => Carregar");
    //mostraOpcao(7,"Ficheiro => Salvar");
    mostraRodape("--- MENU PRINCIPAL ---");
    opcao = lerInteiro("OPCAO:",0,9);
    switch(opcao) {
      case 0:
         break;
      case 1:
        pushSingular(list);
        getchar();getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 2:
        pop(list);
        getchar();getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 3:
        printList(list);
        getchar();
        // Return to dashboard
        Dashboard(list);
         break;
      case 4:
        pushAuto(list);
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 5:
        tempo = arrayConverte(list);
        // Mostra o tamanho da lista gerada
        mostraTexto("Array convertido com sucesso... (%.2f ms)",tempo);
        array_ordenado = 1;
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 6:
        free(arrayDeNodos);
        tamanho_array = 0;
        // Mostra o tamanho da lista gerada
        mostraTexto("Array destruido com sucesso... (0.00 ms)",tempo);
        array_ordenado = 1;
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 7:
        tempo = arrayPesquisaBinaria(arrayDeNodos,tamanho_array);
        mostraTexto("Pesquisa efectuada em (0.00 ms)",tempo);
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 8:
        if (array_ordenado==1) {
            tempo = arrayDesordena(arrayDeNodos,tamanho_array);
            mostraTexto("Array desordenado com sucesso... (%.2f ms)",tempo);
            array_ordenado = 0;
        } else {
            mostraTexto("Array já Desordenado ou Vazio");
        }
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 9:
        if (array_ordenado==0) {
          tempo = arrayOrdenabubbleSort(arrayDeNodos,tamanho_array);
          mostraTexto("Array ordenado com sucesso... (%.2f ms)",tempo);
          array_ordenado = 0;
        } else {
            mostraTexto("Array já Ordenado ou Vazio");
        }
        
        
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
    }
}
/*
double ListmediaTemperatura(t_list* list) {
    // @todo list vs array
    return 0;
}
double ListmediaHumidade(t_list* list) {
    // @todo
    return 0;
}
double ListmaxTemperatura(t_list* list) {
    // @todo
    return 0;
}
double ListmaxHumidade(t_list* list) {
    // @todo
    return 0;
}
double ListminTemperatura(t_list* list) {
    // @todo
    return 0;
}
double ListminHumidade(t_list* list) {
    // @todo
    return 0;
}
double ListcontaNodos(t_list* list) {
    // @todo
    return 0;
}
void ListOrdena(t_list* list) {
    // @todo
}
void ListProcura(t_list* list, t_id id) {
    // @todo
}
*/
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
    //DataNode regHead; = list->&head;
    reg.humidade     = lerInteiro("Insira o valor da humidade para armazenar:",1,100);
    reg.temperatura  = lerInteiro("Insira o valor da temperatura para armazenar:",-30,60);

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
    for(t_id f = 0; f < i; f++){
        reg.id = f + tamanho_anterior;
        reg.humidade = randomNumber(0,100);
        reg.temperatura = randomNumber(-10,60);
        reg.data = getDataTime();
        push(list, reg);
    }
    
    clock_t end = clock();
    double time_spent = 0;
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
    return time_spent;
    
}

/**
 * Gera um numero random
 * @param min_num
 * @param max_num
 * @return 
 */
int randomNumber(int min_num, int max_num) {
    int result = 0;
    srand(time(NULL));
    result = rand() % max_num + min_num;
    return result;
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

/**
 * Pesquisa binária de arrays
 * @param arrayNode
 * @param arraySize
 * @param buscarId
 * @return 
 */
t_id buscaBin(t_datanode arrayNode[], t_id arraySize, t_id buscarId) {
    t_id idEncontrado = -1;
    
    t_id min = 0;
    t_id meio= 0;
    t_id max = (arraySize - 1);
    int iteracoes = 0;
    while( (idEncontrado == -1 )  && (max >= min) ){
        iteracoes++;
        meio = (min + max) / 2;
        if ( arrayNode[meio].id == buscarId){
            idEncontrado = meio;
        } else{
            if (arrayNode[meio].id > buscarId ){
                min = meio + 1;
            } else {
                max = meio - 1;
            }
        }
    }
    return idEncontrado;
}

/**
 * Converte uma lista para array
 * @param list
 */
double arrayConverte(t_list* list) {

    if(!isEmpty(list)){
        
        clock_t begin = clock();
        free(arrayDeNodos);
        // Cria o array a partir da lista
        arrayDeNodos = criaArray(list);

        clock_t end = clock();
        double time_spent = 0;
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
        return time_spent;
        
    } else{
        mostraTexto("A lista está vazia.");
        return -1;
    }
}


/**
 * Converte uma lista para array
 * @param list
 */
double arrayPesquisaBinaria(t_datanode array[], t_id tamanho) {
    
    if (array_ordenado == 0) {
        mostraTexto("O array deve estar ordenado para fazer pesquisa binária");
        return -1;
    }
    
    if(tamanho>0){
        t_id buscarId = lerInteiro("Insira o id do Registo que deseja buscar:",0,-1);
        t_id encontrado = -1;
        clock_t begin = clock();
        if ((encontrado = buscaBin(array, tamanho, buscarId))>=0) {
            mostraTexto("Encontrado!");
            mostraNodo(&array[encontrado]);
        } else {
            mostraTexto("Nenhum registo encontrado.");
        }      
        
        clock_t end = clock();
        double time_spent = 0;
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
        return time_spent;
    } else{
        mostraTexto("O Array está vazio.");
        return 0;
    }
}

/**
 * Cria um array a partir de uma lista
 * @param list
 * @return 
 */
t_datanode * criaArray(t_list* list) {
    t_datanode *array_gerado;
    t_id tamanho = list->size;
    t_id i = 0;
    array_gerado = (t_datanode*) calloc(tamanho, sizeof(t_datanode));
    
    t_node* pointer = list->head;

    while(pointer != NULL){
        t_datanode dataItem = pointer->data;
        array_gerado[i] = dataItem;
        pointer = pointer->next;
        i++;
    }
    tamanho_array = list->size;
    return array_gerado;   
}

/**
 * Desordena um array
 * @param array
 * @param tamanho
 * @return 
 */
double arrayDesordena(t_datanode array[], t_id tamanho) {
    if (tamanho > 1) {
        clock_t begin = clock();
        t_id i;
        for (i = 0; i < tamanho - 1; i++) 
        {
          t_id j = i + rand() / (RAND_MAX / (tamanho - i) + 1);
          t_datanode t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
        clock_t end = clock();
        double time_spent = 0;
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
        return time_spent;
    }
    return 0;
}

/**
 * Ordena um array por bubble sort
 * @param arr
 * @param n
 * @return 
 */
double arrayOrdenabubbleSort(t_datanode arr[], t_id n) { 
    clock_t begin = clock();
    int i, j; 
    for (i = 0; i < n-1; i++)       
        for (j = 0; j < n-i-1; j++)  
            if (arr[j].id > arr[j+1].id) 
               swap(&arr[j], &arr[j+1]); 
    clock_t end = clock();
    double time_spent = 0;
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
    return time_spent;
}

/**
 * Troca dois nodos de um array
 * @param a
 * @param b
 */
void swap(t_datanode *a,t_datanode *b) {
    t_datanode temp = *a;
    *a = *b;
    *b = temp;
}

