/* 
 * File:   arrays.h
 * 
 * Created on 26 de Maio de 2019, 23:29
 */

#ifndef FILES_H
#define FILES_H
#include "headers.h"
#include "listas.h"

extern t_datanode *arrayDeNodos;
extern t_id tamanho_array;
extern int array_ordenado;

t_id writeLeitura(t_datanode* reading);
t_id readLeituras(t_list* list);
t_id totalLeituras();
t_id writeLeituras(t_list* list);
t_id fsize(FILE *fp);
void removeFicheiro();
t_datanode readLeitura(t_id posicao);
t_datanode filebuscaBin(t_id buscarId);
t_datanode filebuscaSeq(t_id buscarId);
#endif /* ARRAYS_H */

