#include <stdio.h>
#include <stdlib.h>
#define max(x, y) ((x) < (y) ? (y) : (x))

typedef struct _node{
	int key;
	struct _node* left;
	struct _node* right;
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

struct result{
	int nodi;
	int max;
};

struct result sbilanciato(node *root){
	if(root == NULL){
		struct result res = {0, 0};
		return res;
	}

	struct result left = sbilanciato(root->left);
	struct result right = sbilanciato(root->right);

	int n = left.nodi + right.nodi + 1;
	int max_s;
	max_s = max(left.max, right.max);
	max_s = max(max_s, abs(left.nodi - right.nodi));

	struct result res = {n, max_s};
	return res;
}

void free_tree(node *root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
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

	printf("%d\n", sbilanciato(root).max);

	free_tree(root);

	return 0;
}
