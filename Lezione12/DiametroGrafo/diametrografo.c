/*
Scrivere un programma che legga da tastiera un grafo diretto e stampi il
diametro del grafo. Il grafo `e rappresentato nel seguente formato: la prima
riga contiene il numero n di nodi, le successive n righe contengono, per
ciascun nodo i, con 0 ≤ i < n, il numero ni di archi uscenti da i seguito da
una lista di ni nodi destinazione, rappresentati con i numeri [0, n).
Il diametro di un grafo `e la lunghezza del “pi`u lungo cammino minimo”
fra tutte le coppie di nodi. Il programma deve eseguire una visita BFS a
partire da ciascun nodo i del grafo per stabilire il cammino minimo pi`u lungo
a partire da i, e quindi stampare il massimo tra tutti questi.
L’input `e costituito da:
• una riga contenente il numero n di nodi del grafo;
• n righe, una per ciasun nodo i, con i ∈ [0, n), nel seguente formato:
– numero ni di archi uscenti da i;
– lista di ni nodi destinazione, rappresentati con i numeri [0, n).
L’output contiene una sola riga contenente il diametro del grafo se questo `e
connesso, -1 altrimenti.*/

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
	q->values = malloc(sizeof(int) * n); //Initializate an array
	q->capacity = 0; //Initializate the capacity occupated
	q->offset = 0; //Initializate the number of elements extracted
}

void queue_deinit(queue *q){
	free(q->values); //Deallocate the array
	q->capacity = 0;
	q->offset = 0;
}

void queue_enqueue(queue *q, int val){
	q->values[q->capacity++] = val; //Insert in the tail the element and increase the capacity
}

int queue_isEmpty(queue *q){
	return q->offset == q->capacity ? 1 : 0; //Checks if the queue is empty
}

int queue_dequeue(queue *q){
	return q->values[q->offset++]; //Extract the element in the head and increase the offset
}

edges *graph_init(int n){
	edges *g = malloc(sizeof(edges) * n); //Initializate an array of edges
	int i;

	for(i = 0; i < n; i++)
		g[i].num_edges = 0; //Initializate the number of connection
	return g;
}

void graph_add_edge(edges *g, int from, int to){
	g[from].edges[g[from].num_edges] = to; //Add a new connection
	g[from].num_edges++; //Increse the number of connection
}

int bfs(edges *g, int n, int from){
	int *distances = malloc(sizeof(int) * n); //Allocate memory for an array
	int i;
	int max_distance = 0; //Initializate the maximum distance
	queue q;

	for(i = 0; i < n; i++)
		distances[i] = -1; //Initializate all the distances
	distances[from] = 0; //Set the distance from the source

	queue_init(&q, n); //Initializate the queue
	queue_enqueue(&q, from); //Enqueue the source in the queue

	while(!queue_isEmpty(&q)){ //Checks if the queue is empty
		int src = queue_dequeue(&q); //Extract the source

		for(i = 0; i < g[src].num_edges; i++){ //For all the edges connected to src
			int dest = g[src].edges[i];

			if(distances[dest] == -1){ //Edge isn't been visited yet
				distances[dest] = distances[src] + 1; //Calculate the distance from the source

				max_distance = distances[dest] > max_distance ? distances[dest] : max_distance; //Calculate the max distance

				queue_enqueue(&q, dest); //Enqueue the edge in the queue
			}
		}
	}

	//Checks if all edges has been visitated
	for(i = 0; i < n; i++)
		if(distances[i] == -1)
			max_distance = -1;

	queue_deinit(&q); //Deallocate the queue
	free(distances); //Deallocate the array
	return max_distance;
}

int max_min_path(edges *g, int n){
	int i, res;
	int max_distance = -1;

	//For all the edges calculate the max_distance
	for(i = 0; i < n; i++){
		res = bfs(g, n, i);
		if(res == -1) //The graph isn't connected
			return -1;
		max_distance = max_distance < res ? res : max_distance; //Calculate the max_distance
	}

	return max_distance;
}

void free_graph(edges *g, int n){
	int i;

	for(i = 0; i < n; i++)
		free(g[i].edges); //Deallocate all the arrays
	free(g); //Deallocate the graph
}

int main(){
	int n, i, from;
	edges *g;

	//Read the dimension of the graph
	scanf("%d", &n);

	//Initializate the graph
	g = graph_init(n);

	//Read all the edges and all the connections
	for(from = 0; from < n; from++){
		int ne;
		scanf("%d", &ne); //Read the number of connection for the i edge

		g[from].edges = malloc(sizeof(int) * ne); //Allocate an array for all the connections

		//Read all the connection for the i edge
		for(i = 0; i < ne; i++){
			int to;
			scanf("%d", &to);

			graph_add_edge(g, from, to); //Add the new connection
		}
	}

	printf("%d\n", max_min_path(g, n)); //Calculate and print the maximum min_path

	free_graph(g, n); //Deallocate memory
	return 0;
}
