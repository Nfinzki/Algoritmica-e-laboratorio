/*Scrivere un programma che legga da tastiera una sequenza di n interi e li
inserisca in una lista nell’ordine di immissione. La lista deve essere monodirezionale.
Il programma deve stampare il contenuto della lista percorrendola in ordine
inverso.
La prima riga dell’input contiene la lunghezza n (non limitata) della lista.
Le righe successive contengono gli interi che compongono la lista, uno per
riga.
L’output contiene la lista stampata al contrario, un elemento per riga*/

#include <stdio.h>
#include <stdlib.h>

typedef struct el{
	int key;
	struct el *next;
}elemento;

typedef struct _indici{
	elemento *head;
	elemento *tail;
}indici;

indici inserisciCoda(indici ind, int key);
void stampaInv(elemento *head);
void freelist(elemento *head);

int main(){
	int n, i, key;
	indici ind = {NULL, NULL};
	scanf("%d", &n);

	//Leggo n interi
	for(i=0; i<n; i++){
		scanf("%d", &key);
		ind = inserisciCoda(ind, key);
	}

	stampaInv(ind.head); //Stampo al contrario
	freelist(ind.head); //Dealloco la memoria
	return 0;
}

indici inserisciCoda(indici ind, int key){
	elemento *tmp = (elemento *) malloc(sizeof(elemento));
	tmp->key = key;
	tmp->next = NULL;

	if(ind.head == NULL)
		ind.head = tmp;
	else
		(ind.tail)->next = tmp;
	ind.tail = tmp;

	return ind;
}

void stampaInv(elemento *head){
	if(head != NULL){
		stampaInv(head->next);
		printf("%d\n", head->key);
	}
}

void freelist(elemento *head){
	if(head != NULL){
		freelist(head->next);
		free(head);
	}
}
