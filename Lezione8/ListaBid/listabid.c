/*Scrivere un programma che legga da tastiera una sequenza di n interi e li
inserisca in una lista nell’ordine di immissione. La lista deve essere bidirezionale.
Il programma deve stampare il contenuto della lista percorrendola in ordine
inverso.
La prima riga dell’input contiene la lunghezza n (non limitata) della lista.
Le righe successive contengono gli interi che compongono la lista, uno per
riga.
L’output contiene la lista stampata al contrario, un elemento per riga.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct el{
	int key;
	struct el *prev;
	struct el *next;
}elemento;

typedef struct{
	elemento *head;
	elemento *tail;
}indici;

indici inserisciCoda(indici head, int key);
void stampa(elemento *tail);
void freelist(elemento *head);

int main(){
	int n, i, key;
	indici ind = {NULL, NULL};
	scanf("%d", &n);

	//Leggo gli n elementi
	for(i=0; i<n; i++){
		scanf("%d", &key);
		ind = inserisciCoda(ind, key);
	}

	//Stampo gli n elementi al contrario
	stampa(ind.tail);

	//Dealloco la memoria
	freelist(ind.head);

	return 0;
}

indici inserisciCoda(indici ind, int key){
	elemento *tmp = malloc(sizeof(elemento));
	tmp->key = key;
	tmp->next = NULL;
	tmp->prev = ind.tail;

	if(ind.head == NULL) ind.head = tmp;
	else (ind.tail)->next = tmp;

	ind.tail = tmp;
	return ind;
}

void stampa(elemento *tail){
	if(tail != NULL){
		printf("%d\n", tail->key);
		stampa(tail->prev);
	}
}

void freelist(elemento *head){
	if(head != NULL){
		freelist(head->next);
		free(head);
	}
}
