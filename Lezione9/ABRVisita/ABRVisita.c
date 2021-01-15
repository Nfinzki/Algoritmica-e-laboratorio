/*Scrivere un programma che legga da tastiera una sequenza di N interi distinti e li inserisca in un albero
binario di ricerca (senza ribilanciamento).
Il programma deve visitare opportunamente l’albero e restituire la sua altezza.
Nella prima riga dell’input si trova la lunghezza N della sequenza; nelle
successive N righe si trovano gli interi che compongono la sequenza.
L’output contiene unicamente l’altezza dell’albero.
*/

#include <stdio.h>
#include <stdlib.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct _node{
	int key;
	struct _node *left;
	struct _node *right;
}node;

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

int height(const node *root){
	if(root == NULL)
		return 0;

	return max(height(root->left), height(root->right)) + 1; //The height of the current node have the max height between the left and right child + 1
}

int main(){
	int N, i, key;
	node *root = NULL;

	scanf("%d", &N);

	//Insert N elements in the tree
	for(i = 0; i < N; i++){
		scanf("%d", &key);
		root = insert(root, key);
	}

	printf("%d\n", height(root)); //Calculate and print the tree height

	return 0;
}
