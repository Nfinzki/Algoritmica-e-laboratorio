/*Scrivere un programma che riceve in input due sequenze di N interi positivi,
dalle quali devono essere costruiti due alberi binari di ricerca NON bilanciati
(un albero per sequenza).
Al programma viene data una chiave intera K. Si pu`o assumere che l’intero
K sia presente in entrambe le sequenze. Il programma deve verificare che
le sequenze di chiavi incontrate nel cammino che dalla radice porta al nodo
con chiave K nei due alberi coincidano.
L’input `e formattato nel seguente modo:
• La prima riga contiene gli interi N e K, separati da uno spazio.
• Seguono 2N righe contenenti ognuna un intero. I primi N interi appartengono alla prima sequenza, mentre
i successivi N interi appartengono alla seconda sequenza.
L’output `e costituito da una singola riga che contiene il risultato del programma: 1 se le due sequenze di
chiavi coincidono, 0 altrimenti.*/

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

int check(const node *root1, const node *root2, int key){
	if(root1 == NULL || root2 == NULL || root1->key != root2->key)
		return 0;
	if(root1->key == key && root2->key == key)
		return 1;

	if(key <= root1->key)
		return check(root1->left, root2->left, key);
	else
		return check(root1->right, root2->right, key);
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(){
	int n, k, i, key;
	node *root1 = NULL;
	node *root2 = NULL;

	scanf("%d%d", &n, &k);

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root1 = insert(root1, key);
	}

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root2 = insert(root2, key);
	}

	printf("%d\n", check(root1, root2, k));

	free_tree(root1);
	free_tree(root2);

	return 0;
}
