/*Scrivere un programma che utilizzi la funzione qsort per ordinare un array
di stringhe. Le stringhe devono essere ordinate per lunghezza crescente. A
parit`a di lunghezza, si utilizzi l’ordinamento lessicografico. Utilizzare una
struct che memorizzi una stringa e la sua lunghezza per evitare di calcolare
quest’ultima ad ogni confronto.
La prima riga dell’input contiene la dimensione N dell’array. Le righe successive contengono
gli elementi dell’array, una stringa per riga. Ogni stringa
ha lunghezza massima di 100 caratteri.
L’output contiene gli elementi dell’array ordinato come richiesto, una stringa
per riga.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct  str{
	string s;
	int len;
}stringhe;

int compare(const void *a, const void *b);

int main(){
	int N, i;
	stringhe *a;
	scanf("%d", &N);
	a = (stringhe *) malloc(sizeof(stringhe) * N);
	for(i=0; i<N; i++){
		a[i].s =(string) malloc(sizeof(string) * 101);
		scanf("%s", a[i].s);
		a[i].len = strlen(a[i].s);
	}
	qsort(a, N, sizeof(stringhe), compare);
	for(i=0; i<N; i++){
		printf("%s\n", a[i].s);
		free(a[i].s);
	}
	free(a);
	return 0;
}

int compare(const void *a, const void *b){
	stringhe *a1 = (stringhe *) a;
	stringhe *b1 = (stringhe *) b;
	if(a1->len == b1->len)
		return strcmp(a1->s, b1->s);
	else
		return (a1->len - b1->len);
}
