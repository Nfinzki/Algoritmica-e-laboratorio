/*
Scrivere un programma che legga da tastiera una sequenza di n interi distinti e li inserisca in una tabella
hash di dimensione 2n posizioni utilizzando
liste monodirezionali per risolvere eventuali conflitti.
Utilizzare la funzione hash h(x) = ((ax + b) % p) % 2n dove p `e
il numero primo 999149 e a e b sono interi positivi minori di 10.000 scelti
casualmente.
Una volta inseriti tutti gli interi, il programma deve stampare la lunghezza massima delle liste e il numero
totale di conflitti.
Prima di scrivere il programma chiedersi perch´e la tabella ha dimensione
2n e non n.
L’input `e cos`ı formato:
• la prima riga contiene la lunghezza n della sequenza;
• la seconda riga contiene a;
• la terza riga contiene b;
• le successive n righe contengono gli interi che compongono la sequenza.
L’output `e cos`ı formato:
• la prima riga contiene la dimensione della lista di lunghezza massima;
• la seconda riga contiene il numero totale di conflitti.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct _node{
	int key;
	struct _node* next;
}node;

typedef struct{
	node* head;
	node* tail;
	size_t size;
}list;

typedef struct{
	size_t a, b, p;
	size_t size;
	list* buckets;
	size_t max_bucket_size;
	size_t num_conflicts;
}hashtable;

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
}

size_t hash(const hashtable* table, int key){
	return ((table->a * key + table->b) % table->p) % table->size;
}

void hashtableinit(hashtable* table, size_t size, size_t a, size_t b){
	int i;
	table->a = a;
	table->b = b;
	table->p = 999149;
	table->size = size;
	table->max_bucket_size = 0;
	table->num_conflicts = 0;

	table->buckets = malloc(size * sizeof(list));

	for(i = 0; i < size; i++){
		table->buckets[i].head = NULL;
		table->buckets[i].tail = NULL;
		table->buckets[i].size = 0;
	}
}

void hashtableinsert(hashtable* table, int key){
	size_t h = hash(table, key);

	list_append(&table->buckets[h], key);

	table->max_bucket_size = MAX(table->max_bucket_size, table->buckets[h].size);

	if(table->buckets[h].size != 1)
		table->num_conflicts++;
}

int main(){
	hashtable table;
	size_t a, b, n;
	int k, i;

	scanf("%lu", &n);
	scanf("%lu", &a);
	scanf("%lu", &b);

	hashtableinit(&table, 2 * n, a, b);

	for(i = 0; i < n; i++){
		scanf("%d", &k);
		hashtableinsert(&table, k);
	}

	printf("%lu\n", table.max_bucket_size);
	printf("%lu\n", table.num_conflicts);

	return 0;
}
