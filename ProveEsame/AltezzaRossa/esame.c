#include <stdio.h>
#include <stdlib.h>
#define max(x, y) ((x) < (y) ? (y) : (x))

typedef struct _node{
	int key;
	int color;
	struct _node *left;
	struct _node *right;
}node;

node *insert(node* root, int key, int color){
	if(root == NULL){ //Right spot in the tree for key
		node* new = (node*) malloc(sizeof(node));
		new->key = key;
		new->color = color;
		new->left = NULL;
		new->right = NULL;
		return new;
	}

	if(key <= root->key)
		root->left = insert(root->left, key, color); //Key is going to be in the left subtree
	else
		root->right = insert(root->right, key, color); //Key is going to be in the right subtree

	return root;
}

struct result{
	int is_balanced;
	int height;
};

struct result one_balanced(node *root){
	if(root == NULL){
		struct result res = {1, -1};
		return res;
	}

	struct result left = one_balanced(root->left);
	struct result right = one_balanced(root->right);

	struct result res;
	if(root->color == 0 && left.height == -1 && right.height == -1)
		res.height = 0;
	else{
		if(root->color == 0)
			res.height = max(left.height, right.height) + 1;
		else
			res.height = max(left.height, right.height);
	}

	int is_balanced = abs(left.height - right.height) <= 1;
	int subtree_balanced = left.is_balanced && right.is_balanced;

	res.is_balanced = is_balanced && subtree_balanced;

	return res;
}

void free_tree(node* root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

int main(){
	node *root = NULL;
	int n, i, key, color;
	int res;

	scanf("%d", &n);

	for(i = 0; i < n; i++){
		scanf("%d", &key);
		scanf("%d", &color);
		root = insert(root, key, color);
	}

	res = one_balanced(root).is_balanced;

	if(res)
		printf("TRUE\n");
	else
		printf("FALSE\n");

	free_tree(root);
	return 0;
}
