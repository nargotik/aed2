#include "headers.h"
#include "ui.h"
#include <stdlib.h>

void Dashboard(List* list){
	int opc = 0;
	DataNode data;
        clearScreen();
        mostraCabecalho("--- MENU PRINCIPAL ---");
        mostraOpcao(0,"Sair");
        mostraOpcao(1,"Inserir Item");
        mostraOpcao(2,"Remover Item");
        mostraOpcao(3,"Imprimir Lista");
        mostraOpcao(4,"Gerar Dados automaticamente");
        mostraRodape("--- MENU PRINCIPAL ---");
        int opcao = lerInteiro("OPCAO:",0,4);
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
        }
}

List* createList(){
	List* list = (List*) malloc(sizeof(List));
	list -> size = 0;
	list -> head = NULL;
	return list;
}

void pushSingular(List* list){

        DataNode reg;
        //DataNode regHead; = list->&head;
        reg.umidade = lerInteiro("Insira o valor da humidade para armazenar:",1,1);
        reg.temperatura = lerInteiro("Insira o valor da temperatura para armazenar:",1,1);

        reg.id = 1;
        reg.data = getDataTime();
        push(list, reg);

    	double tamLista = ((sizeof(DataNode)*(list->size))/1073741824);    //equivalente a 1 GB em Bytes

    	printf("\nItem adicionado com sucesso\n");
    	printf("\nTamanho da lista gerada: %.2f GB\n", tamLista);

}

void push (List* list, DataNode dataParam){
	Node* node = (Node*) malloc(sizeof(Node));

	node->data = dataParam;
	node->next = list->head;

	list->head = node;
	list->size++;
}

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
    }
}

bool isEmpty(List* list){
    return list->size == 0;
}

void pushAuto (List* list){
    long long i;
    printf("\nInsira a quantidade de registos a serem gerados\n\n");
    getchar();
    scanf(" %d", &i);

    for(int f=0;f<i;f++){
        DataNode reg;
        reg.id = f;
        reg.umidade = genSeqRandom(f*2);
        reg.temperatura = genSeqRandom(f*3);
        reg.data = getDataTime();
        push(list, reg);
    };
    double tamLista = ((sizeof(DataNode)*(list->size))/1073741824); //equivalente a 1 GB em Bytes
    printf("\nTamanho da lista gerada: %.2f GB", tamLista);
    printf("\nLista gerada com sucesso");
}

int genSeqRandom(int i) {
	int min = 0;
	int max = 30;
	
	time_t relogio = time(NULL);
	struct tm *sRelogio = localtime(&relogio);

	srand(sRelogio->tm_sec + i);

 	return rand () % max + min;
}	

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