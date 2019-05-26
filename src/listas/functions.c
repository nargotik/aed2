#include "headers.h"
#include "../shared/ui.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "arrays.h"
#include "listas.h"

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
          array_ordenado = 1;
        } else {
            mostraTexto("Array já Ordenado ou Vazio");
        }
        
        
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
    }
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

