/*A partire dal codice dell’esercizio precedente, scrivere una funzione che,
dato un array di stringhe e la sua lunghezza, lo ordini (lessicograficamente)
utilizzando l’algoritmo Quicksort.
Scrivere un programma che utilizzi la funzione per ordinare un array di
N stringhe lette da input e stampi in output gli elementi dell’array ordinato.
Assumere che la lunghezza massima di una stringa sia 100 caratteri.
Si pu`o utilizzare la funzione strcmp in string.h per confrontare lessicograficamente due stringhe. Utilizzare il comando man strcmp per maggiori
informazioni.
La prima riga dell’input contiene la dimensione N dell’array. Le righe successive contengono gli elementi dell’array, una stringa per riga. Ogni stringa
ha lunghezza massima di 100 caratteri.
L’output contiene gli elementi dell’array ordinato, una stringa per riga.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void QuickSort(char **a, int sx, int dx);
int partiziona(char **a, int sx, int px, int dx);
void swap(char **a, char **b);

int main(){
	int N, i;
	char **a;
	srand(time(NULL));
	scanf("%d", &N);
	a = malloc(sizeof(char*) * N);
	if(a == NULL) return -1;
	for(i = 0; i < N; i++){
		a[i] =(char *) malloc(101 * sizeof(char));
		if(a[i] == NULL) return -1;
		scanf("%s", a[i]);
	}
	QuickSort(a, 0, N-1);
	for(i = 0; i < N; i++){
		printf("%s\n", a[i]);
		free(a[i]);
	}
	free(a);
	return 0;
}

void QuickSort(char **a, int sx, int dx){
	if(sx < dx){
		int pivot, perno;
		pivot = sx+(rand()%(dx-sx+1));
		perno = partiziona(a, sx, pivot, dx);

		QuickSort(a, sx, perno-1);
		QuickSort(a, perno+1, dx);
	}
}

int partiziona(char **a, int sx, int px, int dx){
	int i = sx-1;
	int j;
	swap(&a[px], &a[dx]);

	for(j = sx; j < dx; j++){
		if(strcmp(a[j], a[dx]) < 0)
			swap(&a[++i], &a[j]);
	}
	swap(&a[i+1], &a[j]);
	return i+1;
}

void swap(char **a, char **b){
	char *temp = malloc(sizeof(char));
	temp = *a;
	*a = *b;
	*b = temp;
}
