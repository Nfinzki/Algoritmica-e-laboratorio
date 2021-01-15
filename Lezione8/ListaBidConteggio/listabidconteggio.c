/*Scrivere un programma che legga da tastiera una sequenza di n interi ordinati e li inserisca in una
lista bidirezionale. Il programma entra poi in un
ciclo nel quale legge un intero i da tastiera e lo cerca nella lista. Se i si trova
nella lista, stampa la sua posizione (contando da 0), altrimenti stampa -1.
Ogni elemento della lista mantiene anche un contatore che ricorda quante volte `e stata
cercata la corrispondente chiave. Tutti i contatori sono
inizialmente settati a 0. Dopo ogni ricerca si deve garantire che gli elementi
della lista siano ordinati in ordine non-crescente di contatore. Se il contatore di un elemento
viene incrementato e risulta uguale a quello dell’elemento
precedente, i due elementi vanno lasciati nelle loro posizioni.
NOTA: non si devono utilizzare algoritmi di ordinamento, ma osservare
che inizialmente la lista `e ordinata e che dopo ogni ricerca solo un contatore
viene incrementato.
L’input `e formattato come segue:
• la prima riga contiene la lunghezza n (non limitata) della lista;
• le successive n righe contengono gli interi che compongono la lista, in
ordine, uno per riga;
• segue una lista di interi da cercare nella lista (uno per riga), di lunghezza non nota a priori,
terminata da un numero non presente nella
lista.
L’output contiene:
• le posizioni degli elementi trovati nella lista (si assume che il primo
elemento sia in posizione 0), una posizione per riga; gli elementi devono
essere mantenuti ordinati in ordine non-crescente di contatore;
• -1 se `e stato dato in input un numero che non `e nella lista, e in tal
caso si termina.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct el{
	int key;
	int freq;
	struct el *next;
	struct el *prev;
} elemento;

typedef struct{
	elemento *head;
	elemento *tail;
}index;

index inserisciCoda(index ind, int key);
int conteggio(index *ind, int key);
void sposta(index *ind, elemento *el);
void freelist(elemento *head);

int main(){
	int n, i, key, ris;
	index ind = {NULL, NULL};

	scanf("%d", &n);

	//Lettura e inserzione nella lista degli n elementi
	for(i=0; i<n; i++){
		scanf("%d", &key);
		ind = inserisciCoda(ind, key);
	}

	//Ricerca degli elementi
	do{
		scanf("%d", &key);
		ris = conteggio(&ind, key); //Posizione in cui si trova l'elemento
		printf("%d\n", ris);
	}while(ris >= 0);

	freelist(ind.head); //Deallocazione memoria
	return 0;
}

index inserisciCoda(index ind, int key){
	elemento *tmp = malloc(sizeof(elemento));
	tmp->key = key;
	tmp->freq = 0;
	tmp->next = NULL;

	if(ind.head == NULL){
		ind.head = tmp;
		tmp->prev = NULL;
	}
	else{
		tmp->prev = ind.tail;
		(ind.tail)->next = tmp;
	}

	ind.tail = tmp;
	return ind;
}

int conteggio(index *ind, int key){
	int i=0;
	elemento *tmp = ind->head;

	while(tmp != NULL){
		if(tmp->key == key){
			(tmp->freq)++;

			if((tmp->prev) == NULL) return 0; //Elemento in prima posizione

			if((tmp->prev)->freq < tmp->freq){ //Elemento non nella giusta posizione
				(tmp->prev)->next = tmp->next;
				if(tmp->next != NULL) (tmp->next)->prev = tmp->prev;
				else ind->tail = tmp->prev;
				sposta(ind, tmp);
			}
			return i;
		}

		tmp = tmp->next;
		i++;
	}

	return -1;
}

void sposta(index *ind, elemento *el){
	int found = 0;
	elemento *tmp = el->prev;
	while(tmp != NULL && !found){

		if(tmp->freq >= el->freq){
			found = 1;
			continue;
		}

		tmp = tmp->prev;
	}

	if(found){ //Elemento trovato, inserzione nella giusta posizione
		el->next = tmp->next;
		(tmp->next)->prev = el;
		tmp->next = el;
		el->prev = tmp;
	}
	else{//L'elemento va inserito in testa alla lista
		el->prev = NULL;
		el->next = ind->head;
		(ind->head)->prev = el;
		ind->head = el;
	}
}

void freelist(elemento *head){
	if(head != NULL){
		freelist(head->next);
		free(head);
	}
}
