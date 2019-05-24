#include "headers.h"


//Principal
int main() {
	setlocale(LC_ALL, "");
	List* l = createList();
	DataNode data;

	Dashboard(l);

	printf("\nPrima 'ENTER' para sair.\n");
	
	getchar();
	return 0;
}
