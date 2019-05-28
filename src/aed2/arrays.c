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
 * Converte uma lista para array
 * @param list
 */
double arrayPesquisaSequencial(t_datanode array[], t_id tamanho) {
    
     if(tamanho>0){
        t_id buscarId = lerInteiro("Insira o id do Registo que deseja buscar:",0,-1);
        t_id encontrado = -1;
        clock_t begin = clock();
        if ((encontrado = buscaSeq(array, tamanho, buscarId))>=0) {
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
 * Pesquisa binária de arrays
 * @param arrayNode
 * @param arraySize
 * @param buscarId
 * @return 
 */
t_id buscaSeq(t_datanode arrayNode[], t_id arraySize, t_id buscarId) {
    t_id idEncontrado = -1;
    for (t_id f=0; f < arraySize;f++) {
        if ( arrayNode[f].id == buscarId){
            idEncontrado = f;
            break;
        }
    }
    return idEncontrado;
}

/**
 * Cria um array a partir de uma lista
 * @param list
 * @return 
 */
t_datanode * criaArray(t_list* list) {
    // Time show
    clock_t begin = clock();
    double time_spent = 0;
    clock_t end = clock();
    
    
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
        
        // Mostra de 10000 em 10000
        if ((i % 10000) == 0) {
            int perc = i * 100 / tamanho;
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("[PERC %d%%][Inserções %" PRIu64 "][%d OPS/S][%d TOTAL SEC][%d ETA SEC]" ,
                    perc ,
                    i , 
                    (time_spent>0) ? (int)(i / time_spent) : (int)0 , 
                    (int)time_spent,
                    (time_spent>0) ? (int)((tamanho - i) / (i / time_spent)) : (int)0
                    );
            printf("]\n\033[F\033[J"); 
        }  
    }
    printf("\n");
    end = clock();
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
