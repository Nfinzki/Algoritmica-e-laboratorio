/*
Dato un albero binario, definiamo “visita sinistra” dell’albero la visita che,
partendo dalla radice, opera ricorsivamente come segue: se un nodo ha un
figlio sinistro s, tale figlio `e visitato e la visita prosegue da s; altrimenti
termina. Detto in altri termini, sono visitati tutti e soli i nodi presenti nel
cammino che, partendo dalla radice, sceglie sempre e soltanto i figli sinistri,
finch´e ce ne sono.
In maniera speculare, definiamo “visita destra” dell’albero la visita che,
partendo dalla radice, opera ricorsivamente come segue: se un nodo ha
un figlio destro d, tale figlio `e visitato e la visita prosegue da d; altrimenti
termina.
Per ogni nodo u, consideriamo il sottoalbero radicato in u. Si definiscono:
• L(u): il numero di nodi visitati dalla “visita sinistra” del sottoalbero,
escluso u (zero se il nodo u `e una foglia oppure se non ha un figlio
sinistro);
• R(u): il numero di nodi visitati dalla “visita destra” del sottoalbero,
escluso u (zero se il nodo u `e una foglia oppure se non ha un figlio
destro);
Scrivere un programma che legga da tastiera una sequenza di N interi
distinti e li inserisca in un albero binario di ricerca (senza ribilanciamento)
nello stesso ordine con il quale vengono forniti in input. Il programma
deve poi stampare in ordine crescente le chiavi dei nodi che soddisfano la
condizione L(u) > R(u).
NOTA: Affinch´e l’esame sia superato, la complessit`a in tempo dell’algoritmo deve essere lineare.
L’input `e cos`ı formato:
• la prima riga contiene il numero N di interi da inserire nell’albero
binario di ricerca;
• le successive N righe contengono gli N interi, uno per riga.
L’output `e costituito dalle chiavi dei nodi che soddisfano la condizione
L(u) > R(u). Tali chiavi vanno stampate in ordine crescente, una per riga*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	int L;
	int R;
	struct _node *left;
	struct _node *right;
}node;

typedef struct _left_right{
	int l;
	int r;
}left_right;

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

left_right calculate_L_R(node *root){
	if(root == NULL){ //Base case
		left_right lr = {-1, -1};
		return lr;
	}

	root->L = calculate_L_R(root->left).l + 1; //Node visited in the left subtree + the current one
	root->R = calculate_L_R(root->right).r + 1; //Node visited in the right subtree + the current one
	left_right lr = {root->L, root->R};
	return lr;
}

void visit(const node *root){
	if(root != NULL){
		visit(root->left); //Recursive call to the left subtree
		if(root->L > root->R) //Condition to print
			printf("%d\n", root->key);
		visit(root->right); //Recursive call to the right subtree
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
	int n, i, k;
	node *root = NULL;

	scanf("%d", &n);

	//Read n elements and insert in the list
	for(i = 0; i < n; i++){
		scanf("%d", &k);
		root = insert(root, k);
	}

	calculate_L_R(root); //Calculate the node visited
	visit(root); //Makes the visit and print all the nodes that satisfy the condition
	free_tree(root);//Deallocate memory
	return 0;
}
