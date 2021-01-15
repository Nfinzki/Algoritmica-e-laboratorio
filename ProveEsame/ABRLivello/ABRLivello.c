/*Il livello k di un albero `e dato dall’insieme di tutti i nodi dell’albero ad
altezza k. Si ricorda che l’altezza di un nodo u in un albero T radicato in r
`e definita come la lunghezza del cammino in T da r ad u.
Si consideri ad esempio il seguente albero binario di ricerca (ABR, d’ora
in poi):
La radice, in colore rosso, `e al livello 0, mentre i nodi verdi sono al livello 1,
i blu al livello 2 ed i gialli al livello 3.
Il programma, data una sequenza di interi distinti ed un livello k, dovr`a
costruire l’ABR contenente la sequenza di interi in input e stampare i nodi
al livello k in ordine crescente, una linea per ogni intero.
L’input `e formattato nel seguente modo. La prima riga contiene l’intero
n. Seguono n righe, una per ciascun intero della sequenza S da includere
nell’ABR T. Gli interi in S sono distinti. Segue infine una riga contente
l’intero k, il livello da stampare. L’intero k pu`o essere maggiore dell’altezza
dell’albero.
L’output `e costituito dagli interi nell’ABR T letto in input al livello k, in
ordine crescente, un intero per riga. L’output deve essere vuoto nel caso in
cui k sia maggiore dell’altezza dell’albero T.
*/

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

void level(const node *root, int k){
	if(root == NULL) return; //The tree doesn't have the level k

	if(k == 0)
		printf("%d\n", root->key); //The level is reached
	else{
		level(root->left, k-1); //The level isn't reached. First print the left subtree
		level(root->right, k-1);//then the right subtree
	}
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left); //Deallocate the left subtree
		free_tree(root->right); //Deallocate the right subtree
		free(root); //Deallocate the root
	}
}

int main(){
	int n, i, key, k;
	node *root = NULL;

	scanf("%d", &n);

	//Read n elements
	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root = insert(root, key);
	}

	scanf("%d", &k); //Read level

	level(root, k); //Print the k level

	free_tree(root); //Deallocate memory
	return 0;
}
