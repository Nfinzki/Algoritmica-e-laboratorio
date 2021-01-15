/*Scrivere un programma che legga da tastiera una sequenza di n interi distinti
e li inserisca in una lista monodirezionale. Successivamente il programma
deve calcolare la media aritmetica dei valori della lista ed eliminare tutti
gli elementi il cui valore `e inferiore o uguale alla media, troncata all’intero
inferiore. Ad esempio:
avg(1, 2, 4) = 7/3 = 2
IMPORTANTE: Si abbia cura di liberare la memoria dopo ogni cancellazione.
L’input `e costituito da:
• una riga contenente la lunghezza n della sequenza;
• n righe contenenti gli interi che compongono la sequenza.
L’output `e costituito da:
• una riga contenente la media troncata all’intero inferiore;
• una riga contenente tutti gli interi letti da input (separati da uno
spazio);
• una riga contenente tutti gli interi nella lista dopo aver filtrato (separati da uno spazio).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node* next;
}node;

typedef struct{
	node* head;
	node* tail;
	int size;
	int sum_elements;
}list;

void list_append(list *l, int key){
	node* new = malloc(sizeof(node));
	new->key = key;
	new->next = NULL;

	if(l->size == 0)
		l->head = new;
	else
		l->tail->next = new;
	l->tail = new;
	l->size++;
	l->sum_elements += key;
}

void list_init(list *l){
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	l->sum_elements = 0;
}

void delete_elem(list *l, int avg){
	node *tmp = l->head;
	node *prev = NULL;

	while(tmp != NULL){
		if(tmp->key <= avg){
			if(prev == NULL)
				l->head = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp);

			if(prev == NULL)
				tmp = l->head;
			else
				tmp = prev->next;
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void print_list(node *n){
	while(n != NULL){
		printf("%d ", n->key);
		n = n->next;
	}
	printf("\n");
}

void free_list(node *n){
	if(n != NULL){
		free_list(n->next);
		free(n);
	}
}

int main(){
	list l;
	int n, i, key, avg;

	list_init(&l);

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		list_append(&l, key);
	}

	avg = l.sum_elements / l.size;
	printf("%d\n", avg);
	print_list(l.head);
	delete_elem(&l, avg);
	print_list(l.head);

	free_list(l.head);

	return 0;
}
