/*
Il programma deve leggere una sequenza di n ≥ 2 interi ed inserirli in un
albero binario di ricerca non bilanciato. Gli interi sono tutti positivi,
con possibili duplicati. Si utilizzi la seguente struct per definire i nodi
dell’albero:
Al termine dell’inserimento, il programma deve leggere due interi, x e y,
e stampare il loro Lowest Common Ancestor (lca), i.e., la chiave del pi`u
profondo nodo dell’albero da cui discendono i cammini contenenti x e y.
Ogni nodo `e inteso come il discendente di s´e stesso. A tal fine, si implementi
la seguente funzione:

Note:
• Si assuma che x e y siano presenti nell’albero, quindi che il loro lca
esista sempre.
• Al fine del superamento della prova, la visita deve richiedere tempo al
pi`u lineare rispetto all’altezza dell’albero

Suggerimenti:
• Si faccia uso della propriet`a di ricerca degli alberi binari di ricerca.
• Osservare attentamente gli esempi forniti nelle pagine successive pu`o
essere utile nel determinare la corretta strategia implementativa.

L’input `e formattato nel seguente modo. La prima riga contiene il numero
n di interi da inserire nell’albero. Seguono poi n righe, una per ogni intero
nella sequenza. Infine, le ultime due righe corrispondono ai valori di x e y.
L’output `e costituito da una singola riga contenente lca(x, y) e il carattere di new-line ‘\n’.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct n {
	int key;
	struct n* left;
	struct n* right;
} node;

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

int lca(node *root, int x, int y){
	if(root == NULL) return -1;

	if(x <= root->key && root->key <= y)
		return root->key;

	if(x <= root->key && y <= root->key)
		return lca(root->left, x, y);
	else
		return lca(root->right, x, y);
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(){
	int n, i, key, x, y;
	node *root = NULL;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root = insert(root, key);
	}

	scanf("%d", &x);
	scanf("%d", &y);

	if(x < y)
		printf("%d\n", lca(root, x, y));
	else
		printf("%d\n", lca(root, y, x));

	free_tree(root);
	return 0;
}
