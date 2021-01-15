/*Dato un insieme di interi S, un intero i ∈ S ha rango k se esistono esattamente k interi pi`u piccoli di
i in S. Ad esempio, nell’insieme I = {1, 5, 9, 13, 19},
l’elemento 9 ha rango 2 (1 e 5 sono pi`u piccoli di 9 in I), mentre l’elemento
1 ha rango 0 (nessun elemento `e pi`u piccolo di 1 in I). La mediana di un
insieme S con n elementi `e dunque definita come l’elemento di S con rango
bn/2c. Intuitivamente, la mediana `e l’elemento “centrale” della lista ottenuta ordinando gli elementi
nell’insieme: nell’esempio precedente, la mediana
dell’insieme I `e l’elemento 9 in quanto ha rango b5/2c = 2.
L’esercizio richiede di implementare una funzione mediana che, dato un
albero di ricerca binario, restituisca la mediana dell’insieme degli elementi
ivi contenuti.
In particolare, il programma deve leggere una sequenza di n ≥ 1 interi
distinti ed inserirli in un albero binario di ricerca non bilanciato.
Al termine dell’inserimento, il programma deve invocare la funzione mediana
sull’albero costruito al punto precedente e stampare in output il risultato
ottenuto.
Nota: Al fine del superamento della prova, la procedura mediana dovr`a
richiedere tempo O(n), lineare rispetto al numero di elementi contenuti
nell’albero.
L’input `e formattato nel seguente modo. La prima riga contiene il numero
n di interi da inserire nell’albero. Seguono poi n righe, una per ogni intero
nella sequenza.
L’output `e costituito da una singola riga contenente l’intero identificato
dalla funzione mediana.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	int rank;
	struct _node* left;
	struct _node* right;
}node;

node *insert(node *root, int key){
	if(root == NULL){
		node *new = malloc(sizeof(node));

		new->key = key;
		new->rank = 0;
		new->left = NULL;
		new->right = NULL;

		return new;
	}

	if(key <= root->key)
		root->left = insert(root->left, key);
	else
		root->right = insert(root->right, key);

	return root;
}

int mediana(node *root, int rank, int *r){
	if(root == NULL) return -1;

	int k = mediana(root->left, rank, r);
	if(k != -1) return k;

	root->rank = ++*r;
	if(root->rank == rank) return root->key;
	return mediana(root->right, rank, r);
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(){
	int n, i, key;
	int rank = -1;
	node *root = NULL;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root = insert(root, key);
	}

	printf("%d\n", mediana(root, n/2, &rank));

	free_tree(root);
	return 0;
}
