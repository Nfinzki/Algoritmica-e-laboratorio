/*Scrivere un programma che legga da tastiera un grafo indiretto e stampi 1
se il grafo `e connesso, 0 altrimenti. Il grafo `e rappresentato nel seguente
formato: la prima riga contiene il numero n di nodi, le successive n righe
contengono, per ciascun nodo i, con 0 ≤ i < n, il numero ni di archi uscenti
da i seguito da una lista di ni nodi destinazione, rappresentati con i numeri
[0, n). Si assuma che l’input contenga un grafo indiretto, e quindi che per
ciascun arco da i a j esiste anche l’arco da j ad i.
Un grafo `e connesso quando esiste un percorso tra due vertici qualunque
del grafo. Il programma deve eseguire una visita DFS (a partire da un nodo
qualunque, perch´e?) del grafo per stabilire se questo `e connesso.
L’input `e costituito da:
• una riga contenente il numero n di nodi del grafo;
• n righe, una per ciasun nodo i, con i ∈ [0, n), nel seguente formato:
– numero ni di archi uscenti da i;
– lista di ni nodi destinazione, rappresentati con i numeri [0, n).
L’output contiene una riga contenente 1 se il grafo `e connesso, 0 altrimenti.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _edges{
	int num_edges;
	int *edges;
}edges;

edges *graph_init(int n){
	edges *E = malloc(sizeof(edges) * n); //Allocate a graph with n nodes

	//Initialize all the nodes
	for(int i = 0; i < n; i++)
		E[i].num_edges = 0;
	return E;
}

void graph_add_edge(edges *E, int from, int to){
	E[from].edges[E[from].num_edges] = to; //Add the edge
	E[from].num_edges++; //Increase the number of edges in the node
}

void dfs(edges *E, int from, int *colors){
	int i, dest;

	for(i = 0; i < E[from].num_edges; i++){ //For all the edges in the node
		dest = E[from].edges[i];
		if(!colors[dest]){ //If the node isn't been visited yet
			colors[dest] = 1;
			dfs(E, dest, colors); //Visit is recursively
		}
	}
}

int graph_is_connected(edges *E, int n, int from){
	int *colors = malloc(sizeof(int) * n); //Allocate an array of the same dimension of the graph
	int i;

	//Initialize the array
	for(i = 0; i < n; i++)
		colors[i] = 0;

	colors[from] = 1; //Colors the first node

	dfs(E, from, colors); //Calls the DFS starting from 'from'

	//Check if the graph is connected
	for(i = 0; i < n; i++)
		if(colors[i] != 1)
			return 0;

	free(colors); //Deallocate the memory of the array
	return 1;
}

void free_graph(edges *E, int n){
	int i;
	for(i = 0; i < n; i++){//Deallocate all the arrays
		free(E[i].edges);
	}
	free(E); //Deallocate the graph
}

int main(){
	edges *E;
	int n, i, j;

	//Read the graph dimension
	scanf("%d", &n);

	E = graph_init(n); //Initializate the graph

	//Read and insert all the edges for all the nodes
	for(i = 0; i < n; i++){
		int connection;
		scanf("%d", &connection); //Number of edges for one node

		E[i].edges = malloc(sizeof(int) * connection); //Allocate an array

		for(j = 0; j < connection; j++){ //Read edges for the i-node
			int to;
			scanf("%d", &to);
			graph_add_edge(E, i, to); //Insert the edge
		}
	}

	printf("%d\n", graph_is_connected(E, n, 0)); //Calculate if the graph is connected

	free_graph(E, n); //Deallocate memory
	return 0;
}
