/*
Il programma deve leggere una sequenza di n ≥ 2 interi ed inserirli in un
albero binario di ricerca non bilanciato. Si utilizzi la seguente struct per
definire i nodi dell’albero:
Al termine dell’inserimento, stampare il secondo elemento pi`u grande nella
sequenza in input tramite una opportuna visita sull’albero. Si assuma che
il numero n di interi in input sia non inferiore a due.
Nota: Al fine del superamento della prova, la visita deve richiedere tempo
al pi`u lineare rispetto all’altezza dell’albero.
Suggerimento: osservare attentamente i due esempi forniti nelle pagine
successive pu`o essere utile nel determinare la corretta strategia di visita da
implementare.
L’input `e formattato nel seguente modo. La prima riga contiene il numero
n di interi da inserire nell’albero. Seguono poi n righe, una per ogni intero
nella sequenza.
L’output `e costituito da una singola riga contenente l’intero identificato dal
programma*/

#include <stdio.h>
#include <stdlib.h>

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

node *max(node *root, node **parent){
	node *tmp = root;

	while(tmp->right != NULL){
		*parent = tmp;
		tmp = tmp->right;
	}

	return tmp;
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(){
	node *root = NULL;
	node *parent = NULL;
	node *max2 = NULL;
	int n, val, i;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &val);
		root = insert(root, val);
	}

	max2 = max(root, &parent);

	if(max2->left != NULL)
		printf("%d\n", max(max2->left, &parent)->key);
	else
		printf("%d\n", parent->key);

	free_tree(root);
	return 0;
}
