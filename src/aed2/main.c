#include "headers.h"
#include "listas.h"
#include "files.h"
#include <locale.h>

//Principal
int main() {
	setlocale(LC_ALL, "");
	t_list* lista = createList();
        
	Dashboard(lista);
	printf("\nPrima 'ENTER' para sair.\n");
	getchar();
	return 0;
}
