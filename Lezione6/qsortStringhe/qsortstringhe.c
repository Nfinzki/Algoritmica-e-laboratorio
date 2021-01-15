/*Scrivere un programma che legga in input un array A di stringhe e che
utilizzi la funzione qsort per ordinare in ordine alfabetico decrescente le
stringhe in input. Assumere che la lunghezza massima di una stringa sia
100 caratteri.
La prima riga dell’input contiene la dimensione N dell’array. Le righe successive contengono gli
elementi dell’array, una stringa per riga. Ogni stringa
ha lunghezza massima di 100 caratteri.
L’output contiene gli elementi dell’array ordinato in modo decrescente, una
stringa per riga.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b);

int main(){
	int N, i;
	char **a;
	scanf("%d", &N);
	if(N <= 0) return -1;
	a = malloc(sizeof(char*) * N);
	if(a == NULL) return -1;
	for(i=0; i<N; i++){
		a[i] = malloc(sizeof(char) * 101);
		scanf("%s", a[i]);
	}
	qsort(a, N, sizeof(char*), compare);
	for(i=0; i<N; i++){
		printf("%s\n", a[i]);
		free(a[i]);
	}
	free(a);
	return 0;
}

int compare(const void *a, const void *b){
	char **a1 = (char **) a;
	char **b1 = (char **) b;
	return -1*strcmp(*a1, *b1);
}
