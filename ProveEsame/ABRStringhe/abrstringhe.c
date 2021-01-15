/*Il programma deve leggere una sequenza di N coppie chiave e valore. Le
N chiavi sono stringhe distinte di lunghezza al pi`u 100 caratteri, per le
quali deve essere costruito un albero binario di ricerca non bilanciato. I
valori sono interi positivi. Per l’inserimento delle coppie nell’albero si deve
rispettare il loro ordine nella sequenza.
Al programma viene data in input una stringa s che si pu`o assumere
essere presente tra le chiavi della sequenza. Sia u il nodo dell’albero avente
chiave s. Il programma deve indentificare l’intero maggiore tra tutti gli interi
dei nodi che si trovano nel sottoalbero radicato in u, nodo u compreso.
L’input `e formattato nel seguente modo. La prima riga contiene l’intero N.
Seguono poi 2N righe, due righe per coppia. La prima riga della coppia contiene la chiave,
mentre la seconda contiene il valore. L’ultima riga dell’input
contiene la stringa s.
L’output `e costituito da una singola riga contenente l’intero identificato dal
programma.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x, y) ((x) < (y) ? (y) : (x))

typedef char* string;

typedef struct _node{
	string key;
	int val;
	struct _node *left;
	struct _node *right;
}node;

node *insert(node *root, string key, int val){
	if(root == NULL){
		node *new = (node*) malloc(sizeof(node));
		new->key = key,
		new->val = val;
		new->left = NULL;
		new->right = NULL;

		return new;
	}

	if(strcmp(root->key, key) <= 0)
		root->left = insert(root->left, key, val);
	else
		root->right = insert(root->right, key, val);

	return root;
}

int max(node *root){
	if(root == NULL)
		return -1;
	int max_l, max_r, max_val;

	max_l = max(root->left);
	max_r = max(root->right);

	max_val = MAX(max_l, max_r);
	return max_val = MAX(max_val, root->val);
}

int search(node *root, string key){
	if(root == NULL)
		return -1;

	if(strcmp(root->key, key) == 0)
		return max(root);

	if(strcmp(root->key, key) <= 0)
		return search(root->left, key);
	else
		return search(root->right, key);
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root->key);
		free(root);
	}
}

int main(){
	node *root = NULL;
	int n, i;
	string s = (char*) malloc(sizeof(char) * 101);

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		string key = (char*) malloc(sizeof(char) * 101);
		int val;

		scanf("%s", key);
		scanf("%d", &val);

		root = insert(root, key, val);
	}

	scanf("%s", s);

	printf("%d\n", search(root, s));

	free(s);
	free_tree(root);
	return 0;
}
