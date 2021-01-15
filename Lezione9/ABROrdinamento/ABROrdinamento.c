/*Scrivere un programma che legga da tastiera una sequenza di N interi distinti e li inserisca
in un albero binario di ricerca (senza ribilanciamento).
Il programma deve quindi utilizzare un’opportuna visita dell’albero per
stampare gli interi della sequenza in ordine non decrescente.
Nella prima riga dell’input si trova la lunghezza N della sequenza; nelle
successive N righe si trovano gli interi che compongono la sequenza.
L’output contiene la sequenza ordinata degli elementi inseriti nell’albero,
uno per riga*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node *left;
	struct _node *right;
}node;

node *insert(node *root, int key){
	if(root == NULL){ //Right spot for element
		node *new = malloc(sizeof(node));
		new->key = key;
		new->left = NULL;
		new->right = NULL;

		return new;
	}

	if(key <= root->key)
		root->left = insert(root->left, key); //The element needs to stay in the left subtree
	else
		root->right = insert(root->right, key); //The element needs to stay in the right subtree
	return root;
}

void sorting(const node *root){
	if(root != NULL){
		sorting(root->left); //Print the left subtree
		printf("%d\n", root->key); //Print the current node
		sorting(root->right); //Print the right subtree
	}
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left); //Deallocate the left subtree
		free_tree(root->right); //Deallocate the right subtree
		free(root); //Deallocate the current node
	}
}

int main(){
	int n, i, key;
	node *root = NULL;

	scanf("%d", &n);

	//Insert n elements in the tree
	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root = insert(root, key);
	}

	sorting(root); //Print the sorted tree

	free(root); //Deallocate memory

	return 0;
}
