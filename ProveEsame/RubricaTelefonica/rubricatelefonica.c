/*Si vuole implementare una rubrica telefonica, in cui un record della rubrica
`e costituito da un nome (una stringa senza spazi, univoca) a cui `e associato
un numero di telefono. Sia N il numero di record da inserire nella rubrica.
Essi devono essere memorizzati in una tabella hash di dimensione 2N.
La funzione hash riceve in input una stringa non vuota (il nome) e
restituisce in output un valore numerico:
• si esegue la somma di tutti i codici decimali associati ai caratteri della
stringa (escluso il carattere speciale di fine stringa ’\0’); ogni carattere
deve essere trattato come unsigned int;
• l’output `e pari alla somma precedentemente calcolata modulo 2N.
Ad esempio, per la stringa Ciao! (N = 5) si hanno i codici indicati nella
seguente tabella:
Carattere Codice decimale
C 67
i 105
a 97
o 111
! 33
Si ottiene: 67 + 105 + 97 + 111 + 33 = 413, 2N = 10 e dunque
hash(Ciao!) = 413 % 10 = 3.
Quando si inserisce un record in una lista di trabocco, se vi sono conflitti il record
va inserito in ordine lessicografico non decrescente, scandendo
opportunamente la lista fino ad individuare la posizione in cui inserirlo.
Dato un intero K tale che 0 ≤ K < 2N, il programma deve stampare
il contenuto della lista di trabocco di posizione K. Data la maniera in
cui vengono inseriti i record nelle liste, l’output sar`a costituito da record
stampati in base all’ordine lessicografico del nome.
NOTA IMPORTANTE: Non `e consentito l’utilizzo di alcun algoritmo di
ordinamento al fine di riordinare i record della K-esima lista. La procedura
di inserimento di un record `e sufficiente a garantire l’ordinamento.
L’input `e cos`ı formato:
• la prima riga contiene il numero N di record da inserire;
• le successive 2N righe contengono la descrizione degli N record; la
descrizione di un record occupa 2 righe consecutive:
– la prima contiene il nome (una stringa non vuota, univoca, di
lunghezza non superiore a 100 caratteri);
– la seconda contiene il numero di telefono (una stringa non vuota
di lunghezza non superiore a 20 caratteri);
• l’ultima riga contiene il valore K.
L’output `e costituito dalla sequenza dei record presenti nella K-esima lista
di trabocco, stampati in ordine lessicografico del nome, uno per riga. Ogni
record `e stampato nel formato:
<nome> <spazio> <numero di telefono>
(ad esempio AlanTuring 123-456789).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct _node{
	string name;
	string telephone;
	struct _node *next;
}node;

typedef struct _hashtable{
	int size;
	node **buckets;
}hashtable;

int hash(hashtable *table, string name){
	unsigned int sum = 0;
	int i = 0;

	//Sum all the letters in the string casted integer
	while(name[i])
		sum += (unsigned int) name[i++];

	return sum % table->size; //Return the hash value
}

void hashtable_init(hashtable *table, int size){
	table->size = size; //Initializate the table size

	table->buckets = malloc(sizeof(node) * size); //Allocate memory for the table

	//Initializate all the lists
	for(int i = 0; i < size; i++)
		table->buckets[i] = NULL;
}

void hashtable_insert(hashtable *table, string name, string telephone){
	int h = hash(table, name); //Calculate the hash value of the name
	node *new = malloc(sizeof(node)); //Allocate a new node

	//Initializate the ndoe
	new->name = name;
	new->telephone = telephone;
	new->next = NULL;

	if(table->buckets[h] == NULL) //Check if the list is empty
		table->buckets[h] = new;
	else {
		node *tmp = table->buckets[h]; //Initializate a temporary pointer to the head of the list
		node *prev = NULL; //Inizializate the previous pointer to tmp
		int found = 0; //Flag

		while(tmp != NULL && !found){ //Until the list isn't finished or the element is found
			if(strcmp(tmp->name, name) < 0){ //If the spot isn't correct
				prev = tmp; //Save the point before increase tmp
				tmp = tmp->next; //Increase tmp to the next node
			} else {
				//The element is in the right spot
				found = 1; //Change the flag
				new->next = tmp;
				if(prev != NULL)
					prev->next = new; //The node is added in a generic position
				else
					table->buckets[h] = new; //The node is added in the head
			}
		}

		if(!found)
			prev->next = new; //The element is added in the tail
	}
}

void hashtable_print(hashtable *table, int k){
	if(table->buckets[k] != NULL){ //Checks if the list isn't empty
		node *tmp = table->buckets[k]; //Initializate a temporary pointer to the head of the list

		while(tmp != NULL){ //Until the list has no more elements
			printf("%s %s\n", tmp->name, tmp->telephone); //Print information
			tmp = tmp->next; //Increase the pointer to the next node
		}
	}
}

void free_list(node *head){
	if(head != NULL){
		free_list(head->next); //Recursive call to free all the nodes
		free(head->name); //Deallocate memory for the string
		free(head->telephone); //Deallocate memory for the string
		free(head); //Deallocate the node
	}
}

void free_table(hashtable *table){
	int i;

	//Deallocate all the lists
	for(i = 0; i < table->size; i++){
		free_list(table->buckets[i]);
	}

	free(table->buckets); //Deallocate the memory for the table
}

int main(){
	int n, i, k;
	hashtable table;

	//Read the table dimension
	scanf("%d", &n);

	//Initializate the table
	hashtable_init(&table, 2 * n);

	//Read and insert all the information
	for(i = 0; i < n; i++){
		string name = malloc(sizeof(char) * 101); //Allocate memory for the string
		string telephone = malloc(sizeof(char) * 101); //Allocate memory for the string

		scanf("%s", name); //Read the string
		scanf("%s", telephone); //Read the string

		hashtable_insert(&table, name, telephone); //Insert the elements in the table
	}

	//Read the query
	scanf("%d", &k);

	//Print the information in position k
	hashtable_print(&table, k);

	//Deallocate the table
	free_table(&table);
	return 0;
}
