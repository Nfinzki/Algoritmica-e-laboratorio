/*
Alice e Bob seguono fedelmente la filosofia “non hai bisogno di pi`u di quindici
oggetti diversi per vivere”, che pone due vincoli al possesso dei beni:
• si devono possedere al pi`u quindici oggetti;
• si pu`o possedere al pi`u un oggetto per ogni tipologia.
Ad esempio, un individuo non pu`o possedere pi`u di un televisore, ma pu`o
possedere un televisore, un frigorifero, un telefono, etc. fino ad un massimo
di quindici oggetti.
Dopo qualche anno, Alice e Bob decidono finalmente di sposarsi. La filosofia prevede per`o che una coppia
sposata debba essere vista come un unico
soggetto. Dunque Alice e Bob, che complessivamente potevano possedere
fino a quindici oggetti a testa (trenta in totale) prima di sposarsi, devono
rinunciare ad alcuni oggetti al fine di possedere al pi`u quindici oggetti distinti in totale.
Al fine di decidere quali oggetti tenere, Alice e Bob decidono
di associare ad ogni oggetto un “valore affettivo” e di scegliere dunque i
quindici oggetti (al pi`u) che massimizzino la somma del valore affettivo. Il
vostro compito `e quello di aiutare Alice e Bob nella scelta, implementando
la strategia seguente.
Vi verr`a data in input la lista di oggetti posseduti da Alice e da Bob.
Ogni oggetto avr`a un nome (una stringa), che ne contraddistingue la tipologia, ed un valore affettivo
(un intero). Gli oggetti dovranno essere inseriti
in una tabella hash a liste di trabocco, al fine di scoprire i duplicati e di
selezionare, a parit`a di tipologia, l’oggetto col valore affettivo maggiore. In
particolare, la tabella dovr`a avere 2 N ingressi, dove N `e la somma degli
oggetti posseduti complessivamente da Alice e Bob. La funzione hash riceve
in input una stringa non vuota (il nome dell’oggetto) e restituisce in output
un valore numerico:
• si esegue la somma di tutti i codici decimali associati ai caratteri della
stringa (escluso il carattere speciale di fine stringa ’\0’); ogni carattere
deve essere trattato come unsigned int;
• l’output `e pari alla somma precedentemente calcolata modulo 2 N.
Ad esempio, per la stringa "Ciao!" (N = 5) si hanno i codici indicati nella
seguente tabella:
Carattere Codice decimale
C 67
i 105
a 97
o 111
! 33

Si ottiene: 67 + 105 + 97 + 111 + 33 = 413, 2N = 10 e dunque
hash("Ciao!") = 413 % 10 = 3.
Per ogni oggetto in input, bisogner`a aggiornare la tabella hash come
segue. Supponiamo che X sia l’oggetto con cui dovr`a essere aggiornata la
tabella hash, ed indichiamo con nome(X) il suo nome e con valore(X) il
suo valore affettivo. Ogni oggetto in input dovr`a essere cercato nella tabella
hash. Vi sono tre casi:
1. la tabella non contiene un oggetto Y per cui nome(X) = nome(Y ).
In questo caso, bisogner`a inserire l’oggetto X in cima alla lista di
trabocco;
2. la tabella contiene un oggetto Y per cui nome(X) = nome(Y ), e per
cui valore(X) ≤ valore(Y ). In questo caso non bisogna far nulla;
3. la tabella contiene un oggetto Y per cui nome(X) = nome(Y ), e
per cui valore(X) > valore(Y ). In tal caso, bisogner`a aggiornare Y
impostando valore(Y ) = valore(X).
Nota come la regola d’aggiornamento garantisca che, ad ogni passo, vi sia
nella tabella al pi`u un oggetto per tipologia e che, per ogni tipologia, sia stato
selezionato l’elemento col pi`u alto valore affettivo. Una volta riempita la
tabella hash, bisogner`a ordinarne gli oggetti per valore affettivo decrescente
e, a parit`a di valore affettivo, per ordine lessicografico crescente. Infine,
stampare il nome dei primi quindici oggetti ordinati.
Nota: il numero finale degli oggetti potr`a essere inferiore a quindici:
in tal caso stampare tutti gli oggetti nella tabella hash, sempre in base
all’ordinamento richiesto.
L’input `e cos`ı formato:
• La prima linea contiene il numero N di oggetti da processare;
• Le successive 2N linee contengono la descrizione degli N oggetti; la
descrizione di ogni oggetto occupa 2 linee consecutive:
– la prima contiene il nome (una stringa, non vuota, di lunghezza
non superiore a 100 caratteri);
– la seconda contiene il valore affettivo (un intero).
L’output `e composto dai nomi degli oggetti selezionati con la strategia esposta precedentemente, uno per linea,
ordinati per valore affettivo
decrescente e, a parit`a di valore affettivo, per ordine lessicografico crescente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct _node{
	string key;
	int sentimental_val;
	struct _node *next;
}node;

typedef struct _hashtable{
	int N; //Dimension
	node **buckets; //Array of list
	int elem;
}hashtable;

int hash(string s, int N){ //Converts char in integer and sum them all
	unsigned int somma = 0;
	int i = 0;
	while(s[i])
		somma += (unsigned int) s[i++];

	return somma % N;
}

void hashtable_init(hashtable *table, int size){
	int i;
	table->N = size;
	table->elem = 0;
	table->buckets = malloc(size * sizeof(node)); //Allocate an array

	//Initialize array
	for(i = 0; i < size; i++)
		table->buckets[i] = NULL;
}

node *search(node *head, string key){
	if(head == NULL)
		return NULL;
	if(strcmp(head->key, key) == 0)
		return head;
	else
		return search(head->next, key);
}

void hashtable_insert(hashtable *table, string key, int sentimental_val){
	int h = hash(key, table->N); //Calculate the hash value
	node *app = search(table->buckets[h], key);
	if(app == NULL){ //The list is empty, insert the element
		node *new = malloc(sizeof(node));
		new->key = key;
		new->sentimental_val = sentimental_val;
		new->next = table->buckets[h];
		table->buckets[h] = new;
		table->elem++;
	} else { //The list isn't empty
		if(sentimental_val > app->sentimental_val)
			app->sentimental_val = sentimental_val; //Update the sentimental value
	}
}

node **copy(const hashtable *table){
	node **a = malloc(sizeof(node *) * table->elem);
	int i;
	int j = 0;
	for(i = 0; i < table->N; i++){
		node *app = table->buckets[i];
		while(app != NULL){
			a[j] = app;
			j++;
			app = app->next;
		}
	}

	return a;
}

int compare(const void *a, const void *b){
	node *a1 = *(node **) a;
	node *b1 = *(node **) b;

	if(a1->sentimental_val == b1->sentimental_val)
		return strcmp(a1->key, b1->key);
	else return (b1->sentimental_val - a1->sentimental_val);
}

void print_items(node **sorted, int size){
	node **a = sorted;
	int i = 0; //Elements printed

	while(i < size){
		printf("%s\n", a[i]->key);
		i++;
	}
}

void free_list(node *head){
	if(head != NULL){
		free_list(head->next);
		free(head->key);
		free(head);
	}
}

void free_table(hashtable *table){
	int i=0;
	while(i < table->N){
		free_list(table->buckets[i]);
		i++;
	}
	free(table->buckets);
}

int main(){
	hashtable table;
	int n, i, val;
	node **a;


	scanf("%d", &n);

	//Initialize the hash table
	hashtable_init(&table, 2*n);

	//Read n elements and insert in the table
	for(i = 0; i < n; i++){
		string s = malloc(sizeof(char) * 101);
		scanf("%s", s);
		scanf("%d", &val);
		hashtable_insert(&table, s, val);
	}

	a = copy(&table);

	//Sort the elements by sentimental_val
	qsort(a, table.elem, sizeof(node*), compare);

	int size = table.elem < 15 ? table.elem : 15;
	//Print only the first 15 elements
	print_items(a, size);

	//Deallocate memory
	free_table(&table);
	free(a);
	return 0;
}
