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

const t_datanode dataUtil;

t_datanode *arrayDeNodos;
t_id tamanho_array = 0;
int array_ordenado = 1;


/**
 * Dashboard do programa
 * @param list
 */
void Dashboard(t_list* list){
    t_id buscarId;
    t_datanode encontrado;
    double time_spent = 0;
    clock_t begin = clock();
    clock_t end = clock();

    //time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
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
    mostraOpcao(8,"Arrays => Pesquisa Sequencial");
    mostraOpcao(9,"Arrays => Desordena Array");
    mostraOpcao(10,"Arrays => Ordena Array (BubleSort)");
    mostraOpcao(11,"Files => Grava Lista");
    mostraOpcao(12,"Files => Lê Lista");
    mostraOpcao(13,"Files => Re-Inicializa Ficheiro");
    mostraOpcao(14,"Files => Pesquisa Binária");
    mostraOpcao(15,"Files => Pesquisa Sequencial ");
    //mostraOpcao(6,"Ficheiro => Carregar");
    //mostraOpcao(7,"Ficheiro => Salvar");
    mostraRodape("--- MENU PRINCIPAL ---");
    opcao = lerInteiro("OPCAO:",0,15);
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
        mostraTexto("Pesquisa efectuada em (%.2f ms)",tempo);
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 8:
        tempo = arrayPesquisaSequencial(arrayDeNodos,tamanho_array);
        mostraTexto("Pesquisa efectuada em (%.2f ms)",tempo);
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 9:
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
      case 10:
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
      case 11:
        removeFicheiro(); 
        t_id escritas = writeLeituras(list);
        mostraTexto("%"PRIu64 "Registos gravados com sucesso ... ", escritas);
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 12:
        mostraTexto("%"PRIu64 "Registos lidos com sucesso ... ", readLeituras(list));
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 13:
        removeFicheiro(); 
        mostraTexto("Ficheiro removido ");
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 14:
        // Pesquisa binária feita
        buscarId = ler_uint64("Insira o id do Registo que deseja buscar:",0,-1);
        
        begin = clock();
        encontrado = filebuscaBin(buscarId);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
        
        if (encontrado.id == buscarId) {
            mostraTexto("Encontrado...");
            mostraNodo(&encontrado);
        }
        mostraTexto("Pesquisa efectuada em (%.2f ms)",time_spent);
        getchar();
        // Return to dashboard
        Dashboard(list);
        break;
      case 15:
        // Pesquisa binária feita
        buscarId = ler_uint64("Insira o id do Registo que deseja buscar:",0,-1);
        
        begin = clock();
        encontrado = filebuscaSeq(buscarId);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
        
        if (encontrado.id == buscarId) {
            mostraTexto("Encontrado...");
            mostraNodo(&encontrado);
        }
        mostraTexto("Pesquisa efectuada em (%.2f ms)",time_spent);
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

