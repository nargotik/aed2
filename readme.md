# Relatório TP AED2
O presente software foi desenvolvido no contexto académico e deve ser utilizado sem qualquer garantia por conta e risco do utilizador.

O software realizado foi testado e compilado em sistema operativo Linux (kernel 4.9.130 | gcc versão 5.4.0) pelo que deverá funcionar em Windows com alguma limitações inerentes à formatação.
- ___Oscar Silva (<a14383|at|alunos.ipca.pt>)___
- ___Thiago Farias (<a16099|at|alunos.ipca.pt>)___
- ___Daniel Torres <a17442|at|alunos.ipca.pt>___

![Build](https://travis-ci.com/nargotik/aed2.svg?token=qNfqiYyxNzmWoPqpyHnZ&branch=master)

## Problema
Foi tentado fazer uma abordagem de forma a testar duas estruturas de dados abordadas nas aulas uma forma de conseguir tratar dados em grande escala.

O problema idealizado foi o de um sistema que efectua a recolha da temperatura e humidade a cada 15 segundos.

Dada a quantidade de dados verificamos que a geração de dados será a seguinte:

- 1 (um) registo por cada 0,25 segundos;
- 4 (quatro) registos por minuto;
- 240 (duzentos e quarenta) registos por hora;
- 5760 (cinco mil, setecentos e sessenta) registos por dia;
- 178560 (cento e setenta e oito mil, quinhentos e sessenta) registos por mês (assumindo que cada mês possui 31 dias);
- 2142720 (dois milhões, cento e quarenta e dois mil, setecentos e vinte) registos por ano

Desta forma decidimos testar então a inserção da informação em massa em listas ligadas, arrays e posteriormente a persistência dos dados em ficheiros dado o volume de dados a armazenar.

Foi então pensado utilizar um ficheiro de dados de forma a armazenar a informação mensal com o intuito de mais tarde possa ser carregada e analisada.

No decorrer deste relatório será então mostrado qual as vantagens e desvantagens de cada uma das estruturas.


## Compilação, Instalação e Execução
A compilação do programa deverá ser transparente utilizando o (GNU Make 4.1). Após a compilação da aplicação o binário de execução deverá estar na pasta __bin/aed2__
```console
foo@bar:~$ make
make[1]: Entering directory 'src/aed2'
gcc -o ../bin/aed2 *.c ../shared/*.c  -O3 -g3 -lm  -W -Wall -Wextra -Wuninitialized -Wstrict-aliasing -Wno-format-security -Wno-unused-but-set-variable -Wno-unused-result -std=c99 -Wno-unknown-pragmas
make[1]: Leaving directory 'src/aed2'
foo@bar:~$ ./bin/aed2
```

## Organização do Código
O código fonte e estrutura de ficheiros da aplicação está organizado da seguinte forma:

 - __./src/__
	 - __aed2/__
		 - Makefile (automake file)
		 - *.h (Ficheiros header da aplicação)
		 - *.c (Ficheiros de código fonte da aplicação)
	 - __shared/__
		 - *.c (Alguma funções de ajuda no UI)
		 - *.c (ficheiros header das funções partilhadas)
 - __./bin/__
	 - aed2 (ficheiro binário elf)
	 - aed2.exe (ficheiro executavel cygwin)
 - Makefile - Makefile (automake file)
 - readme.md (este relatório em formato markup)

## Menu Aplicação
Ao iniciar a aplicação veremos o menu que se segue:
```console
==========--- DADOS LISTA ---==========
TAMANHO LISTA         : XXXXX
TAMANHO ARRAY         : YYYYY
ARRAY (ORDENADO/DESORDENADO)

==========--- MENU PRINCIPAL ---==========
   0 - Sair
   1 - Lista => Inserir Item
   2 - Lista => Remover Item
   3 - Lista => Imprimir Lista
   4 - Lista => Gerar Dados automaticamente
   5 - Arrays => Converter Lista para Array
   6 - Arrays => Destruir Array
   7 - Arrays => Pesquisa Binária
   8 - Arrays => Pesquisa Sequencial
   9 - Arrays => Desordena Array
   10 - Arrays => Ordena Array (BubbleSort)
   11 - Files => Grava Lista
   12 - Files => Lê Lista
   13 - Files => Re-Inicializa Ficheiro
   14 - Files => Pesquisa Binária
   15 - Files => Pesquisa Sequencial
==========================================
OPCAO:

```
Segue abaixo um resumo da funcionalidade de cada opção do menu:
 1. Inserir um item na lista ligada.
 2. Remover um item da lista ordenada.
 3. Imprimir no ecrã a lista presentem em memória.
 4. Geração automática e aleatória de dados para runtime. 
 5. Converte a lista que está em memória para um array.
 6. Destrói o array que está em memória.
 7. Efectua pesquisa binária no array.
 8. Efectua pesquisa sequencial no array.
 9. Desordena aleatoriamente o array em memória.
 10. Ordena o array pelo  método BubbleSort.
 11. Grava a lista num ficheiro binário.
 12. Lê o ficheiro binário.
 13. Remove o ficheiro binário existente.
 14. Efectua pesquisa binária no ficheiro.
 15. Efectua pesquisa sequencial no ficheiro.

## Listas
### Criação

Foi criada uma função para inserir um dado numero de nodos numa lista ligada. 
```c
double cicloInserir(t_list* list, t_id i) {
    clock_t begin = clock();
    t_datanode reg;
    t_id tamanho_anterior = list->size;
    for(t_id f = 0; f < i; f++){
        reg.id = f + tamanho_anterior;
        reg.humidade = randomNumber(0,100);
        reg.temperatura = randomNumber(-10,60);
        reg.data = getDataTime();
        push(list, reg);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000 ;
    return time_spent;
    
}
```
Para a criação de dados de forma aleatória devemos utilizar a opção 4 do menu principal:
```console
OPCAO:4
==========--- MENU GERACAO DADOS ---==========
   0 -  Voltar <<<<
   1 -  Inserir     10.000 registos
   2 -  Inserir     50.000 registos
   3 -  Inserir    100.000 registos
   4 -  Inserir  1.000.000 registos
   5 -  Inserir 10.000.000 registos
   6 -  Inserir numero manual de registos
==============================================
OPCAO:5
[PERC 8%][Inserções 800000][55152 OPS/S][14 TOTAL SEC][166 ETA SEC]]
```
Teremos então acesso a um sub-menu que dá possibilidade de criar várias quantidades de dados aleatórios na lista.

Nos testes que fizemos verificamos que a velocidade de inserção numa lista ordenada rondava os 55,000 registos por segundo, demorando cerca de 3 minutos a fazer a inserção de 10,000,000 de registos.

A lista gerada ocuparia cerca de 400MB de memória.
```console
==========--- Tamanho da lista gerada ---==========
Bytes:          390625.00 B
MBytes:         381.47 MB
GBytes:         0.37 GB
Nodos Total:    10000000
===================================================
```
### Pesquisa
A pesquisa numa lista ligada equivale a percorrer a lista de até encontrar o valor necessário.

O tempo de realização da pesquisa sequencial na lista ordenada será o equivalente à criação da mesma.

Desta forma foi pensado a criação de um ficheiro binário com todos os nodos inseridos de forma sequencial de forma a que seja possível fazer a pesquisa binária em um ficheiro

__(afazer extender...)__

## Arrays
### Criação
A criação/cópia de dados da lista para o array é feita da forma mostrada no código abaixo, desta forma e utilizando o calloc para criar um array e o devolver por apontador é a forma mais eficiente de criar um array com uma grande quantidade de dados.
```c
        t_datanode *arrayDeNodos;
        t_id tamanho_array;
....
        // Cria o array a partir da lista
        arrayDeNodos = criaArray(list);
....


/**
 * Cria um array a partir de uma lista
 * @param list
 * @return 
 */
t_datanode * criaArray(t_list* list) {
    t_datanode *array_gerado;
    t_id tamanho = list->size, i = 0;
    array_gerado = (t_datanode*) calloc(tamanho, sizeof(t_datanode));
    t_node* pointer = list->head;

    while(pointer != NULL){
        t_datanode dataItem = pointer->data;
        array_gerado[i] = dataItem;
        pointer = pointer->next;
        i++;
    }
    tamanho_array = list->size;
    return array_gerado;   
}
```

A conversão da lista para um array recém criado é feita através da opção 5 do menu principal:
```console
OPCAO:5

Array convertido com sucesso... (1004.18 ms)
```
Nos testes que fizemos verificamos que a velocidade de inserção em um array rondava os 10,000,000 registos por segundo, demorando cerca de 1 segundo a fazer a inserção de 10,000,000 de registos.

O array criado ocuparia cerca de 400MB de memória.
___

### Pesquisa
#### Binária
A pesquisa binária têm por necessidade que o array esteja ordenado pelo que será feita com o array já ordenado tendo em conta que a inserção será já ordenada.
```c
t_id buscaBin(t_datanode arrayNode[], t_id arraySize, t_id buscarId) {
    t_id idEncontrado = -1;
    t_id min = 0, meio= 0, max = (arraySize - 1);
    while( (idEncontrado == -1 )  && (max >= min) ){
        meio = (min + max) / 2;
        if ( arrayNode[meio].id == buscarId)
            idEncontrado = meio;
        else
	        (arrayNode[meio].id > buscarId) ? min = meio + 1 : max = meio - 1;
    }
    return idEncontrado;
}
```
__(afazer extender...)__

#### Sequencial
A pesquisa sequencial não têm por necessidade que o array esteja ordenado pelo que será feita com o array já ordenado de forma a podermos comparar.
```c
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
```

__(afazer extender...)__

## Resumo
Breve resumo do que foi feito

Explicar as conclusões que tiramos das duas estruturas de dados
__(afazer extender...)__

## Conclusões
__(afazer extender...)__



## Bibliografia / Referências
__(afazer extender...)__
