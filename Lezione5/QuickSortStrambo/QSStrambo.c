/*
Modificare il Quicksort del primo esercizio in maniera tale che ordini gli
elementi pari nella parte inferiore dell'array e quelli dispari in quella
superiore.
Scrivere un programma che utilizzi la funzione per ordinare come indicato
un array di N interi letti da input.
La prima riga dell'input contiene la dimensione N (non limitata) dell'array.
Le righe successive contengono gli elementi dell'array, uno per riga.
L'output contiene la sequenza ordinata, su una sola riga.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int *a, int sx, int dx);
int PartitionStrambo(int *a, int sx, int px, int dx);
void swap(int *a, int *b);

int main(){
	int N, *a, i;
	srand(time(NULL));
	scanf("%d", &N);
	a = malloc(sizeof(int) * N);
	if(a == NULL) return -1;
	for(i = 0; i < N; i++)
		scanf("%d", &a[i]);
	QuickSort(a, 0, N-1);
	for(i = 0; i < N; i++)
		printf("%d ", a[i]);
	free(a);
	return 0;
}

void QuickSort(int *a, int sx, int dx){
	if(sx < dx){
		int pivot = sx + (rand() % (dx-sx+1));
		int px = PartitionStrambo(a, sx, pivot, dx);
		QuickSort(a, sx, px-1);
		QuickSort(a, px+1, dx);
	}
}

int PartitionStrambo(int *a, int sx, int px, int dx){
	int i = sx-1;
	int j = sx;
	int k = dx;
	swap(a+px, a+dx);
	while(j < k){
		if(a[dx]%2 == 0){
			if(a[j]%2 == 0){
				if(a[j] <= a[dx]){
					i++;
					swap(a+i, a+j);
					j++;
				}
				else j++;
			}
			else{
				k--;
				swap(a+j, a+k);
			}
		}
		else{
			if(a[j]%2 != 0){
				if(a[j] <= a[dx]) j++;
				else{
					k--;
					swap(a+j, a+k);
				}
			}
			else{
				i++;
				swap(a+i, a+j);
				j++;
			}
		}
	}
	if(a[dx]%2 == 0){
		swap(a+(i+1), a+dx);
		return i+1;
	}
	else{
		swap(a+j, a+dx);
		return j;
	}
}

void swap (int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
