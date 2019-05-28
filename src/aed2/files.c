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

#define LEITURAS_FILENAME "leituras.dat"

/**
 * Escreve uma leitura no fim do ficheiro de leituras
 * @param reading
 * @return 
 */
t_id writeLeitura(t_datanode* reading) {
  FILE *af;
  t_id nescritos=0;
  // Abertura para modo binário
  af = fopen(LEITURAS_FILENAME,"ab+");  
  if (af == NULL) {
      // Impossivel abrir o ficheiro ficheiro nao existe (Inicializa)
      nescritos = -1;
  } else{
    nescritos = fwrite(reading, sizeof(t_datanode), 1 , af);	
    fclose(af);
  }
  return nescritos; 
}

/**
 * Escreve leituas no fim do ficheiro de leituras
 * @param reading
 * @return 
 */
t_id writeLeituras(t_list* list) {
    if(isEmpty(list)){
        mostraTexto("Lista vazia!");
        return 0;
    }
    t_id nescritos=0;
    t_node* pointer = list->head;
    while(pointer != NULL){
        // Mostra o nodo currente
        nescritos += writeLeitura(&pointer->data);
        pointer = pointer->next;
    }
  //FILE *af;
  return nescritos; 
}

/**
 * Le as leituras do ficheiro
 * @param readings
 * @return numero de leituras lidas
 */
t_id readLeituras(t_list* list) {
  FILE *af;
  t_datanode reading;
  t_id nlidos;

  // Abertura para modo binário
  af = fopen(LEITURAS_FILENAME,"rb");
  if (af == NULL) {
      // Impossivel abrir o ficheiro ficheiro nao existe (Inicializa)
      nlidos = -1;
  } else {
    t_id i = 0;
    
    while (fread(&reading, sizeof(t_datanode), 1, af) == 1) {
        pushBool(list,reading);
        i++;
    };
    nlidos = i;
    list->size = nlidos;
    fclose(af);
  }
  return nlidos; 
}

/**
 * Verifica o Total de Leituras atraves do tamanho do ficheiro leituras
 * @return 
 */
t_id totalLeituras() {
    FILE *af;
    af = fopen(LEITURAS_FILENAME,"rb+");  
    t_id total_leituras = 0;
    if (af == NULL) {
      // Impossivel abrir o ficheiro ficheiro nao existe (Inicializa)
      total_leituras = -1;
    } else {
        total_leituras = fsize(af) / sizeof(t_datanode);
        fclose(af);
    } 
    printf("total leituras %"PRIu64, total_leituras);
    return total_leituras;
}

/**
 * Devolve o tamanho do ficheiro em Bytes
 * @param fp
 * @return 
 */
t_id fsize(FILE *fp){
    // Armazena a posição inicial para colocar após leitura
    t_id prev = ftell(fp);
    // Procura o fim do ficheiro
    fseek(fp, 0L, SEEK_END);
    // Armazena a posição do fim do ficheiro
    t_id sz = ftell(fp);
    // Volta a colocar no ponto inicial
    fseek(fp,prev,SEEK_SET);
    return sz;
}

void removeFicheiro() {
    remove(LEITURAS_FILENAME);
}