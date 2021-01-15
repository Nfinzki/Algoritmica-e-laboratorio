/*Dato un albero binario di ricerca, definiamo la somma di un cammino come
la somma delle chiavi dei nodi appartenenti al cammino. Consideriamo i
cammini di somma massima (si noti come, in generale, possono esistere pi`u
cammini di somma massima). L’obiettivo dell’esercizio `e quello di stampare
la chiave pi`u piccola appartenente ad un cammino di somma massima.
Scrivere un programma che legga da tastiera una sequenza di N chiavi
(interi positivi distinti) e le inserisca in un albero binario di ricerca (senza
ribilanciamento) nello stesso ordine con il quale vengono fornite in input. Il
programma deve stampare la chiave pi`u piccola appartenente ad un cammino
di somma massima.
NOTA 1: Affinch´e l’esame sia superato, la complessit`a in tempo dell’algoritmo deve essere lineare nel
numero N dei nodi.
NOTA 2: Dato che le chiavi sono interi positivi, tutti i cammini di somma
massima iniziano dalla radice dell’albero.
L’input `e cos`ı formato:
• la prima riga contiene il numero N di chiavi da inserire nell’albero
binario di ricerca;
• le successive N righe contengono le chiavi, una per riga; ogni chiave `e
un intero positivo.
L’output `e costituito dalla chiave pi`u piccola appartenente ad un cammino
di somma massima.
*/
#include <stdio.h>
#include <stdlib.h>

#define min(x, y) (x) < (y) ? (x) : (y)

typedef struct _node{
	int key;
	struct _node *left;
	struct _node *right;
}node;

typedef struct _path{
	int max_sum;
	int min;
}path;

node *insert(node *root, int key){
	if(root == NULL){
		node *new = malloc(sizeof(node));
		new->key = key;
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

path max_sum_path(node *root){
	if(root == NULL){
		path p;
		p.max_sum = 0;
		p.min = 0;
		return p;
	}

	path left = max_sum_path(root->left);
	path right = max_sum_path(root->right);

	if(left.max_sum + root->key >= right.max_sum + root->key){ //Choose the max path
		if(left.max_sum == 0) //Root is a leaf
			left.min = root->key; //The min is the current key
		left.max_sum = left.max_sum + root->key; //Update the max path
		left.min = min(left.min, root->key); //Update the min
		return left;
	} else {
		if(right.max_sum == 0) //Root is a leaf
			right.min = root->key; //The min is the current key
		right.max_sum = right.max_sum + root->key; //Update the max path
		right.min = min(right.min, root->key); //Update the min
		return right;
	}
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
	node *root = NULL;
	path p;

	scanf("%d", &n);

	//Read n elements and insert in the tree
	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root = insert(root, key);
	}

	p = max_sum_path(root); //Calculate che min element of the max sum path

	printf("%d\n", p.min);

	free_tree(root); //Deallocate memory

	return 0;
}
