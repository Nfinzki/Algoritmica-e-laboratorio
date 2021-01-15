/*Scrivere un programma che riceva in input una sequenza di N interi positivi e costruisca un albero ternario
di ricerca non bilanciato. L’ordine di inserimento dei valori nell’albero deve coincidere con quello
della sequenza.
Ogni nodo in un albero ternario di ricerca pu`o avere fino a tre figli:
figlio sinistro, figlio centrale e figlio destro. L’inserimento di un nuovo valore
avviene partendo dalla radice dell’albero e utilizzando la seguente regola. Il
valore da inserire viene confrontato con la chiave del nodo corrente. Ci sono
tre possibili casi in base al risultato del confronto:
1. se il valore `e minore della chiave del nodo corrente, esso viene inserito
ricorsivamente nel sottoalbero radicato nel figlio sinistro;
2. se il valore `e divisibile per la chiave del nodo corrente, esso viene
inserito ricorsivamente nel sottoalbero radicato nel figlio centrale;
3. in ogni altro caso il valore viene inserito ricorsivamente nel sottoalbero
radicato nel figlio destro.
Il programma deve stampare il numero di nodi dell’albero che hanno tre
figli.
La prima riga contiene la lunghezza N della sequenza. Le N righe successive
contengono ciascuna un elemento da inserire nell’albero.
L’output `e costituito da una singola riga che contiene il numero di nodi
dell’albero che hanno tre figli.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node *left;
	struct _node *middle;
	struct _node *right;
}node;

node *insert(node *root, int key){
	if(root == NULL){
		node *new = malloc(sizeof(node));
		new->key = key;
		new->left = NULL;
		new->middle = NULL;
		new->right = NULL;

		return new;
	}

	if(key % root->key == 0)
		root->middle = insert(root->middle, key);
	else{
		if(key <= root->key)
			root->left = insert(root->left, key);
		else
			root->right = insert(root->right, key);
	}
	return root;
}


void stampa(const node *root){
	if(root != NULL){
		printf("%d\n", root->key);
		stampa(root->left);
		stampa(root->middle);
		stampa(root->right);
	}
}


int children(const node *root){
	if(root == NULL)
		return 0;

	if(root->left != NULL && root->middle != NULL && root->right != NULL)
		return 1 + children(root->left) + children(root->middle) + children(root->right);
	else
		return children(root->left) + children(root->middle) + children(root->right);
}

void free_list(node *root){
	if(root != NULL){
		free_list(root->left);
		free_list(root->middle);
		free_list(root->right);
		free(root);
	}
}

int main(){
	int n, i, key;
	node *root = NULL;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root = insert(root, key);
	}

	printf("%d\n", children(root));
//stampa(root);

	free_list(root);

	return 0;
}
