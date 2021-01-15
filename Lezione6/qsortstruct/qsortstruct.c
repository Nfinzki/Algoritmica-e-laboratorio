/*Scrivere un programma che utilizzi la funzione qsort per ordinare un vettore
di punti del piano cartesiano. Ciascun punto `e formato da una coppia di
coordinate (x, y).
I punti devono essere ordinati per ascissa crescente. A parit`a di ascissa,
si ordini per ordinata decrescente.
La prima riga dell’input contiene il numero N dei punti. Le righe successive
contengono le coordinate dei punti, una coppia per riga (ascissa e ordinata
separate da uno spazio).
L’output contiene la sequenza ordinata dei punti, un punto per riga (ascissa
e ordinata separate da uno spazio), ordinati per ascissa crescente. A parit`a
di ascissa, l’ordinamento `e per ordinata decrescente.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct coor{
	int x;
	int y;
} coordinate;

int compare(const void *a, const void *b);

int main(){
	int N, i;
	coordinate *punto;
	scanf("%d", &N);
	punto = (coordinate*) malloc(sizeof(coordinate) * N);
	if(punto == NULL) return -1;
	for(i=0; i<N; i++)
		scanf("%d %d", &(punto[i].x), &(punto[i].y));
	qsort(punto, N, sizeof(coordinate), compare);
	for(i=0; i<N; i++)
		printf("%d %d\n", punto[i].x, punto[i].y);
	return 0;
}

int compare(const void *a, const void *b){
	coordinate *a1 = (coordinate *) a;
	coordinate *b1 = (coordinate *) b;
	if(a1->x == b1->x)
		return (b1->y - a1->y);
	else
		return (a1->x - b1->x);
}
