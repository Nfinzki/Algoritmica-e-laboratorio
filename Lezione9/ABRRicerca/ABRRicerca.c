/*Scrivere un programma che legga da tastiera una sequenza di N interi distinti
e li inserisca in un albero binario di ricerca (senza ribilanciamento).
Il programma entra poi in un ciclo infinito nel quale legge un intero i da
tastiera e lo cerca nell’albero. Il ciclo termina solo se l’intero i inserito `e
strettamente minore di 0. Se i si trova nell’albero stampa la profondit`a alla
quale l’elemento si trova (contando da 0), altrimenti stampa NO.
L’input `e costituito da:
• una riga contenente la lunghezza N della sequenza;
• N righe contenenti gli interi che compongono la sequenza;
• una sequenza di dimensione non nota di richieste espresse con interi.
Se i `e minore di 0, il programma termina (non ci sono pi`u richieste);
altrimenti i rappresenta il valore da cercare.
L’output contiene una riga per ogni richiesta di ricerca, contenente la profondit`a a cui l’elemento si trova
(contando da 0) se esso `e presente nell’albero,
NO altrimenti.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node *left;
	struct _node *right;
}node;

node* insert(node* root, int key){
	if(root == NULL){ //Right spot in the tree for key
		node* new = malloc(sizeof(node));
		new->key = key;
		new->left = NULL;
		new->right = NULL;
		return new;
	}

	if(key <= root->key)
		root->left = insert(root->left, key); //Key is going to be in the left subtree
	else
		root->right = insert(root->right, key); //Key is going to be in the right subtree

	return root;
}

int search(node* root, int key){
	if(root == NULL) //Key not found
		return -1;

	if(key == root->key) return 0; //Key found

	int res;
	if(key <= root->key) //Recursive call to calculate the depth of the sons
		res = search(root->left, key);
	else
		res = search(root->right, key);

	return res >= 0 ? 1+res : -1; //If the key wasn't found return -1 otherwise return depth increased by 1
}

int main(){
	int n, i, key, ris;
	node *root = NULL;

	scanf("%d", &n);

	//Read n elements
	for(i = 0; i < n; i++){
		scanf("%d", &key);
		root = insert(root, key); //Insert an element in the tree
	}

	while(1){
		scanf("%d", &i);
		if(i < 0) break;

		ris = search(root, i); //Search the element in the tree
		if(ris < 0)
			printf("NO\n"); //Element not found
		else
			printf("%d\n", ris); //Element found, depth
	}

	return 0;
}
