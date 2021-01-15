/*Scrivere un programma che legga da tastiera una sequenza di n interi maggiori di 0 e li inserisca
in una lista nell’ordine di immissione. La lista deve
essere monodirezionale.
Successivamente il programma deve sostituire il valore di ciascun elemento con la somma dei valori degli
elementi che lo seguono nella lista.
Suggerimento: si utilizzi la ricorsione per ottenere la somma ad ogni
passo.
L’input `e costituito da:
• una riga contenente la lunghezza n della sequenza;
• n righe contenenti gli interi che compongono la sequenza.
L’output `e costituito da:
• una riga contenente tutti gli interi letti da input (separati da uno
spazio);
• una riga contenente tutti gli interi nella lista dopo aver calcolato le
somme suffisse (separati da uno spazio).*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node* next;
}node;

typedef struct{
	node* head;
	node* tail;
}list;

void list_append(list *l, int key){
	node* new = malloc(sizeof(node));
	new->key = key;
	new->next = NULL;

	if(l->head == NULL)
		l->head = new;
	else
		l->tail->next = new;
	l->tail = new;
}

void print_list(node *n){
	if(n != NULL){
		printf("%d ", n->key); //Probabilmente gli darà fastidio questo
		print_list(n->next);
	}
	else
		printf("\n");
}

int sums_suffixed(node *n){
	int sum;
	if(n != NULL){
		sum = sums_suffixed(n->next);
		sum += n->key;
		n->key = sum - n->key;
		return sum;
	}
	else
		return 0;
}

void free_list(node *n){
	if(n != NULL){
		free_list(n->next);
		free(n);
	}
}

int main(){
	int n, k, i;
	list l = {NULL, NULL};

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &k);
		list_append(&l, k);
	}

	print_list(l.head);
	sums_suffixed(l.head);
	print_list(l.head);

	free_list(l.head);

	return 0;
}
