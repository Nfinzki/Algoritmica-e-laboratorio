/*Scrivere un programma che legga da tastiera un grafo indiretto e stampi 1
se il grafo `e bipartito, 0 altrimenti. Il grafo `e rappresentato nel seguente
formato: la prima riga contiene il numero n di nodi, le successive n righe
contengono, per ciascun nodo i, con 0 ≤ i < n, il numero ni di archi uscenti
da i seguito da una lista di ni nodi destinazione, rappresentati con i numeri
[0, n). Si assuma che l’input contenga un grafo indiretto, e quindi che per
ciascun arco da i a j esista anche l’arco da j ad i.
Un grafo bipartito `e un grafo tale che l’insieme dei suoi vertici si pu`o
partizionare in due sottoinsiemi in cui ogni vertice `e collegato solo a vertici
appartenenti alla partizione opposta.
Suggerimento: un grafo `e bipartito se e solo se `e possibile colorarlo usando due colori.
Colorare il grafo corrisponde ad assegnare a ciascun vertice
un colore diverso da quello dei suoi vertici adiacenti.
L’input `e costituito da:
• una riga contenente il numero n di nodi del grafo;
• n righe, una per ciasun nodo i, con i ∈ [0, n), nel seguente formato:
– numero ni di archi uscenti da i;
– lista di ni nodi destinazione, rappresentati con i numeri [0, n).
L’output contiene una riga contenente 1 se il grafo `e bipartito, 0 altrimenti*/

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

int graph_color(edges *E, int *colors, int from, int c){
	//Checks if the node is already colored and if is colored with the right color otherwise return 0
	if(colors[from] != -1 && colors[from] == !c)
		return 0;

	colors[from] = c; //Color the node

	//Checks if all the adjacent nodes can the colored with the opposite color
	for(int i = 0; i < E[from].num_edges; i++){
		int to = E[from].edges[i];

		//Checks if all the adjacent nodes are colored and the node can be colored with
		//the opposite color
		if(colors[to] == -1 && !graph_color(E, colors, to, !c))
			return 0;

		//Checks if the node is already colored and the color is correct
		if(colors[to] != -1 && colors[to] != !c)
			return 0;
	}

	return 1;
}

int graph_is_bipartite(edges *E, int n){
	int i;
	int *colors = malloc(sizeof(int) * n); //Allocate an array of colors

	//Initialize the array
	for(i = 0; i < n; i++)
		colors[i] = -1;

	//Checks if all the nodes are colored and the node can be colored otherwise return 0
	for(i = 0; i < n; i++){
		if(colors[i] == -1 && !graph_color(E, colors, i, 0))
			return 0;
	}

	free(colors); //Deallocate memory
	return 1;
}

void free_graph(edges *E, int n){
	int i;
	for(i = 0; i < n; i++) //Deallocate all the arrays
		free(E[i].edges);

	free(E); //Deallocate the graph
}

int main(){
	int n, from;

	//Read the graph dimension
	scanf("%d", &n);

	edges *E = graph_init(n); //Initializate the graph

	//Read and insert all the edges for all the nodes
	for(from = 0; from < n; from++){
		int ne, i;
		scanf("%d", &ne); //Number of edges for one node

		E[from].edges = malloc(sizeof(int) * ne); //Allocate an array

		for(i = 0; i < ne; i++){ //Read edges for the from-node
			int to;
			scanf("%d", &to);
			graph_add_edge(E, from, to); //Insert the edge
		}
	}

	printf("%d\n", graph_is_bipartite(E, n)); //Calculate if the graph is bipartite

	free_graph(E, n); //Deallocate the graph
	return 0;
}
