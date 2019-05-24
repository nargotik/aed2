#include "headers.h"


//Principal
int main() {
	setlocale(LC_ALL, "");
	List* l = createList();
	Dashboard(l);

	printf("\nPrima 'ENTER' para sair.\n");
	
	getchar();
	return 0;
}
