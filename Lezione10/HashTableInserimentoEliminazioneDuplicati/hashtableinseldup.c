/*Scrivere un programma che legga da tastiera una sequenza di n interi NON
distinti e li inserisca senza duplicati in una tabella hash di dimensione 2n
posizioni utilizzando liste monodirezionali per risolvere eventuali conflitti.
Utilizzare la funzione hash h(x) = ((ax + b) % p) % 2n dove p `e
il numero primo 999149 e a e b sono interi positivi minori di 10.000 scelti
casualmente.
Una volta inseriti tutti gli interi, il programma deve stampare il numero
totale di conflitti, la lunghezza massima delle liste e il numero di elementi
distinti.
L’input `e cos`ı formato:
• la prima riga contiene la lunghezza n della sequenza;
• la seconda riga contiene a;
• la terza riga contiene b;
• le successive n righe contengono gli interi che compongono la sequenza.
L’output `e cos`ı formato:
• la prima riga contiene il numero totale di conflitti;
• la seconda riga contiene la dimensione della lista di lunghezza massima;
• la terza riga contiene il numero totale di elementi distinti.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct _node{
	int key;
	struct _node* next;
}node;

typedef struct{
	node *head;
	node *tail;
	size_t size;
}list;

typedef struct{
	size_t a, b, p;
	size_t size;
	list *bucket;
	size_t max_buckets_size;
	size_t num_conflicts;
	size_t num_distinct_elements;
}hashtable;

size_t hash(const hashtable* table, int key){
	return ((table->a * key + table->b) % table->p) % table->size;
}

size_t search(list l, int key){
	while(l.head != NULL){
		if(l.head->key == key)
			return 1;
		l.head = l.head->next;
	}
	return 0;
}

size_t list_append(list *l, int key){
	node* new = malloc(sizeof(node));
	new->key = key;
	new->next = NULL;

	if(l->size == 0){
		l->head = new;
		l->tail = new;
		l->size++;
	} else {
		if(!search(*l, key)){
			l->tail->next = new;
			l->tail = new;
			l->size++;
		}
		else return 0;
	}
	return 1;
}

void hashtableinit(hashtable *table, size_t a, size_t b, size_t size){
	int i;
	table->a = a;
	table->b = b;
	table->p = 999149;
	table->size = size;

	table->bucket = malloc(size * sizeof(list));

	for(i = 0; i < size; i++){
		table->bucket[i].head = NULL;
		table->bucket[i].tail = NULL;
		table->bucket[i].size = 0;
	}

	table->max_buckets_size = 0;
	table->num_conflicts = 0;
	table->num_distinct_elements = 0;
}

void hashtableinsert(hashtable *table, int key){
	size_t h = hash(table, key);

	table->num_distinct_elements += list_append(&table->bucket[h], key);

	table->max_buckets_size = MAX(table->bucket[h].size, table->max_buckets_size);

	if(table->bucket[h].size != 1)
		table->num_conflicts++;
}

void freelist(node *n){
	if(n != NULL){
		freelist(n->next);
		free(n);
	}
}

int main(){
	hashtable table;
	size_t a, b, n, i;
	int key;

	scanf("%lu", &n);
	scanf("%lu", &a);
	scanf("%lu", &b);

	hashtableinit(&table, a, b, 2 * n);

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		hashtableinsert(&table, key);
	}

	printf("%lu\n", table.num_conflicts);
	printf("%lu\n", table.max_buckets_size);
	printf("%lu\n", table.num_distinct_elements);

	for(i = 0; i < 2*n; i++){
		freelist(table.bucket[i].head);
	}
	free(table.bucket);

	return 0;
}
