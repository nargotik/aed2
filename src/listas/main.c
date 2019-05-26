#include "headers.h"

//Principal
int main() {
	setlocale(LC_ALL, "");
	t_list* lista = createList();
	Dashboard(lista);

	printf("\nPrima 'ENTER' para sair.\n");
	
	getchar();
	return 0;
}
