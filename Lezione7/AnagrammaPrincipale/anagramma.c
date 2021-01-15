/*L’anagramma principale di una stringa S `e l’anagramma di S ottenuto ordinando i suoi simboli
individualmente. Ad esempio, l’anagramma principale
di abracadabra `e aaaaabbcdrr. Notare che l’anagramma principale di una
stringa `e unico e che stringhe diverse possono avere lo stesso anagramma
principale.
Scrivere un programma che legga da tastiera una sequenza A di N stringhe di lunghezza variabile.
Il programma deve poi raggruppare le stringhe
di A aventi lo stesso anagramma principale e restituire le stringhe di ciascun
gruppo in ordine lessicografico non-decrescente. I gruppi devono essere restituiti in ordine lessicografico
non-decrescente del corrispondente anagramma
principale.
L’input `e formattato nel seguente modo:
• La prima riga contiene la lunghezza N della sequenza. Si assuma che
N sia maggiore di zero.
• Le righe successive contengono le N stringhe che compongono la sequenza A, una per riga. Si pu`o assumere
che le stringhe abbiano
lunghezza inferiore a 20 caratteri.
L’output deve contenere solo e soltanto un gruppo di stringhe per riga.
Le stringhe dello stesso gruppo devono essere separate da uno spazio.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct{
	string str;
	int pos;
}anagramma;

int compareChar(const void *a, const void *b);
int compareStr(const void *a, const void *b);

int main(){
	int N, i;
	string *s, tmp;
	anagramma *a;
	scanf("%d", &N);

	tmp = malloc(sizeof(string) * 21);//Allocazione di una variabile d'appoggio

	//Alloco le N stringhe
	s = malloc(sizeof(string) * N);
	if(s == NULL) return -1;
	a = malloc(sizeof(anagramma) * N);
	if(a == NULL) return -1;

	//Leggo le N stringhe
	for(i=0; i<N; i++){
		s[i] = malloc(sizeof(char) * 21);
		if(s[i] == NULL) return -1;
		scanf("%s", s[i]);
	}

	//Ordino le N stringhe
	qsort(s, N, sizeof(string), compareStr);

	//Copio le N stringhe con la loro posizione
	for(i=0; i<N; i++){
		a[i].str = malloc(sizeof(char) * 21);
		if(a[i].str == NULL) return -1;
		strcpy(a[i].str, s[i]);
		a[i].pos = i;
		qsort(a[i].str, strlen(a[i].str), sizeof(char), compareChar); //Calcolo l'anagramma
	}

	//Ordina tutti gli anagrammi
	qsort(a, N, sizeof(anagramma), compareStr);

	//Stampo il risultato
	printf("%s", s[a[0].pos]);
	strcpy(tmp, a[0].str);
	for(i=1; i<N; i++){
		if(strcmp(tmp, a[i].str)) printf("\n%s", s[a[i].pos]); //Se la stringa precedente non è uguale a quella attuale vado a capo
		else printf(" %s", s[a[i].pos]);
		strcpy(tmp, a[i].str);

		free(a[i].str);
	}

	//Deallocazione della memoria
	for(i=0; i<N; i++)
		free(s[i]);
	free(tmp);
	free(a);
	free(s);

	return 0;
}

int compareChar(const void *a, const void *b){
	char c1 = *(char *)a;
	char c2 = *(char *)b;
	if(c1 < c2) return -1;
	else{
		if(c1 > c2) return 1;
			else return 0;
	}
}

int compareStr(const void *a, const void *b){
	string str1 = *(string *)a;
	string str2 = *(string *)b;
	return strcmp(str1, str2);
}
