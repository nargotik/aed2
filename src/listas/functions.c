#include "headers.h"
#include "ui.h"
#include <stdlib.h>

const DataNode dataUtil;

/**
 * 
 * @param list
 */
void Dashboard(List* list){
    int opcao = -1;
    while(opcao != 0){
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
            getchar();
            break;
          case 2 :
            pop(list);
            getchar();
            break;
          case 3 :
            printList(list);
            getchar();
             break;
          case 4 :
            pushAuto(list);
            getchar();
            break;
          case 5 :
            converteArray(list);
            getchar();
            break;
        }
        getchar();
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
    reg.umidade = lerInteiro("Insira o valor da humidade para armazenar:",1,100);
    reg.temperatura = lerInteiro("Insira o valor da temperatura para armazenar:",1,60);

    reg.id = 1;
    reg.data = getDataTime();
    push(list, reg);

    double tamLista = ((sizeof(DataNode)*(list->size))/1073741824);    //equivalente a 1 GB em Bytes

    printf("\nTamanho da lista gerada: %.2f GB\n", tamLista);
    printf("\nItem adicionado com sucesso!\n");

}

/**
 * 
 * @param list
 * @param dataParam
 */
void push (List* list, DataNode dataParam){
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
        printf("\nLista vazia.\n");
        return;
    }

    Node* pointer = list->head;
    printf("\n");
    while(pointer != NULL){
        printf("\nData id = %d", pointer->data.id);
        printf("\nData umidade = %d", pointer->data.umidade);
        printf("\nData temperatura = %d", pointer->data.temperatura);
        printf("\nHora: %d:%d:%d\n", pointer->data.data.hora, pointer->data.data.min, pointer->data.data.seg);
        pointer = pointer->next;
    }
}

/**
 * 
 * @param list
 */
void pop(List* list){
    if(!isEmpty(list)){
        Node* pointer = list->head;

        printf("\nData id = %d", pointer->data.id);
        printf("\nData umidade = %d", pointer->data.umidade);
        printf("\nData temperatura = %d", pointer->data.temperatura);
        printf("\nHora: %d:%d:%d\n", pointer->data.data.hora, pointer->data.data.min, pointer->data.data.seg);

        list->head = pointer->next;
        free(pointer);
        list->size--;
    }else{
        printf("\nLista Vazia\n");
        return;
    }
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
void pushAuto (List* list){
	long long i, f;
	printf("\nInsira a quantidade de registos a serem gerados:\n\n");
	scanf(" %lld",&i);

    DataNode reg;
	for(f=0;f<i;f++){
		reg.id = f;
		reg.umidade = genSeqRandom(f*2);
		reg.temperatura = genSeqRandom(f*3);
		reg.data = getDataTime();
		push(list, reg);
	}
	double tamLista = ((sizeof(DataNode)*(list->size))/1073741824); //equivalente a 1 GB em Bytes
	printf("\nTamanho da lista gerada: %.2f GB", tamLista);
	printf("\nLista gerada com sucesso\n");
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
	reg.dia = sRelogio->tm_mday+1;
	reg.mes = sRelogio->tm_mon + 1;
	reg.ano = sRelogio->tm_year + 1900;

	return reg;
}

void buscaBin (DataNode arrayNode[], int arraySize, int buscarId){
    int idEncontrado = 0;
	int min = 0;
	int meio= 0;
    int max = (arraySize - 1);

    while( (idEncontrado == 0 )  && (max >= min) ){
        meio = (min + max) / 2;
        if ( arrayNode[meio].id == buscarId){
			idEncontrado = 1;
			printf("\nId encontrado\n");
			printf("\nPosição no array: %d",meio);
			printf("\nId: %d", arrayNode[meio].id);
			printf("\nUmidade: %d", arrayNode[meio].umidade);
			printf("\nTemperatura: %d", arrayNode[meio].temperatura);
			printf("\nHora: %d:%d:%d\n", arrayNode[meio].data.hora, arrayNode[meio].data.min, arrayNode[meio].data.seg);
		} else{
			if (arrayNode[meio].id > buscarId ){
				min = meio + 1;
			} else{
				max = meio - 1;
			}
		}
    }
	if (idEncontrado == 0){
        printf("\nId não encontrado\n");
	}
}

/**
 *
 * @param list
 */
void converteArray(List* list) {

	if(!isEmpty(list)){
		int arraySize = (int)list->size, i = 0;
		struct dataNode arrayNode [arraySize];
		int buscarId = 0;
		Node* pointer = list->head;

		while(pointer != NULL){
			DataNode dataItem = pointer->data;
			arrayNode[i] = dataItem;
			pointer = pointer->next;
			//printf("\nId %d",arrayNode[i].id);
			i++;

		}
		printf("\nInsira o id do Registo que deseja buscar:\n");
		scanf("%d",&buscarId);
		buscaBin(arrayNode, i, buscarId);

	} else{
		printf("\nA lista está vazia.\n");
	}
}
