/*Scrivere un programma che legga da tastiera un grafo diretto, una sequenza
di m query, ciascuna composta dagli indici di due nodi del grafo e stampi,
per ciascuna query, la lunghezza del percorso minimo che collega i rispettivi
due nodi della query. Il grafo `e rappresentato nel seguente formato: la
prima riga contiene il numero n di nodi, le successive n righe contengono,
per ciascun nodo i, con 0 ≤ i < n, il numero ni di archi uscenti da i seguito
da una lista di ni nodi destinazione, rappresentati con i numeri [0, n).
Il percorso minimo dal nodo i al nodo j `e il percorso che porta da i a j
che attraversa il minor numero di archi. A tale scopo si esegua una visita
BFS del grafo a partire dal nodo i per stabilire il percorso minimo che porta
al nodo j, qualora questo esista.
L’input `e costituito da:
• una riga contenente il numero n di nodi del grafo;
• n righe, una per ciasun nodo i, con i ∈ [0, n), nel seguente formato:
– numero ni di archi uscenti da i;
– lista di ni nodi destinazione, rappresentati con i numeri [0, n).
• una riga contenente il numero m di query;
• m righe, una per ciasuna query, contenenti l’indice del nodo di partenza
e l’indice del nodo di destinazione.
L’output contiene m righe contenenti ciascuna la lunghezza del percorso
minimo che collega i due nodi della rispettiva query e -1 quando i nodi non
sono collegati.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _edges{
	int num_edges;
	int *edges;
}edges;

typedef struct _queue{
	int *values;
	int capacity;
	int offset;
}queue;

void queue_init(queue *q, int n){
	q->values = malloc(sizeof(int) * n); //Allocate the memory for the queue
	q->capacity = 0; //Initializate the number of elements in the queue
	q->offset = 0; //Initializate the number of elements removed from the queue
}

void queue_push(queue *q, int val){
	q->values[q->capacity] = val; //Add an element in the tail of the queue
	q->capacity++; //Increase the current number of elements added in queue
}

int queue_pop(queue *q){
	int ris = q->values[q->offset];
	q->offset++; //Increase the number of elements removed from the queue
	return ris;
}

int queue_isEmpty(queue *q){
	return q->offset == q->capacity ? 1 : 0; //Check if the queue is empty
}

void queue_deinit(queue *q){
	free(q->values); //Deallocate the queue
}

edges *graph_init(int n){
	edges *g = malloc(sizeof(edges) * n); //Allocate the space for n nodes
	int i;

	for(i = 0; i < n; i++) //Initializate the current number of edges in the node
		g[i].num_edges = 0;
	return g;
}

void graph_add_edge(edges *g, int from, int to){
	g[from].edges[g[from].num_edges] = to; //Adds a connection to a node
	g[from].num_edges++; //Increase the number of connections
}

int bfs(edges *g, int n, int from, int to){
	int i, src, dest;
	queue q;
	int res;

	int *distances = malloc(sizeof(int) * n); //Allocate the space for n elements

	//Initializate all the elements at distance -1
	for(i = 0; i < n; i++){
		distances[i] = -1;
	}
	distances[from] = 0; //Initializate the source element to distance 0

	queue_init(&q, n); //Initializate the queue
	queue_push(&q, from); //Push the source element in the queue

	while(!queue_isEmpty(&q)){
		src = queue_pop(&q); //Extract the head from the queue
		for(i = 0; i < g[src].num_edges; i++){ //For all the edges of the node extracted
			dest = g[src].edges[i];

			if(distances[dest] == -1){ //The node isn't been visited yet
				distances[dest] = distances[src] + 1; //Update the distance
				queue_push(&q, dest); //Push the edge element in the queue
			}
		}
	}

	queue_deinit(&q); //Deallocate the queue

	res = distances[to]; //Calculate the result
	free(distances); //Deallocate the array
	return res;
}

void free_graph(edges *g, int n){
	int i;
	for(i = 0; i < n; i++)	//Deallocate all the adjacent edges
		free(g[i].edges);
	free(g); //Deallocate the graph
}

int main(){
	edges *g;
	int n, from, q, i, to, ne;

	//Read the dimension of the graph
	scanf("%d", &n);

	//Initializate the graph
	g = graph_init(n);

	//Read the graph
	for(from = 0; from < n; from++){

		scanf("%d", &ne);

		g[from].edges = malloc(sizeof(int) * ne); //Allocate memory for the adjacent edges

		//Read all the adjacent edges of the current edge
		for(i = 0; i < ne; i++){
			scanf("%d", &to);
			graph_add_edge(g, from, to); //Insert the edge in the adjacent array
		}
	}

	//Read the number of querys
	scanf("%d", &q);

	for(i = 0; i < q; i++){
		scanf("%d", &from); //Source
		scanf("%d", &to); //Destination

		printf("%d\n", bfs(g, n, from, to)); //Print the result
	}

	free_graph(g, n); //Deallocate the graph
	return 0;
}
