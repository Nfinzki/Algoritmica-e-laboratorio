/*Partendo dall’implementazione del primo esercizio, implementare il Quicksort su interi con three-way partition. L’algoritmo si differenzia dal Quicksort
per la fase di partizionamento. In questo caso la funzione distribuzione
divide l’array in tre intervalli (invece di due):
1. gli elementi minori del pivot;
2. gli elementi uguali al pivot;
3. gli elementi maggiori del pivot.
Scrivere un programma che utilizzi la funzione per ordinare un array di
N interi letti da input.
La prima riga dell’input contiene la dimensione N (non limitata) dell’array.
Le righe successive contengono gli elementi dell’array, uno per riga.
L'output contiene gli elementi dell’array ordinato, su una sola riga.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ThreeQuickSort(int *a, int sx, int dx);
void RandomPartition(int *a, int sx, int px, int dx, int *i, int *j);
void swap(int *a, int *b);

int main(){
	srand(time(NULL));
	int N, *a, i;
	scanf("%d", &N);
	if(N <= 0) return -1;
	a = malloc(sizeof(int) * N);
	if(a == NULL) return -1;
	for(i = 0; i < N; i++)
		scanf("%d", &a[i]);
	ThreeQuickSort(a, 0, N-1);
	for(i = 0; i < N; i++)
		printf("%d ", a[i]);
	free(a);
	return 0;
}

void ThreeQuickSort(int *a, int sx, int dx){
	if(sx < dx){
		int i, j, pivot;
		pivot = sx + (rand() % (dx-sx+1));
		RandomPartition(a, sx, pivot, dx, &i, &j);
		ThreeQuickSort(a, sx, i);
		ThreeQuickSort(a, j+1, dx);
	}
}

void RandomPartition(int *a, int sx, int px, int dx, int *i, int *j){
	*i = sx-1;
	*j = sx;
	int k = dx;
	swap(a+px, a+dx);
	while(*j < k){
		if(a[*j] < a[dx]){
			(*i)++;
			swap(a+(*i), a+(*j));
			(*j)++;
		}
		else{
			if(a[*j] > a[dx]){
				k--;
				swap(a+(*j), a+k);
			}
			else (*j)++;
		}
	}
	swap(a+(*j), a+dx);
}

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
