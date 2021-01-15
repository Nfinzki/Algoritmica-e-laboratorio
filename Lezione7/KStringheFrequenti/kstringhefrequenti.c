/*Scrivere un programma che legga da tastiera due interi N e K e una sequenza
di N stringhe e che stampi le K stringhe pi`u frequenti in essa contenute, in
ordine lessicografico.
Si pu`o assumere che:
• non esistano due stringhe con la stessa frequenza;
• il valore di K sia minore o uguale al numero di stringhe distinte;
• le stringhe contengono soltanto caratteri alfanumerici (a−z minuscoli
e maiuscoli o numeri, nessuno spazio o punteggiatura) e sono lunghe
al pi`u 100 caratteri ciascuna.
L’input `e formattato nel seguente modo: la prima riga contiene il numero N
di stringhe da leggere, mentre la seconda riga contiene l’intero K. Seguono
N righe contenenti una stringa ciascuna.
L’output deve contenere solo e soltanto le K stringhe pi`u frequenti,
ordinate lessicograficamente, stampate una per riga.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

//Struttura utilizzata per il calcolo del risultato
typedef struct{
	int freq;
	int pos;
}risultato;

int compare(const void *a, const void *b);
int compare2(const void *a, const void *b);
void frequenza(string *s, int N, risultato *r, int K);
void sostituisciMin(risultato *r, int K, int f, int p);

int main(){
	int N, K, i;
	string *s;
	risultato *r;
	scanf("%d", &N);

	//Allocazione di N strignhe
	s = malloc(sizeof(string) * N);
	if(s == NULL) return -1;

	scanf("%d", &K);

	//Allocazione di K risultati
	r = malloc(sizeof(risultato) * K);
	if(r == NULL) return -1;

	//Leggo le N stringhe
	for(i=0; i<N; i++){
		s[i] = malloc(sizeof(string*) * 101);
		scanf("%s", s[i]);
	}

	//Ordino le stringhe in ordine alfanumerico
	qsort(s, N, sizeof(string), compare);

	//Calcolo le K stringhe più frequenti in r
	frequenza(s, N, r, K);

	//Ordino il risultato
	qsort(r, K, sizeof(risultato), compare2);

	//Stampo il risultato
	for(i=0; i<K; i++)
		printf("%s\n", s[r[i].pos]);

	//Dealloco la memoria
	for(i=0; i<N; i++)
		free(s[i]);
	free(r);
	free(s);
	return 0;
}

int compare(const void *a, const void *b){
	string s1 = *(string*)a;
	string s2 = *(string*)b;
	return strcmp(s1, s2);
}

int compare2(const void *a, const void *b){
	risultato r1 = *(risultato *)a;
	risultato r2 = *(risultato *)b;
	return r1.pos - r2.pos;
}

void frequenza(string *s, int N, risultato *r, int K){
	int i = 1;
	int freq = 1;
	int j = 0;
	string tmp = s[0];

	while(i<N){
		if(strcmp(tmp, s[i]) == 0){
			freq++;}
		else{
			if(j<K){ //Se l'array con i risultati non è pieno inserisco senza controlli
				r[j].freq = freq;
				r[j].pos = i-1;
				j++;

				/*Per una soluzione più efficiente: se j==K chiamo build-min-heap O(n) o forse min-heapify O(logn)*/
			}
			else sostituisciMin(r, K, freq, i-1); //Se l'array è pieno sostituisco il valore minimo
				/*Soluzione più efficiente: Sostituire la radice (nodo minimo) con la nuova frequenza (se questa è maggiore) e poi chiamare min-heapify O(logn)*/

			tmp = s[i];
			freq = 1;
		}
		i++;
	}
	sostituisciMin(r, K, freq, i-1);
}

void sostituisciMin(risultato *r, int K, int f, int p){
	int i;
	risultato min;

	//Trovo la frequenza minima in risultato
	min.freq = r[0].freq;
	min.pos = 0; //Utilizzo pos per salvare la posizione in cui si trova il minimo

	for(i=1; i<K; i++){
		if(r[i].freq < min.freq){
			min.freq = r[i].freq;
			min.pos = i;
		}
	}

	//Se la frequenza minima calcolata è minore della frequenza massima calcolata da frequenza faccio la sostituzione
	if(min.freq < f){
		r[min.pos].freq = f;
		r[min.pos].pos = p;
	}
}
