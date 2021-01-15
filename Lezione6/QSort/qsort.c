/*Scrivere un programma che utilizzi la funzione qsort e ordini un vettore di
interi (in input), in modo da ottenere il seguente effetto. L’array ordinato
deve contenere prima tutti i numeri pari e, a seguire, i numeri dispari. Si
assuma che il numero 0 sia pari. I numeri pari devono essere ordinati in
modo crescente fra di loro. I numeri dispari devono essere ordinati in modo
decrescente fra di loro.
La prima riga dell’input contiene la dimensione N (non limitata) dell’array.
Le righe successive contengono gli elementi dell’array, uno per riga.
L’output contiene gli elementi dell’array ordinati come richiesto, uno per
riga.*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b);

int main(){
	int N, *a;
	int i;
	scanf("%d", &N);
	if(N <= 0) return -1;
	a = (int*) malloc(sizeof(int) * N);
	if(a == NULL) return -1;
	for(i=0; i<N; i++)
		scanf("%d", &a[i]);
	qsort(a, N, sizeof(int), compare);
	for(i=0; i<N; i++)
		printf("%d\n", a[i]);
	return 0;
}

int compare(const void *a, const void *b){
	int *a1 = (int*) a;
	int *b1 = (int*) b;
	if((*a1)%2 == 0 && (*b1)%2 == 0)
		return (*a1 - *b1);
	else{
		if((*a1)%2 != 0 && (*b1)%2 != 0)
			return (*b1 - *a1);
		else{
			if((*a1)%2 == 0)
				return -1;
			else
				return 1;
		}
	}
}
