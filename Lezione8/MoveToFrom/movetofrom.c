/*Scrivere un programma che legga da tastiera una sequenza di n interi distinti e li inserisca
 in una lista monodirezionale (nell’ordine dato). Il programma
entra poi in un ciclo nel quale legge un intero i da tastiera e lo cerca nella
lista. Se i si trova nella lista stampa la sua posizione (contando da 0) e porta
l’elemento in testa alla lista (MTF), altrimenti stampa -1 e termina.
L’input `e formattato come segue:
• la prima riga contiene la lunghezza n (non limitata) della sequenza;
• le successive n righe contengono gli interi che compongono la sequenza,
uno per riga;
• segue una sequenza di interi da cercare nella lista (uno per riga), di
lunghezza non nota a priori, terminata da un numero non presente
nella lista.
L’output contiene:
• le posizioni degli elementi trovati nella lista (si assume che il primo
elemento sia in posizione 0), una posizione per riga;
• -1 se `e stato dato in input un numero che non `e nella lista, e in tal
caso si termina.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct el{
	int key;
	struct el *next;
}elemento;

typedef struct{
	elemento *head;
	elemento *tail;
}index;

index inserisciCoda(index ind, int key);
int movetofrom(index *ind, int key);
void freelist(elemento *head);

int main(){
	int n, i, key, ris;
	index ind = {NULL, NULL};

	scanf("%d", &n);

	//Leggo le n chiavi
	for(i=0; i<n; i++){
		scanf("%d", &key);
		ind = inserisciCoda(ind, key);
	}

	//Leggo e cerco le chiavi
	do{
		scanf("%d", &i);
		ris = movetofrom(&ind, i);
		printf("%d\n", ris);
	}while(ris >= 0);

	freelist(ind.head); //Dealloco la memoria
	return 0;
}

index inserisciCoda(index ind, int key){
	elemento *tmp = malloc(sizeof(elemento));
	tmp->key = key;
	tmp->next = NULL;

	if(ind.head == NULL) ind.head = tmp;
	else (ind.tail)->next = tmp;

	ind.tail = tmp;
	return ind;
}

int movetofrom(index *ind, int key){
	int i = 0;
	elemento *tmp = ind->head;
	elemento *app = NULL;

	while(tmp != NULL){
		if(tmp->key == key){
			if(app == NULL) return 0; //Elemento in prima posizione

			//Sposto l'elemento trovato in prima posizone
			app->next = tmp->next;
			tmp->next = ind->head;
			ind->head = tmp;

			return i;
		}

		app = tmp;
		tmp = tmp->next;
		i++;
	}

	return -1;
}

void freelist(elemento *head){
	if(head != NULL){
		freelist(head->next);
		free(head);
	}
}
