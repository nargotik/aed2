/* 
 * File:   arrays.h
 * 
 * Created on 26 de Maio de 2019, 23:29
 */

#ifndef ARRAYS_H
#define ARRAYS_H
#include "headers.h"

void bubbleSort(t_datanode arr[], int n);
void swap(t_datanode *a,t_datanode *b);
t_datanode * criaArray(t_list* list);
double arrayPesquisaBinaria(t_datanode array[], t_id tamanho);
double arrayConverte(t_list* list);
double arrayDesordena(t_datanode *array, t_id tamanho);
double arrayOrdenabubbleSort(t_datanode arr[], t_id n);
void converteArray(t_list* list);

#endif /* ARRAYS_H */

