/*
Si consideri il quadrante positivo del piano cartesiano. Un punto colorato sul
piano `e caratterizzato da una tripla (x, y, c), dove x, y e c sono valori interi
non-negativi. Il primo intero della tripla caratterizza l’ascissa del punto, il
secondo intero l’ordinata, il terzo intero `e il colore assegnato al punto.
Sia A un insieme di N punti colorati. Lo scopo del programma `e quello di
rispondere a una sequenza di interrogazioni sui punti di A. Un’interrogazione
`e definita da due coppie h(x1, y1); (x2, y2)i, dove x1 < x2 e y1 < y2, che
identificano un rettangolo R:
R = {(u, v) ∈ N^2| x1 ≤ u ≤ x2 ∧ y1 ≤ v ≤ y2}
Data un’interrogazione R, si vuole calcolare il numero di colori distinti dei
punti di A che ricadono in R (i punti sul perimetro del rettangolo devono
essere considerati nel conteggio).
Scrivere un programma che legga da tastiera una sequenze A di N punti
colorati e un insieme Q di M interrogazioni, e stampi la risposta a ciascuna
interrogazione su una riga distinta. Nel caso non vi siano punti all’interno
del rettangolo stampare 0.
L’input `e formattato nel seguente modo:
• Le prime due righe contengono i due interi N e M, rispettivamente.
Si assuma che N > 0 ed M > 0.
• Seguono N righe, contenenti i punti colorati, uno per riga. Ogni punto `e definito da 3 interi, separati da uno spazio,
che rappresentano,
nell’ordine, i valori x, y e c.
• Le ultime M righe contengono le interrogazioni, disposte una per riga.
Ogni interrogazione `e definita da 4 interi, separati da uno spazio, che
rappresentano, nell’ordine, i valori x1, y1, x2, y2. Si assuma che x1 <
x2 e y1 < y2.
L’output deve contenere solo e soltanto gli interi di risposta alle
interrogazioni, uno per riga*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int x;
	int y;
	int c;
}punto;

int compare(const void *a, const void *b);
int conta(punto *p, int N, int x1, int y1, int x2, int y2);

int main(){
	int N, M, i, x1, y1, x2, y2;
	punto *p;
	scanf("%d %d", &N, &M);

	//Alloco la memoria per N punti
	p = malloc(sizeof(punto) * N);
	if(p == NULL) return -1;

	//Leggo gli N punti
	for(i=0; i<N; i++)
		scanf("%d %d %d", &(p[i].x), &(p[i].y), &(p[i].c));

	//Ordino gli N punti per colore
	qsort(p, N, sizeof(punto), compare);

	for(i=0; i<M; i++){
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2); //Leggo le M interrogazioni
		printf("%d\n", conta(p, N, x1, y1, x2, y2)); //Calcolo e stampo il risultato
	}

	free(p); //Dealloco la memoria
	return 0;
}

int compare(const void *a, const void *b){
	punto c1 = *(punto *)a;
	punto c2 = *(punto *)b;
	return c1.c - c2.c;
}

int conta(punto *p, int N, int x1, int y1, int x2, int y2){
	int ris = 0;
	int last_color = -1;
	int i;
	for(i=0; i<N; i++){
		if(p[i].x >= x1 && p[i].x <= x2 && p[i].y >= y1 && p[i].y <= y2){
			if(last_color != p[i].c){
				ris++;
				last_color = p[i].c;
			}
		}
	}
	return ris;
}
